// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C5F0 __alldiv
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Compiler helper
// stdcall(signed64dividend,signed64divisor), signed64quotient EDX:EAX,RET16; corrected false32bitreturn/unsigneddividend. PreserveEBX/ESI/EDI. Test signofeachhighDWORD,negate
// negative operands INOWNARGUMENTSTACKslots to unsignedmagnitudes,tracknegativecount. Divisormagnitudehigh0: two unsignedDIVsteps produce full64quotient. Highnonzero: rightshift
// divisoranddividend togetheruntildivisorhigh0,oneDIVestimate fits32; multiplyestimate byoriginaldivisor,ifproductoverflow/exceedsdividend decrementestimateonce,returnhigh0.
// Negate64quotient iffEXACToneinputnegative; truncatestowardzero. Divisor0 reachesCPU DIV fault, no explicitguard/errno/exceptionhandler. INT64_MIN/-1 yields INT64_MIN bitpattern
// through magnitude path, no separate signedoverflowtrap. No remainderoutput or allocation; inputstackmutation not caller-variablemutation.
__int64 __stdcall _alldiv(__int64 a1, __int64 a2)
{
  int v2; // edi
  int v3; // eax
  unsigned __int64 v4; // rtt
  __int64 result; // rax
  unsigned __int64 v6; // rcx
  unsigned __int64 v7; // rax
  unsigned int v8; // esi
  unsigned __int64 v9; // rax

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
    ++v2;
    v3 = -HIDWORD(a2) - ((_DWORD)a2 != 0);
    HIDWORD(a2) = v3;
    LODWORD(a2) = -(int)a2;
  }
  if ( v3 )
  {
    v6 = __PAIR64__(v3, a2);
    v7 = a1;
    do
    {
      v6 >>= 1;
      v7 >>= 1;
    }
    while ( HIDWORD(v6) );
    v8 = v7 / (unsigned int)v6;
    v9 = v8 * (unsigned __int64)(unsigned int)a2;
    if ( __CFADD__(HIDWORD(a2) * v8, HIDWORD(v9)) || (HIDWORD(v9) = (a2 * (unsigned __int64)v8) >> 32, v9 > a1) )
      --v8;
    result = v8;
  }
  else
  {
    LODWORD(v4) = a1;
    HIDWORD(v4) = HIDWORD(a1) % (unsigned int)a2;
    LODWORD(result) = v4 / (unsigned int)a2;
    HIDWORD(result) = HIDWORD(a1) / (unsigned int)a2;
  }
  if ( v2 == 1 )
    return -result;
  return result;
}

