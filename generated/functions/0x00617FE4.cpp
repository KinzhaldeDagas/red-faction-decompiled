// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617FE4 __sptype
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(double rawBits), int special-type code;
// corrected two-int logical parameters to ONE by-value binary64, stack8 unchanged. Integer bit classification only: exact highDWORD7FF00000/low0 ->1 positive infinity; FFF00000/low0
// ->2 negative infinity. Otherwise topWORD mask7FF8==7FF8 ->3 quiet NaN; masked7FF0 with highDWORD mask7FFFF or lowDWORD nonzero ->4 signaling NaN; all other values0. No x87
// load/compare, quieting, errno or sign mutation. Non-infinity path loads DWORD from argument BYTE+6 (reads2 bytes beyond8-byte argument) but masks high16 away, so extra bytes
// ignored. Raw NaN quiet/signaling distinction is preserved here; caller fpclass performs FP load/store BEFORE calling this helper.
int __cdecl _sptype(double a1)
{
  if ( HIDWORD(a1) == 2146435072 )
  {
    if ( !LODWORD(a1) )
      return 1;
  }
  else if ( a1 == -INFINITY )
  {
    return 2;
  }
  if ( (HIWORD(a1) & 0x7FF8) == 0x7FF8 )
    return 3;
  if ( (HIWORD(a1) & 0x7FF8) == 0x7FF0 && ((HIDWORD(a1) & 0x7FFFF) != 0 || LODWORD(a1)) )
    return 4;
  return 0;
}

