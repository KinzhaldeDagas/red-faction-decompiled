// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062001A ___mtold12
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(const signed numericDigitBytes*,UNSIGNED
// count,output12*), returns output pointer. Zero all12 output bytes FIRST, before reading source. Accumulate96-bit unsigned value by10*N+digit for intended digits0..9, with explicit
// DWORD carry propagation; source bytes are NUMERIC values, NOT ASCII (no subtraction of '0', no terminator scan). Native loads each byte SIGN-EXTENDED to32, adds to lowDWORD with
// unsigned carry checks; invalid negative bytes are not full96-bit signed additions. Count test/decrement is UNSIGNED; negative-looking32-bit count is huge. All arithmetic truncates
// modulo2^96, no magnitude/digit/count validation. Initial exponentWORD404E (=16383+79); while highDWORD==0 shift accumulator left16 and subtract16 from exponent. Then while
// highDWORD mask8000 clear shift96 left1/decrement exponent. Store LOW WORD exponent into output+10, replacing high16 bits of accumulator; low80 bits form significand. Valid positive
// N<2^80 becomes exact positive packed80-significand extended value. NO ZERO EXIT: count0, allzero digits or wrapped-zero accumulator loops forever in normalization. No sign parsing,
// allocation, rounding, source/output alias handling, own errno/invalid handler or FP instructions; source overlapping output can be destroyed by initial zeroing. Cookie checked only
// on returning path.
_DWORD *__cdecl __mtold12(const signed __int8 *a1, unsigned int a2, _DWORD *a3)
{
  _DWORD *result; // eax
  int v4; // ecx
  unsigned int v5; // ebx
  unsigned int v6; // esi
  unsigned int v7; // edx
  unsigned int v8; // edi
  int v9; // ebx
  unsigned int v10; // ecx
  unsigned int v11; // ebx
  int v12; // esi
  unsigned int v13; // ecx
  unsigned int v14; // edi
  int v15; // ebx
  unsigned int v16; // edx
  unsigned int v17; // esi
  int v18; // edx
  unsigned int v19; // ecx
  unsigned __int64 v20; // kr00_8
  unsigned int v21; // esi
  unsigned int v22; // edi
  int v23; // ecx
  __int16 v24; // [esp+Ch] [ebp-18h]
  int v25; // [esp+10h] [ebp-14h]
  int v26; // [esp+10h] [ebp-14h]
  unsigned int v27; // [esp+18h] [ebp-Ch]
  int v28; // [esp+1Ch] [ebp-8h]

  result = a3;
  v24 = 16462;
  *a3 = 0;
  a3[1] = 0;
  for ( a3[2] = 0; a2; ++a1 )
  {
    v27 = a3[1];
    v28 = a3[2];
    v25 = 0;
    v4 = __SPAIR64__(*(_QWORD *)(a3 + 1) >> 31, *(__int64 *)a3 >> 31) >> 31;
    v5 = *a3;
    v6 = 4 * *a3;
    v7 = (2LL * *(_QWORD *)a3) >> 31;
    v8 = 5 * *a3;
    *a3 = v6;
    a3[1] = v7;
    a3[2] = v4;
    if ( v8 < v6 || v8 < v5 )
      v25 = 1;
    v9 = 0;
    *a3 = v8;
    if ( v25 )
    {
      if ( v7 + 1 < v7 || v7 == -1 )
        v9 = 1;
      a3[1] = v7 + 1;
      if ( v9 )
        a3[2] = v4 + 1;
    }
    v10 = a3[1];
    v11 = v10 + v27;
    v12 = 0;
    if ( v10 + v27 < v10 || v11 < v27 )
      v12 = 1;
    a3[1] = v11;
    if ( v12 )
      ++a3[2];
    a3[2] += v28;
    v26 = 0;
    v13 = 2 * v8;
    v14 = (v8 >> 31) | (2 * v11);
    v15 = (v11 >> 31) | (2 * a3[2]);
    *a3 = v13;
    a3[1] = v14;
    a3[2] = v15;
    v16 = *a1;
    v17 = v13 + v16;
    if ( v13 + v16 < v13 || v17 < v16 )
      v26 = 1;
    *a3 = v17;
    if ( v26 )
    {
      v18 = 0;
      if ( v14 + 1 < v14 || v14 == -1 )
        v18 = 1;
      a3[1] = v14 + 1;
      if ( v18 )
        a3[2] = v15 + 1;
    }
    --a2;
  }
  while ( !a3[2] )
  {
    v19 = a3[1];
    a3[2] = HIWORD(v19);
    v20 = (unsigned __int64)(unsigned int)*a3 << 16;
    v24 -= 16;
    a3[1] = __SPAIR64__(v19, *a3) >> 16;
    *a3 = v20;
  }
  if ( (a3[2] & 0x8000) == 0 )
  {
    do
    {
      v21 = *a3;
      v22 = a3[1];
      --v24;
      *a3 *= 2;
      v23 = (v22 >> 31) | (2 * a3[2]);
      a3[1] = (v21 >> 31) | (2 * v22);
      a3[2] = v23;
    }
    while ( (v23 & 0x8000) == 0 );
  }
  *((_WORD *)a3 + 5) = v24;
  return result;
}

