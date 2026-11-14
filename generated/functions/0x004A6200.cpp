// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6200 rf_crt_difftime64_forward
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(two signed64-bit time values),16 argument bytes. Forwards Time2 high/low then Time1 high/low to original __difftime64, caller-cleans16 and propagates double in ST0. No
// incoming ST0 parameter; this return is the x87 value consumed by uptime's __ftol2_sse. No logging state mutation.
double __cdecl rf_crt_difftime64_forward(__time64_t Time1, __time64_t Time2)
{
  return _difftime64(Time1, Time2);
}

