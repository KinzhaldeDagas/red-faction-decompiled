// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606F30 _floor
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Public floor, ordinary cdecl(double),8 caller-owned
// argument bytes, numeric return ST0. Gate: live DWORD02021F60 nonzero, (snapshotMXCSR&0x1F80)==0x1F80, then (FNSTCW&0x7F)==0x7F. Restore8 gate bytes with LEA preserving final flags.
// Fail ->tail default0x006127A3; accepted ->own SSE2 bit/arithmetic kernel. No complete-default FP-state requirement; MXCSR rounding/DAZ/FTZ/status and x87 precision/rounding ignored
// by this gate. MOVQ loads input bits/zeros high lane. Raw EAX=(bits>>52) includes sign asbit11; AND0x7FF obtains exponent E for vector count=1075-E via packed32 subtraction.
// PSRLQ/PSLLQ use FULL low64 count (>=64 yields0, not count modulo64) and truncate fractional bits. Bins E1023..1074 need integer truncation/correction, E>=1075 already integral or
// special, E<1023 small-magnitude path. Original masks/branch thresholds verified from PE. Nonnegative E<1023 returns+0; nonnegative bins1023..1074 return bit-truncation; larger go
// self-UCOMISD. Negative bins1023..1074 compare original LESS-THAN truncated, mask+1.0, SUBSD from truncation. Negative E<1023 compare with -0, OR sign mask then AND original
// -1-pattern: -0 preserved, negative tiny nonzero ->-1 when comparison treats input nonzero. All E>=1075 use UCOMISD(input,input): ordered (including infinities) ->FLD original
// argument; unordered ->libm_error_support(&argument,&argument,&argument,1005),16 caller-popped bytes, then FLD possibly callback-modified argument. NaN path omitted by old
// simplified pseudocode is present in native bytes. All three pointer arguments alias SAME caller argument slot; selector maps to type1/namefloor, callback0 may set errno33.
// Intermediate CMPNLEPD/CMPLTPD may already affect MXCSR flags for special input. SSE comparisons obey live MXCSR (including DAZ); own kernel never clears/changes MXCSR/CW. Finite
// bit-result proof explicitly assumes DAZ input preservation; do not infer state-independent small-subnormal behavior. Stores update argument image before FLD return; helper
// callbacks/FP operations may throw/trap, no own SEH or environment rollback.
double __cdecl floor(double X)
{
  int v1; // eax
  bool v2; // zf
  __m128i v3; // xmm7
  __m128d v4; // xmm0
  int v5; // eax
  __m128i v6; // xmm2
  __m128i v7; // xmm1
  double v8; // xmm1_8
  __m128d v10; // xmm1
  __m128d v11; // xmm3
  double v12; // xmm0_8
  char v13; // [esp+8h] [ebp-8h]

  if ( !unk_2021F60 )
    return _floor_default(X);
  v1 = _mm_getcsr() & 0x1F80;
  v2 = v1 == 8064;
  if ( v1 == 8064 )
    v2 = (v13 & 0x7F) == 127;
  if ( !v2 )
    return _floor_default(X);
  v3 = _mm_loadl_epi64((const __m128i *)&X);
  v4 = (__m128d)_mm_srli_epi64(v3, 0x34u);
  v5 = _mm_cvtsi128_si32((__m128i)v4);
  v6 = _mm_sub_epi32((__m128i)xmmword_648DC0, (__m128i)_mm_and_pd(v4, (__m128d)xmmword_648DF0));
  v7 = _mm_srl_epi64(v3, v6);
  if ( (v5 & 0x800) != 0 )
  {
    v10 = (__m128d)_mm_sll_epi64(v7, v6);
    v11 = (__m128d)_mm_loadl_epi64((const __m128i *)&X);
    v12 = _mm_cmplt_pd(v11, v10).m128d_f64[0];
    if ( v5 < 3071 )
    {
      *(_QWORD *)&X = *(_QWORD *)&_mm_cmplt_pd(v11, (__m128d)xmmword_648DE0).m128d_f64[0] & 0x3FF0000000000000LL
                    | 0x8000000000000000uLL;
      return X;
    }
    else
    {
      if ( v5 > 3122 )
        return X;
      return v10.m128d_f64[0] - COERCE_DOUBLE(*(_QWORD *)&v12 & 0x3FF0000000000000LL);
    }
  }
  else
  {
    if ( v5 >= 1023 )
    {
      *(_QWORD *)&v8 = v7.m128i_i64[0] << v6.m128i_i8[0];
      if ( v5 <= 1074 )
      {
        X = v8;
        return v8;
      }
      return X;
    }
    return 0.0;
  }
}

