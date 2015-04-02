function check_status(status)
  if status != 0
    error("libbbn-ni-r failed with error number $status")
  end
end

function open_load_run()
    check_status(ccall((:open_load_run, "libbbn-ni-r"), Cint, ()))
end

function set_numSamples(numSamples)
  check_status(ccall((:set_numSamples, "libbbn-ni-r"), Cint, (Cuint,), numSamples))
end

function get_numSamples()
  numSamples = Ref{Cuint}(0)
  check_status(ccall((:get_numSamples, "libbbn-ni-r"), Cint, (Ref{Cuint},), numSamples))
  return numSamples[]
end

function set_sampleInterval(sampleInterval)
  check_status(ccall((:set_sampleInterval, "libbbn-ni-r"), Cint, (Cdouble,), sampleInterval))
end

function get_sampleInterval()
  sampleInterval = Ref{Cdouble}(0)
  check_status(ccall((:get_sampleInterval, "libbbn-ni-r"), Cint, (Ref{Cdouble},), sampleInterval))
  return sampleInterval[]
end

function get_sampleCt()
  sampleCt = Ref{Cint}(0)
  check_status(ccall((:get_sampleCt, "libbbn-ni-r"), Cint, (Ref{Cint},), sampleCt))
  return sampleCt[]
end

function enable_acquisition()
  check_status(ccall((:enable_acquisition, "libbbn-ni-r"), Cint, ()))
end

function reset_fifo()
  check_status(ccall((:reset_fifo, "libbbn-ni-r"), Cint, ()))
end

function disable_acquisition()
  check_status(ccall((:disable_acquisition, "libbbn-ni-r"), Cint, ()))
end

function trigger()
  check_status(ccall((:trigger, "libbbn-ni-r"), Cint, ()))
end

function trigger_out()
  check_status(ccall((:trigger_out, "libbbn-ni-r"), Cint, ()))
end

function transfer_waveform(numPts, timeOut)
  data = Array(Float64, numPts)
  check_status(ccall((:transfer_waveform, "libbbn-ni-r"), Cint,
                      (Cuint, Ptr{Cdouble}, Cdouble),
                      numPts, data, timeOut))
  return data
end

function get_analogOut()
  val = Ref{Cdouble}(0)
  check_status(ccall((:get_analogOut, "libbbn-ni-r"), Cint, (Ref{Cdouble},), val))
  return val[]
end

function get_analogIn()
  val = Ref{Cdouble}(0)
  check_status(ccall((:get_analogIn, "libbbn-ni-r"), Cint, (Ref{Cdouble},), val))
  return val[]
end
