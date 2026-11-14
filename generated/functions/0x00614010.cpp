// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00614010 __allrem
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Compiler helper
// stdcall(signed64dividend,signed64divisor), signed64remainder EDX:EAX,RET16; corrected unsignedsignature. PreserveEBX/EDI. Convertnegativeoperands to unsignedmagnitudes in
// ownargumentstack,trackONLYoriginaldividend sign. Divisorhigh0: two unsignedDIVsteps,zeroextend finalremainder thennegate ifdividendnegative. Highnonzero: shiftbothmagnitudes
// untildivisorhigh0,divideestimate,multiplyoriginaldivisor; ifcarry/product>dividend subtractonedivisor fromproduct. Form product-dividend,negate
// onlyfornonnegativeoriginaldividend,so remainder hasdividendsign andabs<absdivisor forvalidnonzerodivisor. Divisor0 causesCPU DIVfault,no own guard/errno/callback. INT64_MIN/-1
// remainder0,noseparateoverflowtrap. No quotientoutput,allocation,x87 or externalmemorywrite beyondownstack.
__int64 __stdcall _allrem(__int64 a1, __int64 a2)
{
  int v2; // edi
  int v3; // eax
  unsigned __int64 v4; // rtt
  __int64 result; // rax
  unsigned __int64 v6; // rcx
  unsigned __int64 v7; // rax
  unsigned int v8; // eax
  int v9; // ecx
  bool v10; // cf
  unsigned __int64 v11; // rax

  v2 = 0;
  if ( a1 < 0 )
  {
    v2 = 1;
    HIDWORD(a1) = -HIDWORD(a1) - ((_DWORD)a1 != 0);
    LODWORD(a1) = -(int)a1;
  }
  v3 = HIDWORD(a2);
  if ( a2 < 0 )
  {
    v3 = -HIDWORD(a2) - ((_DWORD)a2 != 0);
    HIDWORD(a2) = v3;
    LODWORD(a2) = -(int)a2;
  }
  if ( !v3 )
  {
    LODWORD(v4) = a1;
    HIDWORD(v4) = HIDWORD(a1) % (unsigned int)a2;
    result = v4 % (unsigned int)a2;
    if ( v2 - 1 < 0 )
      return result;
    return -result;
  }
  v6 = __PAIR64__(v3, a2);
  v7 = a1;
  do
  {
    v6 >>= 1;
    v7 >>= 1;
  }
  while ( HIDWORD(v6) );
  v8 = v7 / (unsigned int)v6;
  v9 = HIDWORD(a2) * v8;
  v11 = (unsigned int)a2 * (unsigned __int64)v8;
  v10 = __CFADD__(v9, HIDWORD(v11));
  HIDWORD(v11) += v9;
  if ( v10 || v11 > a1 )
    v11 -= a2;
  result = v11 - a1;
  if ( v2 - 1 < 0 )
    return -result;
  return result;
}

