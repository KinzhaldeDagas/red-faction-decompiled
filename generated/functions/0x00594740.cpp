// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00594740 rf_system_time64_forward
// UNREALRED VERIFIED [system-progress-20261028]: Forwards optional time64 output pointer to CRT _time64. Returns64-bit time in EDX:EAX; does not truncate internally. Seeder0x594700 uses only low32 return bits.
__time64_t __cdecl rf_system_time64_forward(__time64_t *Time)
{
  return _time64(Time);
}

