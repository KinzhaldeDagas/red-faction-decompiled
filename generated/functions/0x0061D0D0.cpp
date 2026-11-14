// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D0D0 ___dtold
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(output10bytes,binary64Pointer), returns
// original output. Pure integer exact binary64-to-x87-extended80 representation conversion, no x87 instructions. Capture sign from inputWORD+6 mask8000; exponent=(WORD+6>>4)&7FF;
// fraction=input64&FFFFFFFFFFFFF. Signed zero -> significand64zero, exponentWORD=sign. Normal finite -> extended exponent=encodedExponent+3C00, significand=(1<<63)|(fraction<<11).
// Exponent7FF -> extended exponent7FFF and same explicit integer bit/fraction payload shift, preserving NaN payload/quiet bit without separate quieting. Nonzero subnormal ->
// tentative exponent3C01, significand=fraction<<11, repeatedly shift64left and decrement LOW WORD exponent until bit63 set. Store64 significand at output0..7, sign|exponent WORD at8;
// exactly10 bytes, no padding writes. Reads all required source before destination writes, allowing exact input/output alias. No NULL/alignment/size validation, errno, rounding,
// FP-status update, helper call or invalid handler.
int *__cdecl __dtold(int *a1, int *a2)
{
  int v3; // ecx
  int v4; // eax
  unsigned int v5; // edx
  int v6; // eax
  __int16 v7; // cx
  __int16 v8; // di
  int *result; // eax
  __int16 v10; // cx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  unsigned int v14; // [esp+Ch] [ebp-4h]
  __int16 v15; // [esp+1Ch] [ebp+Ch]

  v3 = (*((unsigned __int16 *)a2 + 3) >> 4) & 0x7FF;
  v15 = *((_WORD *)a2 + 3) & 0x8000;
  v4 = a2[1];
  v5 = *a2;
  v6 = v4 & 0xFFFFF;
  v14 = 0x80000000;
  if ( !(_WORD)v3 )
  {
    if ( !v6 && !v5 )
    {
      result = a1;
      v10 = v15;
      a1[1] = 0;
      *a1 = 0;
      goto LABEL_13;
    }
    v7 = 15361;
    v14 = 0;
    goto LABEL_9;
  }
  if ( (unsigned __int16)v3 != 2047 )
  {
    v7 = v3 + 15360;
LABEL_9:
    v8 = v7;
    goto LABEL_10;
  }
  v8 = 0x7FFF;
LABEL_10:
  v11 = v14 | (v6 << 11) | (v5 >> 21);
  result = a1;
  a1[1] = v11;
  *a1 = v5 << 11;
  if ( (v11 & 0x80000000) == 0 )
  {
    do
    {
      v12 = *(__int64 *)a1 >> 31;
      v13 = 2 * *a1;
      --v8;
      a1[1] = v12;
      *a1 = v13;
    }
    while ( (v12 & 0x80000000) == 0 );
  }
  v10 = v8 | v15;
LABEL_13:
  *((_WORD *)result + 4) = v10;
  return result;
}

