// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00620AB3 _findenv
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal EDI=nameByteLen, stack=input string, EAX
// signed index. Assumes narrowenv2021360 nonNULL and pointer-array/string validity; no own lock/validation. Scan entries with mbsnbicoll(input,entry,len)==0 and entry[len] either
// equals OR NUL; no explicit strlen>=len precheck. Match returns nonnegative index. No match returns NEGATED array length (empty array returns0, ambiguous with match index0; caller
// also checks first entry). No allocation, errno or ASCII-only comparison.
int __usercall findenv@<eax>(size_t a1@<edi>, unsigned __int8 *Str1)
{
  const unsigned __int8 **i; // esi
  unsigned __int8 v3; // al

  for ( i = (const unsigned __int8 **)unk_2021360; ; ++i )
  {
    if ( !*i )
      return -(((char *)i - (_BYTE *)unk_2021360) >> 2);
    if ( !_mbsnbicoll(Str1, *i, a1) )
    {
      v3 = (*i)[a1];
      if ( v3 == 61 || !v3 )
        break;
    }
  }
  return ((char *)i - (_BYTE *)unk_2021360) >> 2;
}

