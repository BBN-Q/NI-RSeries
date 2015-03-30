/*
A simple example to see if we can get anything to run.
*/

#include <iostream>
#include <chrono>
#include <thread>

#include "NiFpga_FPGA_VI.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
  NiFpga_Session session;
  /* must be called before any other calls */
  NiFpga_Status status = NiFpga_Initialize();
  cout << "NiFpga_Initialize() status: " << status << endl;
  if (NiFpga_IsNotError(status)) {

    /* opens a session, downloads the bitstream, and runs the FPGA */
    NiFpga_MergeStatus(&status, NiFpga_Open(NiFpga_FPGA_VI_Bitfile,
                                            NiFpga_FPGA_VI_Signature,
                                            "RIO0",
                                            0,
                                            &session));

    cout << "NiFpga_Open() status: " << status << endl;

    if (NiFpga_IsNotError(status)) {

      cout << "Got here!" << endl;
      std::this_thread::sleep_for(std::chrono::seconds(2));

      //Deactivate aquisition
      NiFpga_MergeStatus(&status, NiFpga_WriteBool(session, NiFpga_FPGA_VI_ControlBool_Acquire, 0));

      //Set the number of samples
      NiFpga_MergeStatus(&status, NiFpga_WriteU32(session, NiFpga_FPGA_VI_ControlU32_NumberofSamples, 128));

      //Set the sample rate in us
      NiFpga_MergeStatus(&status, NiFpga_WriteU32(session, NiFpga_FPGA_VI_ControlU32_SampleIntervaluSec, 100));

      //Read the sample count
      int32_t sampleCt;
      NiFpga_MergeStatus(&status, NiFpga_ReadI32(session, NiFpga_FPGA_VI_IndicatorI32_sampleCt, &sampleCt));
      cout << "sampleCt: " << sampleCt << endl;

      //Activate the acquisition
      NiFpga_MergeStatus(&status, NiFpga_WriteBool(session, NiFpga_FPGA_VI_ControlBool_Acquire, 1));

      //Read the sample count
      NiFpga_MergeStatus(&status, NiFpga_ReadI32(session, NiFpga_FPGA_VI_IndicatorI32_sampleCt, &sampleCt));
      cout << "sampleCt: " << sampleCt << endl;

      //Toggle the trigger
      NiFpga_MergeStatus(&status, NiFpga_WriteBool(session, NiFpga_FPGA_VI_ControlBool_Trigger, 0));
      NiFpga_MergeStatus(&status, NiFpga_WriteBool(session, NiFpga_FPGA_VI_ControlBool_Trigger, 1));

      //See if there is any data to read
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      int16_t fifoData[128];
      size_t numPts;
      NiFpga_MergeStatus(&status,
                            NiFpga_ReadFifoI16(session,
                            NiFpga_FPGA_VI_TargetToHostFifoI16_AIFIFO,
                            fifoData,
                            64,
                            1000,
                            &numPts));
      cout << "NiFpga_ReadFifoI16() status: " << status << endl;
      cout << "Num points remaining: " << numPts << " points." << endl;

      //Read the sample count
      NiFpga_MergeStatus(&status, NiFpga_ReadI32(session, NiFpga_FPGA_VI_IndicatorI32_sampleCt, &sampleCt));
      cout << "sampleCt: " << sampleCt << endl;

      if (NiFpga_IsNotError(status))
      {
         NiFpga_MergeStatus(&status,
            NiFpga_ReleaseFifoElements(session, NiFpga_FPGA_VI_TargetToHostFifoI16_AIFIFO, numPts));
      }

      /* must close if we successfully opened */
      NiFpga_MergeStatus(&status, NiFpga_Close(session, 0));
    }
    /* must be called after all other calls */
    NiFpga_MergeStatus(&status, NiFpga_Finalize());
   }
   return status;
}
