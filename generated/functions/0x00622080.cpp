// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00622080 ___ascii_strnicmp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(first bytes, second bytes, raw32-bit count),
// returns exactly -1/0/+1. Count0 returns0 without pointer reads. For nonzero count read both current bytes; if either NUL, compare those RAW bytes immediately before folding.
// Otherwise advance both pointers, fold only unsigned ASCII A..Z by adding0x20, compare unsigned folded bytes; mismatch returns normalized sign. Equal nonzero bytes decrement count
// with32-bit wrap; exhausted count returns0. High-bit bytes unchanged, no locale provider or multibyte handling. Existing signed-int count type does not imply negative rejection: any
// nonzero count, including negative bit patterns, enters the decrement loop until equality limit, NUL or mismatch. No input validation or writes.
int __cdecl __ascii_strnicmp(unsigned __int8 *a1, unsigned __int8 *a2, int a3)
{
  int v3; // ecx
  unsigned __int8 v6; // ah
  unsigned __int8 v7; // al
  bool v8; // cf

  v3 = a3;
  if ( a3 )
  {
    do
    {
      v6 = *a1;
      v7 = *a2;
      if ( !*a1 || !v7 )
        break;
      ++a1;
      ++a2;
      if ( v6 >= 0x41u && v6 <= 0x5Au )
        v6 += 32;
      if ( v7 >= 0x41u && v7 <= 0x5Au )
        v7 += 32;
      v8 = v6 < v7;
      if ( v6 != v7 )
        goto differ;
      --v3;
    }
    while ( v3 );
    v3 = 0;
    v8 = v6 < v7;
    if ( v6 == v7 )
      return v3;
differ:
    v3 = -1;
    if ( !v8 )
      return 1;
  }
  return v3;
}

