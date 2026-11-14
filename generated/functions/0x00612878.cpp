// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00612878 _CPtoLCID
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal EAX=raw codepage,plainRET,EAX LCID. Exact
// mapping932->1041(411h),936->2052(804h),949->1042(412h),950->1028(404h),all others0 including1361. SUB/conditionalreturn sequence changes onlyEAX/flags, preservesECX/EDX
// neededbysetmbcp_nolock. No stackargument, OSlookup, validation, errno or allocation.
int __usercall CPtoLCID@<eax>(int a1@<eax>)
{
  int v1; // eax
  int v2; // eax
  int v3; // eax

  v1 = a1 - 932;
  if ( !v1 )
    return 1041;
  v2 = v1 - 4;
  if ( !v2 )
    return 2052;
  v3 = v2 - 13;
  if ( !v3 )
    return 1042;
  if ( v3 == 1 )
    return 1028;
  return 0;
}

