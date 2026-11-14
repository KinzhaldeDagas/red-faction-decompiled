// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00607E57 __localtime64
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl pointer to64-bit time. Get thread/runtime tm buffer; NULL buffer returnsNULL without conversion. Else call localtime64_s(buffer,time), convert
// status0->buffer and ANY nonzero->NULL using NEG/SBB/NOT/AND. No time pointer validation or own conversion; returns reused provider buffer, no new allocation by wrapper or failure
// buffer clearing.
struct tm *__cdecl _localtime64(const __time64_t *Time)
{
  struct tm *result; // eax

  result = __getgmtimebuf();
  if ( result )
    return _localtime64_s(result, Time) == 0 ? result : nullptr;
  return result;
}

