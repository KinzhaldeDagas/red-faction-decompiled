// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D220 __alldvrm
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Compiler signed64 division+remainder helper. Two
// stack64 arguments dividend/divisor, RET16; quotient EDX:EAX, remainder EBX:ECX. Corrected ABI declares64 quotient, signed inputs, callee stack cleanup and EBX spoil; secondary
// remainder remains documented here. Preserve EDI/ESI/EBP; EBX is intentionally OUTPUT, not preserved. Negate negative operands IN THEIR STACK COPIES using64-bit two's complement;
// keep quotient sign parity and ORIGINAL dividend sign. Divisor magnitude highDWORD0: two unsigned32 DIVs yield full64 quotient. Otherwise shift BOTH magnitudes right until divisor
// fits32, DIV estimate, multiply estimate by original divisor; if product overflow or product>dividend, decrement estimate once and subtract divisor from product; quotient high0.
// Form remainder magnitude from product-dividend and conditionally negate so result remainder sign matches original dividend. Apply quotient sign iff exactly one operand negative. No
// divisor0 guard (hardware DIV fault), errno, allocation, floating operations or signed-overflow trap. INT64_MIN/-1 returns wrapped INT64_MIN quotient/remainder0 via
// unsigned-magnitude algorithm. Raw input slots left as magnitudes; quotient truncates toward zero for representable results.
__int64 __userpurge __spoils<eax,ebx,ecx,edx> _alldvrm@<edx:eax>(__int64 a1, __int64 a2)
{
  int v2; // edi
  int v3; // eax
  unsigned int v4; // ebx
  unsigned __int64 v5; // rtt
  unsigned int v6; // esi
  unsigned __int64 v7; // rcx
  unsigned __int64 v8; // rax
  unsigned __int64 v9; // rax
  __int64 result; // rax

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
    v7 = __PAIR64__(v3, a2);
    v8 = a1;
    do
    {
      v7 >>= 1;
      v8 >>= 1;
    }
    while ( HIDWORD(v7) );
    v6 = v8 / (unsigned int)v7;
    v9 = v6 * (unsigned __int64)(unsigned int)a2;
    if ( __CFADD__(HIDWORD(a2) * v6, HIDWORD(v9)) || (HIDWORD(v9) = (a2 * (unsigned __int64)v6) >> 32, v9 > a1) )
      --v6;
    v4 = 0;
  }
  else
  {
    v4 = HIDWORD(a1) / (unsigned int)a2;
    LODWORD(v5) = a1;
    HIDWORD(v5) = HIDWORD(a1) % (unsigned int)a2;
    v6 = v5 / (unsigned int)a2;
  }
  result = __PAIR64__(v4, v6);
  if ( v2 == 1 )
  {
    LODWORD(result) = -v6;
    HIDWORD(result) = -v4 - (v6 != 0);
  }
  return result;
}

