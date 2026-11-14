// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061AD86 __hextodec
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl raw inputBYTE. Pass ZERO-EXTENDED byte to isdigit; afterward SIGN-EXTEND originalbyte intoEAX. Digit predicate nonzero returns original signed ASCII
// value,NOT0..9. Predicate0 returns (signExtendedByte &0xFFFFFFDF)-7 wrapped, with no A..F/a..f admission check. It does not produce a complete checked0..15 hex value.
unsigned int __cdecl _hextodec(char a1)
{
  bool v1; // zf
  unsigned int result; // eax

  v1 = isdigit((unsigned __int8)a1) == 0;
  result = a1;
  if ( v1 )
    return (a1 & 0xFFFFFFDF) - 7;
  return result;
}

