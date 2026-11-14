// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A60C0 rf_crt_localtime64_forward
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(pointer to signed64-bit time). Pass-through wrapper to original __localtime64, same one-DWORD pointer argument, propagates tm pointer EAX. No own error/null validation or
// logging state changes; no x87 argument/return.
struct tm *__cdecl rf_crt_localtime64_forward(__time64_t *Time)
{
  return _localtime64(Time);
}

