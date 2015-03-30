#include "libbbn-ni-r.h"

//global to hold on to session handle
NiFpga_Session session;
bool isOpen = false;

//Initialize FPGA on loading the library -- constructor hook in header
void init() {
  NiFpga_Status status = NiFpga_Initialize();
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
  NiFpga_Status status = NiFpga_WriteU32(session, NiFpga_SimpleDigitizer_VI_ControlU32_NumberofSamples, numSamples);
  return status;
};
BBN_NI_R_STATUS get_numSamples(uint32_t* numSamples){
  NiFpga_Status status = NiFpga_ReadU32(session, NiFpga_SimpleDigitizer_VI_ControlU32_NumberofSamples, numSamples);
  return status;
};

BBN_NI_R_STATUS set_sampleInterval(double sampleInterval){
  uint32_t sampleInterval_us = static_cast<uint32_t>(sampleInterval/1e6);
  NiFpga_Status status = NiFpga_WriteU32(session, NiFpga_SimpleDigitizer_VI_ControlU32_SampleIntervaluSec, sampleInterval * 1000000);
  return status;
};
BBN_NI_R_STATUS get_sampleInterval(double* sampleInterval){
  uint32_t sampleInterval_us;
  NiFpga_Status status = NiFpga_ReadU32(session, NiFpga_SimpleDigitizer_VI_ControlU32_SampleIntervaluSec, &sampleInterval_us);
  *sampleInterval = static_cast<double>(sampleInterval_us) / 1000000;
  return status;
};
