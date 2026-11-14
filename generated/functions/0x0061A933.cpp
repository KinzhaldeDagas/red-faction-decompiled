// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061A933 _strnlen
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl source/maxUnsigned32. EAX0;max0 returns0 WITHOUT reading source. Otherwise scan bytes while index<max unsigned and byte!=NUL;return number beforeNUL
// ormax. No NULL validation whenmax>0, codepoint/locale interpretation, wide-size multiplication, allocation or copy. End comparison uses JB unsigned, not signed-negative cap.
size_t __cdecl strnlen(const char *String, size_t MaxCount)
{
  size_t result; // eax

  for ( result = 0; result < MaxCount; ++String )
  {
    if ( !*String )
      break;
    ++result;
  }
  return result;
}

