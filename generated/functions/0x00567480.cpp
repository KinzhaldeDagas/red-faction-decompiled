// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567480 rf_clock_read_timestamp_counter
// UNREALRED VERIFIED [system-progress-20261028]: Direct RDTSC wrapper returns64-bit counter in EDX:EAX. Separate from equivalent0x594760. No serialization or feature check. Performance-clock initializer stores only low32 return bits for calibration.
unsigned __int64 rf_clock_read_timestamp_counter()
{
  return __rdtsc();
}

