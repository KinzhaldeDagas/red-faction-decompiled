// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DF78 __checkTOS_withFB
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Helper reads ONLY highDWORD of caller DOUBLE image at entryESP+8. EAX=high&0x7FF00000; compare against allones exponent. Ordinary exponent returns masked
// value and comparison flags. Allones path reloads FULL highDWORD without changing flags, thenRET. No FLD/pop/arithmetic/classification of low payload bits; original EFLAGS equality
// from exponent compare is a live output used by math kernels. Not a canonical Boolean.
int __cdecl _checkTOS_withFB(int a1, int a2)
{
  int result; // eax

  result = a2 & 0x7FF00000;
  if ( (a2 & 0x7FF00000) == 0x7FF00000 )
    return a2;
  return result;
}

