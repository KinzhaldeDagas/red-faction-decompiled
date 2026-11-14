// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006205E9 ?strncnt@@YAHPBDH@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Actual input sourcepointer EAX plus ONE stack rawcount; plainRET returns INTEGER byte countEAX,not pointer. ECX=count; while count!=0: decrementECX BEFORE
// testbyte,stop onNUL else advanceEAX pointer. Exhaustion decrementsECX once more to-1;final originalCount-ECX-1 yields consumed count,zero limit returns0 withoutread. Negative
// counts not rejected; wrapped countdown may scan hugeextent untilNUL. No strlen call, NULL/locale/capacityguard. Original620675/620689 callers setEAX source,pushcount,consume return
// as length; corrected customABI.
int __usercall strncnt@<eax>(const char *text@<eax>, int count)
{
  int v2; // ecx

  v2 = count;
  while ( v2 )
  {
    --v2;
    if ( !*text )
      return count - v2 - 1;
    ++text;
  }
  v2 = -1;
  return count - v2 - 1;
}

