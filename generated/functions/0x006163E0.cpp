// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006163E0 __aulldiv
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Compiler helper
// stdcall(unsigned64dividend,unsigned64divisor), unsigned64quotient EDX:EAX,RET16; corrected false32bitreturn/signeddivisor. PreserveEBX/ESI. Divisorhigh0: divide dividendhigh
// bylowdivisor,savequotienthigh,divide lowhalf withcarriedremainder,returnfullpair. Divisorhighnonzero:
// shiftdivisor/dividendrighttogetheruntildivisorhigh0,oneDIVestimate,verifyestimate*originaldivisor usingunsignedMULandcarry; overflow/product>dividend
// decrementsestimateONCE;returnhigh0. No signnormalization. Divisor0 reachesCPU DIVfault,noexplicitguard/errno/callback; no allocation,x87,remainderoutput or externalwrites.
unsigned __int64 __stdcall _aulldiv(unsigned __int64 a1, unsigned __int64 a2)
{
  unsigned __int64 v2; // rtt
  unsigned __int64 result; // rax
  unsigned int v4; // ecx
  unsigned int v5; // ebx
  unsigned __int64 v6; // rax
  char v7; // cf
  unsigned int v8; // esi
  unsigned __int64 v9; // rax

  if ( HIDWORD(a2) )
  {
    v4 = HIDWORD(a2);
    v5 = a2;
    v6 = a1;
    do
    {
      v7 = v4 & 1;
      v4 >>= 1;
      v5 = (v5 >> 1) | (v7 << 31);
      v6 >>= 1;
    }
    while ( v4 );
    v8 = v6 / v5;
    v9 = v8 * (unsigned __int64)(unsigned int)a2;
    if ( __CFADD__(HIDWORD(a2) * v8, HIDWORD(v9)) || (HIDWORD(v9) = (a2 * v8) >> 32, v9 > a1) )
      --v8;
    return v8;
  }
  else
  {
    LODWORD(v2) = a1;
    HIDWORD(v2) = HIDWORD(a1) % (unsigned int)a2;
    LODWORD(result) = v2 / (unsigned int)a2;
    HIDWORD(result) = HIDWORD(a1) / (unsigned int)a2;
  }
  return result;
}

