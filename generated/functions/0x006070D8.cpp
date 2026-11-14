// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006070D8 __freea
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl Memory pointer. NULL skips. Otherwise compute Memory-8, compare DWORD at that header with0xDDDD; ONLY exact tag match calls free(header), reclaim4-byte
// slot. Other tags untouched, not automatically heap free. No header accessibility/size/ownership/duplicate-free guard; does not zero header or caller pointer. Does not free original
// interior Memory address directly.
void __cdecl _freea(void *Memory)
{
  if ( Memory )
  {
    if ( *((_DWORD *)Memory - 2) == 56797 )
      free((char *)Memory - 8);
  }
}

