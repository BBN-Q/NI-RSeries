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
  NiFpga_Status status = NiFpga_Open(NiFpga_SimpleDigitizer_VI_Bitfile,
                                      NiFpga_SimpleDigitizer_VI_Signature,
                                      "RIO0", 0, &session);
  if (status == NiFpga_Status_Success){
    isOpen = true;
  }
  return status;
}

BBN_NI_R_STATUS set_numSamples(unsigned numSamples){
  return 0;
};
BBN_NI_R_STATUS get_numSamples(unsigned* numSamples){
  return 0;
};

BBN_NI_R_STATUS set_sampleInterval(unsigned sampleInterval){
  return 0;
};
BBN_NI_R_STATUS get_sampleInterval(unsigned* sampleInterval){
  return 0;
};
