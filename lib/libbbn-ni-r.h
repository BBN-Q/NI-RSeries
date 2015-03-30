/*

Simple library for data acquisition using NI-USB 7855

*/

#ifndef LIBBBN_NI_R_H
#define LIBBBN_NI_R_H

#include "NiFpga_SimpleDigitizer_VI.h"

typedef int BBN_NI_R_STATUS;

#ifdef __cplusplus
extern "C" {
#endif

void init() __attribute__((constructor));
void cleanup() __attribute__((destructor));

BBN_NI_R_STATUS open_load_run();

BBN_NI_R_STATUS set_numSamples(uint32_t numSamples);
BBN_NI_R_STATUS get_numSamples(uint32_t* numSamples);

BBN_NI_R_STATUS set_sampleInterval(double sampleInterval);
BBN_NI_R_STATUS get_sampleInterval(double* sampleInterval);


#ifdef __cplusplus
}
#endif

#endif // LIBBBN_NI_R_H
