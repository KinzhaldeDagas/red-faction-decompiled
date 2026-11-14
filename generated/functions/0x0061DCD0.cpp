// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061DCD0 __aulldvrm
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Compiler unsigned64 division+remainder: two64 stack
// operands,RET16. Quotient EDX:EAX,remainder EBX:ECX. Corrected full64 return,unsigned divisor,callee cleanup,EBX spoil; secondary result documented here. ESI saved/restored,EDI/EBP
// untouched,EBX intentionally OUTPUT. Inputs read-only. Divisor high0: DIV dividendHigh/divisorLow then DIV remainder:dividendLow yields full64 quotient; multiply it back. High
// divisor nonzero: shift divisor AND dividend logically right until divisor fits32, DIV quotient estimate (high0); multiply estimate by original divisor. Product carry overflow OR
// product>dividend ->decrement estimate ONCE/subtract original divisor from product. Compute product-dividend then64-bit negate for remainder; rearrange registers to two pairs. No
// divisor0 guard (hardware DIV fault),errno,sign adjustments,allocation,FP operations or language overflow handling. Old32-bit return/signed divisor typing lost native information.
unsigned __int64 __userpurge __spoils<eax,ebx,ecx,edx> _aulldvrm@<edx:eax>(unsigned __int64 a1, unsigned __int64 a2)
{
  unsigned int v2; // ebx
  unsigned __int64 v3; // rtt
  unsigned int v4; // esi
  unsigned int v5; // ecx
  unsigned int v6; // ebx
  unsigned __int64 v7; // rax
  char v8; // cf
  unsigned __int64 v9; // rax

  if ( HIDWORD(a2) )
  {
    v5 = HIDWORD(a2);
    v6 = a2;
    v7 = a1;
    do
    {
      v8 = v5 & 1;
      v5 >>= 1;
      v6 = (v6 >> 1) | (v8 << 31);
      v7 >>= 1;
    }
    while ( v5 );
    v4 = v7 / v6;
    v9 = v4 * (unsigned __int64)(unsigned int)a2;
    if ( __CFADD__(HIDWORD(a2) * v4, HIDWORD(v9)) || (HIDWORD(v9) = (a2 * v4) >> 32, v9 > a1) )
      --v4;
    v2 = 0;
  }
  else
  {
    v2 = HIDWORD(a1) / (unsigned int)a2;
    LODWORD(v3) = a1;
    HIDWORD(v3) = HIDWORD(a1) % (unsigned int)a2;
    v4 = v3 / (unsigned int)a2;
  }
  return __PAIR64__(v2, v4);
}

