// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00616C9E crt_log_sse2_kernel
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Private optimized kernel: scalar binary64 input in
// low64 of its input XMM register plus matching binary64 backup at entryESP+4; caller bridge supplies both, kernel does not check their consistency. Numeric return x87 ST0; no
// incoming numeric ST0. Incoming upper XMM lanes and other scratch vectors/GPRs are not semantic parameters: native lane-definedness review confirms packed arithmetic initializes
// them before use. No repeat of public CPU/FP admission gate; SSE arithmetic/conversion obeys live MXCSR, including rounding/DAZ/FTZ and exception flags. Original constants/tables
// verified bit-for-bit; comments describe native approximation and compensation order, not a proved public numerical error bound. Existing chunks preserved, no byte patches or
// floating environment rollback if a helper/trap escapes. Input low64 XMM0; EDX scale adjustment starts0. BEFORE sign/exponent validation, normalize raw mantissa to y in[1,2) using
// mask64C8C0/OR1.0. Add original bias64C8D0; lowWORD&0x7F0 forms16-byte table offset, actually0..0x400 (65 rows under original constants/all rounding modes). Reciprocal table64C9A0
// contains equal-lane quantized R; split-log table64CDB0 stores -ln(R) hi/lo. Split y into Yh (mask64C8E0) and Yl; h=Yh*R-1,l=Yl*R,z=h+l. Raw sign/exponent field
// ecx=((bits>>52)&0xFFF)-1. Positive normal0<=ecx<=0x7FD ->K=ecx-1022+adjustment. Combine split table log, h, K*split ln2, and masked l; mask selector16 only if
// (K<<10)+tableOffset==0 (K0/row0 or K-1/row64 near1), else0; coefficient pairs64C970/80/90 generate remaining z^2/z^5 polynomial lanes and compensated scalar sum.16-byte output
// temporary, FLD,return. Special path uses floating CMPEQ with backup and zero FIRST: both signed zeros (or DAZ-zeroed subnormals) generate1/input for status, propose
// -infinity,selector2. Positive subnormal ecxFFFFFFFF scales backup by2^52,sets adjustment-52,retries from616CA3 (does not reset adjustment). Positive infinity normalized fraction0
// returns+infinity; positive NaN selector1000. Negative finite/-infinity generate0/0 NaN,selector3; negative NaN identified by both fraction parts,selector1000. Callback
// libm_error_support(&backup,&backup,&localResult,selector) uses28 local bytes and returns modified result;1000 copies original into output first. No incoming XMM2/EDX numeric
// parameter, raw-input consistency check, direct errno/CW write or SEH. Native preliminary table arithmetic/status and floating zero comparison remain present even for rejected
// input.
// local variable allocation has failed, the output may be wrong!
long double __usercall crt_log_sse2_kernel@<st0>(double x@<xmm0>, double originalImage)
{
  __m128i v2; // xmm2
  int i; // edx
  __m128i v4; // xmm5
  __m128d v5; // xmm0
  int v6; // eax
  __m128d v7; // xmm4
  __m128d v8; // xmm6
  __m128d v9; // xmm0
  __m128d v10; // xmm6
  __m128d v11; // xmm7
  __m128d v12; // xmm4
  unsigned int v13; // ecx
  int v14; // ecx
  __m128d v15; // xmm6
  int v16; // edx
  __m128d v17; // xmm3
  __m128d v18; // xmm7
  __m128d v19; // xmm0
  __m128d v21; // xmm0
  __m128i v22; // xmm1
  __m128d v23; // xmm0
  int v24; // edx
  long double v25; // [esp+10h] [ebp-Ch] BYREF

  for ( i = 0; ; i = -52 )
  {
    v4 = *(__m128i *)&x;
    v5 = _mm_or_pd(
           _mm_and_pd(_mm_unpacklo_pd(*(__m128d *)&x, *(__m128d *)&x), (__m128d)xmmword_64C8C0),
           (__m128d)xmmword_64C920);
    v6 = _mm_extract_epi16((__m128i)_mm_add_pd((__m128d)xmmword_64C8D0, v5), 0) & 0x7F0;
    v7 = *(__m128d *)(v6 + 6605216);
    v11 = *(__m128d *)(v6 + 6606256);
    v8 = _mm_and_pd((__m128d)xmmword_64C8E0, v5);
    v9 = _mm_sub_pd(v5, v8);
    v10 = _mm_sub_pd(_mm_mul_pd(v8, v7), (__m128d)xmmword_64C920);
    v11.m128d_f64[0] = v11.m128d_f64[0] + v10.m128d_f64[0];
    v12 = _mm_mul_pd(v9, v7);
    *(__m128d *)&x = _mm_add_pd(v12, v10);
    v13 = (_mm_extract_epi16(_mm_srli_epi64(v4, 0x34u), 0) & 0xFFF) - 1;
    if ( v13 <= 0x7FD )
      break;
    v21.m128d_f64[0] = originalImage;
    v22 = (__m128i)_mm_cmpeq_sd((__m128d)xmmword_64C930, v21);
    if ( _mm_extract_epi16(v22, 0) )
    {
      *(double *)v22.m128i_i64 = -INFINITY;
      v24 = 2;
CALL_LIBM_ERROR_1:
      v25 = *(double *)v22.m128i_i64;
      __libm_error_support(&originalImage, &originalImage, &v25, v24);
      return v25;
    }
    if ( v13 != -1 )
    {
      if ( v13 > 0x7FE )
      {
        if ( (((_WORD)v13 + 1) & 0x7FFu) >= 0x7FF
          && (*(double *)v2.m128i_i64 = originalImage,
              _mm_cvtsi128_si32(_mm_srli_epi64(v2, 0x20u)) & 0xFFFFF | _mm_cvtsi128_si32(v2)) )
        {
          v24 = 1000;
        }
        else
        {
          *(double *)v22.m128i_i64 = 0.0 / 0.0;
          v24 = 3;
        }
      }
      else
      {
        v23.m128d_f64[0] = originalImage;
        v22.m128i_i64[0] = 0xFFFFFFFFFFFFFLL;
        if ( _mm_extract_epi16(
               (__m128i)_mm_cmpeq_sd(
                          (__m128d)xmmword_64C920,
                          _mm_or_pd(_mm_and_pd(v23, (__m128d)xmmword_64C8C0), (__m128d)xmmword_64C920)),
               0) )
        {
          return INFINITY;
        }
        v24 = 1000;
      }
      goto CALL_LIBM_ERROR_1;
    }
    x = originalImage * 4.503599627370496e15;
  }
  v14 = i + v13 - 1022;
  v10.m128d_f64[0] = (double)v14;
  v15 = _mm_unpacklo_pd(v10, v10);
  v16 = 0;
  if ( !((v14 << 10) + v6) )
    v16 = 16;
  v17 = _mm_mul_pd(*(__m128d *)&x, *(__m128d *)&x);
  v18 = _mm_add_pd(
          _mm_add_pd(v11, _mm_mul_pd(v15, (__m128d)xmmword_64C8F0)),
          _mm_and_pd(v12, *(__m128d *)(v16 + 6605056)));
  v17.m128d_f64[0] = v17.m128d_f64[0] * v17.m128d_f64[0] * x;
  v19 = _mm_mul_pd(
          _mm_add_pd(
            _mm_mul_pd(
              _mm_add_pd(_mm_mul_pd((__m128d)xmmword_64C970, *(__m128d *)&x), (__m128d)xmmword_64C980),
              *(__m128d *)&x),
            (__m128d)xmmword_64C990),
          v17);
  return v19.m128d_f64[0]
       + _mm_unpackhi_pd(v19, v19).m128d_f64[0]
       + _mm_unpackhi_pd(v18, v18).m128d_f64[0]
       + v18.m128d_f64[0];
}

