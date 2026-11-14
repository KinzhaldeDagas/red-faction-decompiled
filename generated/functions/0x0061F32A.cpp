// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061F32A ___ansicp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(LCID),intcodepage/-1.
// Ownstackcharbuffer6logicalAPIcapacitywithadditionalforcedbyte6NUL. GetLocaleInfoA(LCID,1004h,buffer,6);nonzero->atol(buffer),zero->-1. No
// ownLCIDvalidation,errno/dosmaperr,strictnumericparseorcodepagevalidation. Securitycookiecheckednormalreturns; extraNULboundsdelegatedatolreadifAPIunexpectedlyomitsonewithin6.
int __cdecl __ansicp(LCID Locale)
{
  CHAR LCData[8]; // [esp+0h] [ebp-Ch] BYREF

  LCData[6] = 0;
  if ( GetLocaleInfoA(Locale, 0x1004u, LCData, 6) )
    return atol(LCData);
  else
    return -1;
}

