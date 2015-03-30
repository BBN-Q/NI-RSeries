/*
 * Generated with the FPGA Interface C API Generator 14.0.0
 * for NI-RIO 14.0.0 or later.
 */

#ifndef __NiFpga_SimpleDigitizer_VI_h__
#define __NiFpga_SimpleDigitizer_VI_h__

#ifndef NiFpga_Version
   #define NiFpga_Version 1400
#endif

#include "NiFpga.h"

/**
 * The filename of the FPGA bitfile.
 *
 * This is a #define to allow for string literal concatenation. For example:
 *
 *    static const char* const Bitfile = "C:\\" NiFpga_SimpleDigitizer_VI_Bitfile;
 */
#define NiFpga_SimpleDigitizer_VI_Bitfile "NiFpga_SimpleDigitizer_VI.lvbitx"

/**
 * The signature of the FPGA bitfile.
 */
static const char* const NiFpga_SimpleDigitizer_VI_Signature = "F1CE92CE4DF634033A86F93319F6AFE3";

typedef enum
{
   NiFpga_SimpleDigitizer_VI_IndicatorI16_AnalogOut = 0x2A,
} NiFpga_SimpleDigitizer_VI_IndicatorI16;

typedef enum
{
   NiFpga_SimpleDigitizer_VI_IndicatorI32_sampleCt = 0x18,
} NiFpga_SimpleDigitizer_VI_IndicatorI32;

typedef enum
{
   NiFpga_SimpleDigitizer_VI_ControlBool_Acquire = 0x22,
   NiFpga_SimpleDigitizer_VI_ControlBool_Trigger = 0x1E,
} NiFpga_SimpleDigitizer_VI_ControlBool;

typedef enum
{
   NiFpga_SimpleDigitizer_VI_ControlU32_NumberofSamples = 0x24,
   NiFpga_SimpleDigitizer_VI_ControlU32_SampleIntervaluSec = 0x10,
} NiFpga_SimpleDigitizer_VI_ControlU32;

typedef enum
{
   NiFpga_SimpleDigitizer_VI_TargetToHostFifoI16_AIFIFO = 0,
} NiFpga_SimpleDigitizer_VI_TargetToHostFifoI16;

#endif
