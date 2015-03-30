/*
 * Generated with the FPGA Interface C API Generator 14.0.0
 * for NI-RIO 14.0.0 or later.
 */

#ifndef __NiFpga_FPGA_VI_h__
#define __NiFpga_FPGA_VI_h__

#ifndef NiFpga_Version
   #define NiFpga_Version 1400
#endif

#include "NiFpga.h"

/**
 * The filename of the FPGA bitfile.
 *
 * This is a #define to allow for string literal concatenation. For example:
 *
 *    static const char* const Bitfile = "C:\\" NiFpga_FPGA_VI_Bitfile;
 */
#define NiFpga_FPGA_VI_Bitfile "NiFpga_FPGA_VI.lvbitx"

/**
 * The signature of the FPGA bitfile.
 */
static const char* const NiFpga_FPGA_VI_Signature = "8FE9D53BE4AAFC25D0D9DDECD342F356";

typedef enum
{
   NiFpga_FPGA_VI_IndicatorI16_AnalogOut = 0x2A,
} NiFpga_FPGA_VI_IndicatorI16;

typedef enum
{
   NiFpga_FPGA_VI_IndicatorI32_sampleCt = 0x18,
} NiFpga_FPGA_VI_IndicatorI32;

typedef enum
{
   NiFpga_FPGA_VI_ControlBool_Acquire = 0x22,
   NiFpga_FPGA_VI_ControlBool_Trigger = 0x1E,
} NiFpga_FPGA_VI_ControlBool;

typedef enum
{
   NiFpga_FPGA_VI_ControlU32_NumberofSamples = 0x24,
   NiFpga_FPGA_VI_ControlU32_SampleIntervaluSec = 0x10,
} NiFpga_FPGA_VI_ControlU32;

typedef enum
{
   NiFpga_FPGA_VI_TargetToHostFifoI16_AIFIFO = 0,
} NiFpga_FPGA_VI_TargetToHostFifoI16;

#endif
