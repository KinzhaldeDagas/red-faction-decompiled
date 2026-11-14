// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00594760 rf_cpu_read_timestamp_counter
// UNREALRED VERIFIED [system-progress-20261028]: Direct RDTSC wrapper returns64-bit counter in EDX:EAX. No serialization, feature check, scaling or epoch conversion. Legacy CPU-speed caller0x594770 uses only low32 bits.
unsigned __int64 rf_cpu_read_timestamp_counter()
{
  return __rdtsc();
}

