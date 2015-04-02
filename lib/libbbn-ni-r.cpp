#include "libbbn-ni-r.h"

#include <vector>
#include <algorithm> // std::transform

//global to hold on to session handle
NiFpga_Session session;
bool isOpen = false;

//Initialize FPGA on loading the library -- constructor hook in header
void init() {
  NiFpga_Initialize();
}

//Cleanup NI library -- destructor hook in header
void cleanup(){
  if (isOpen) {NiFpga_Close(session, 0);};
  NiFpga_Finalize();
}

BBN_NI_R_STATUS open_load_run(){
  NiFpga_Status status = NiFpga_Open("../" NiFpga_SimpleDigitizer_VI_Bitfile,
                                      NiFpga_SimpleDigitizer_VI_Signature,
                                      "RIO0", 0, &session);
  if (status == NiFpga_Status_Success){
    isOpen = true;
  }
  return status;
}

BBN_NI_R_STATUS set_numSamples(uint32_t numSamples){
  return NiFpga_WriteU32(session, NiFpga_SimpleDigitizer_VI_ControlU32_NumberofSamples, numSamples);
};

BBN_NI_R_STATUS get_numSamples(uint32_t* numSamples){
  return NiFpga_ReadU32(session, NiFpga_SimpleDigitizer_VI_ControlU32_NumberofSamples, numSamples);
};

BBN_NI_R_STATUS set_sampleInterval(double sampleInterval){
  NiFpga_Status status = NiFpga_WriteU32(session, NiFpga_SimpleDigitizer_VI_ControlU32_SampleIntervaluSec, sampleInterval * 1000000);
  return status;
};
BBN_NI_R_STATUS get_sampleInterval(double* sampleInterval){
  uint32_t sampleInterval_us;
  NiFpga_Status status = NiFpga_ReadU32(session, NiFpga_SimpleDigitizer_VI_ControlU32_SampleIntervaluSec, &sampleInterval_us);
  *sampleInterval = static_cast<double>(sampleInterval_us) / 1000000;
  return status;
};

BBN_NI_R_STATUS enable_acquisition(){
  return NiFpga_WriteBool(session, NiFpga_SimpleDigitizer_VI_ControlBool_Acquire, NiFpga_True);
}

BBN_NI_R_STATUS disable_acquisition(){
  return NiFpga_WriteBool(session, NiFpga_SimpleDigitizer_VI_ControlBool_Acquire, NiFpga_False);
}

BBN_NI_R_STATUS trigger(){
  //Toggle the software trigger
  NiFpga_Status status = NiFpga_WriteBool(session, NiFpga_SimpleDigitizer_VI_ControlBool_Trigger, NiFpga_False);
  NiFpga_MergeStatus(&status, NiFpga_WriteBool(session, NiFpga_SimpleDigitizer_VI_ControlBool_Trigger, NiFpga_True));
  NiFpga_MergeStatus(&status, NiFpga_WriteBool(session, NiFpga_SimpleDigitizer_VI_ControlBool_Trigger, NiFpga_False));
  return status;
}

BBN_NI_R_STATUS trigger_out(){
  //Toggle the software trigger
  NiFpga_Status status = NiFpga_WriteBool(session, NiFpga_SimpleDigitizer_VI_ControlBool_TriggerOut, NiFpga_False);
  NiFpga_MergeStatus(&status, NiFpga_WriteBool(session, NiFpga_SimpleDigitizer_VI_ControlBool_TriggerOut, NiFpga_True));
  NiFpga_MergeStatus(&status, NiFpga_WriteBool(session, NiFpga_SimpleDigitizer_VI_ControlBool_TriggerOut, NiFpga_False));
  return status;
}

BBN_NI_R_STATUS reset_fifo(){
  //Pump stop-start to reset FIFO
  //See http://zone.ni.com/reference/en-XX/help/371599H-01/lvfpgahelp/clearing_fpga_fifos/
  NiFpga_Status status = NiFpga_StopFifo(session, NiFpga_SimpleDigitizer_VI_TargetToHostFifoI32_AIFIFO);
  NiFpga_MergeStatus(&status, NiFpga_StartFifo(session, NiFpga_SimpleDigitizer_VI_TargetToHostFifoI32_AIFIFO));
  return status;
}

BBN_NI_R_STATUS transfer_waveform(unsigned numPoints, double* data, double timeOut){
  // Ask for a number of points from the FIFO
  // Assumes memory has been correctly allocated by caller
  uint32_t timeOut_ms = timeOut*1e3;
  std::vector<int32_t> data_int32;
  data_int32.resize(numPoints);
  NiFpga_Status status = NiFpga_ReadFifoI32(session, NiFpga_SimpleDigitizer_VI_TargetToHostFifoI32_AIFIFO, data_int32.data(), numPoints, timeOut_ms, nullptr);
  std::transform(data_int32.begin(), data_int32.end(), data, [](int32_t x){return static_cast<double>(x)/(1 << 22);});
  return status;
}

BBN_NI_R_STATUS get_analogOut(double* val){
  int16_t val_int16;
  NiFpga_Status status = NiFpga_ReadI16(session, NiFpga_SimpleDigitizer_VI_IndicatorI16_AnalogOut, &val_int16);
  *val = static_cast<double>(val_int16) / (1 << 13);
  return status;
}

BBN_NI_R_STATUS get_analogIn(double* val){
  int32_t val_int32;
  NiFpga_Status status = NiFpga_ReadI32(session, NiFpga_SimpleDigitizer_VI_IndicatorI32_AnalogIn, &val_int32);
  *val = static_cast<double>(val_int32) / (1 << 22);
  return status;
}

BBN_NI_R_STATUS get_sampleCt(int32_t* ct){
  return NiFpga_ReadI32(session, NiFpga_SimpleDigitizer_VI_IndicatorI32_sampleCt, ct);
};
