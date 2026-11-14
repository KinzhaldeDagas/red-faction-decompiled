// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00616F0E crt_tan_sse2_kernel
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Private optimized kernel: scalar binary64 input in
// low64 of its input XMM register plus matching binary64 backup at entryESP+4; caller bridge supplies both, kernel does not check their consistency. Numeric return x87 ST0; no
// incoming numeric ST0. Incoming upper XMM lanes and other scratch vectors/GPRs are not semantic parameters: native lane-definedness review confirms packed arithmetic initializes
// them before use. No repeat of public CPU/FP admission gate; SSE arithmetic/conversion obeys live MXCSR, including rounding/DAZ/FTZ and exception flags. Original constants/tables
// verified bit-for-bit; comments describe native approximation and compensation order, not a proved public numerical error bound. Existing chunks preserved, no byte patches or
// floating environment rollback if a helper/trap escapes. Input low64 XMM0. Let w=absolute topWORD,d=WORD(w-0x3820). Main unsigned d<=0x8A8 ->w0x3820..0x40C8. Rejected signed JG
// ->large fallback, otherwise tiny. Main duplicate x; n=CVTSD2SI((32/pi)*x) BEFORE bias operations, MXCSR-rounding sensitive. Row j=(n+0x72900)&31 (same n&31); native shifts/adds
// compute176*j,32 records of11 vector-sized slots at64D1C0. Dual floating grid t=((K*x)+bias)-bias uses DIFFERENT lane biases64E7D0: low1.5*2^56 (coarse16-unit grid), high1.5*2^52
// (fine1-unit grid), not one scalar n. Reduce with lane-specific pi/32 hi/mid/tail constants, compute coarse denominator q=(coarse first
// remainder+tLow*scalarCorrection)&FFFFFFFFFFFC0000, clearing18 low bits. Fine residual is duplicated from high lane. Slots0..7 are paired polynomial coefficients; slot8(+80,+88)
// split base/correction; slot9(+90,+98) paired linear/correction terms; slot10(+A0 scalar factor,+A8 RAW BIT MASK) selects reciprocal contribution: rows9..23 use
// factor1/maskFFFFFFF800000000 for regularized -cot(delta)+1/delta around the pole, other rows factor0/mask0. The mask may encode NaN bits but is used by ANDPD, not as numeric
// coefficient. Native polynomial powers, compensated linear/base sums, residual corrections and masked1/q reciprocal refinement are combined in original ADDSD/SUBSD/MULSD order; no
// scalar-algebra/FMA replacement.16-byte temporary stores result/FLD. Tiny raw exponent0 detected by wrapped d>>4==0xC7E first computes x*2^-55 for status then discards it; all tiny
// paths return (2^55*x+x)*2^-55. Keep sign/status/MXCSR dependence, not a pure identity. Large/Inf/NaN tail public default60A03F, EDX=&backup/fload_withFB then fall through x87 tan
// core60A048; original argument unchanged on own SSE paths. No own callback/errno/CW save.
// local variable allocation has failed, the output may be wrong!
long double __usercall crt_tan_sse2_kernel@<st0>(double x@<xmm0>, double originalImage)
{
  bool v2; // zf
  unsigned int v3; // eax
  long double v4; // st7
  __int16 v5; // ax
  __m128d v6; // xmm0
  __m128d v7; // xmm1
  int v8; // edx
  __m128d v9; // xmm1
  __m128d v10; // xmm4
  __m128d v11; // xmm0
  double v12; // xmm5_8
  __m128d v13; // xmm2
  __m128d v14; // xmm0
  double v15; // xmm3_8
  __m128d *v16; // eax
  __m128d v17; // xmm2
  __m128d v18; // xmm0
  __m128d v19; // xmm7
  __m128d v20; // xmm2
  __m128d v21; // xmm1
  __m128d v22; // xmm4
  __m128d v23; // xmm3
  __m128d v24; // xmm0
  __m128d v25; // xmm7
  __m128d v26; // xmm1
  __m128d v27; // xmm0
  __m128d v28; // xmm4
  __m128d v29; // xmm1
  __m128d v30; // xmm4
  __m128d v31; // xmm7

  v5 = (_mm_extract_epi16(*(__m128i *)&x, 3) & 0x7FFF) - 14368;
  if ( (unsigned __int16)v5 > 0x8A8u )
  {
    if ( v5 > 2216 )
    {
      v4 = _fload_withFB(&originalImage);
      return crt_tan_x87_core(v4, v3, v2, originalImage);
    }
    else
    {
      return (3.602879701896397e16 * x + x) * 2.775557561562891e-17;
    }
  }
  else
  {
    v6 = _mm_unpacklo_pd(*(__m128d *)&x, *(__m128d *)&x);
    v7 = _mm_mul_pd((__m128d)xmmword_64E7C0, v6);
    v8 = (int)v7.m128d_f64[0];
    v9 = _mm_sub_pd(_mm_add_pd(v7, (__m128d)xmmword_64E7D0), (__m128d)xmmword_64E7D0);
    v10 = _mm_mul_pd((__m128d)xmmword_64E7F0, v9);
    v11 = _mm_sub_pd(v6, _mm_mul_pd((__m128d)xmmword_64E7E0, v9));
    v12 = 6.716466596857464e-14 * v9.m128d_f64[0] + v11.m128d_f64[0];
    v13 = v11;
    v14 = _mm_sub_pd(v11, v10);
    *(_QWORD *)&v12 &= 0xFFFFFFFFFFFC0000uLL;
    v15 = v14.m128d_f64[0];
    v16 = (__m128d *)((char *)&unk_64D1C0 + 176 * (v8 & 0x1F));
    v17 = _mm_sub_pd(v13, v14);
    v18 = _mm_unpackhi_pd(v14, v14);
    v19 = _mm_mul_pd(v16[1], v18);
    v20 = _mm_sub_pd(_mm_sub_pd(v17, v10), _mm_mul_pd(v9, (__m128d)xmmword_64E800));
    v21 = _mm_mul_pd(v16[3], v18);
    v22 = _mm_mul_pd(v16[6], v18);
    v20.m128d_f64[0] = v20.m128d_f64[0] + v15 - v12;
    v23 = v18;
    v24 = _mm_mul_pd(v18, v18);
    v25 = _mm_add_pd(_mm_add_pd(v19, *v16), _mm_mul_pd(_mm_add_pd(v21, v16[2]), v24));
    v26 = _mm_mul_pd(v16[7], v24);
    v27 = _mm_mul_pd(v24, v24);
    v28 = _mm_add_pd(_mm_add_pd(v22, v16[5]), v26);
    v29 = _mm_mul_pd(v23, v16[9]);
    v30 = _mm_mul_pd(v28, _mm_mul_pd(v23, v27));
    v23.m128d_f64[0] = v29.m128d_f64[0];
    v31 = _mm_add_pd(_mm_add_pd(v25, _mm_mul_pd(v16[4], v27)), v30);
    v30.m128d_f64[0] = v29.m128d_f64[0];
    v29.m128d_f64[0] = _mm_unpackhi_pd(v29, v29).m128d_f64[0];
    v23.m128d_f64[0] = v23.m128d_f64[0] + v29.m128d_f64[0];
    v29.m128d_f64[0] = v29.m128d_f64[0] + v30.m128d_f64[0] - v23.m128d_f64[0];
    v30.m128d_f64[0] = v20.m128d_f64[0];
    v27.m128d_f64[0] = v27.m128d_f64[0] * v27.m128d_f64[0] * v31.m128d_f64[0]
                     + _mm_unpackhi_pd(v31, v31).m128d_f64[0]
                     + (v16[9].m128d_f64[0] + v16[9].m128d_f64[1]) * _mm_unpackhi_pd(v20, v20).m128d_f64[0]
                     + v16[8].m128d_f64[1]
                     + v29.m128d_f64[0];
    *(_QWORD *)&v20.m128d_f64[0] = COERCE_UNSIGNED_INT64(v16[10].m128d_f64[1]) & COERCE_UNSIGNED_INT64(1.0 / v12);
    return v27.m128d_f64[0]
         + v23.m128d_f64[0]
         - (v20.m128d_f64[0]
          - v16[8].m128d_f64[0]
          + v23.m128d_f64[0]
          - (v20.m128d_f64[0]
           - v16[8].m128d_f64[0]))
         - (1.0 - v12 * v20.m128d_f64[0] - v30.m128d_f64[0] * (1.0 / v12)) * (1.0 / v12 * v16[10].m128d_f64[0])
         + v23.m128d_f64[0]
         - (v20.m128d_f64[0]
          - v16[8].m128d_f64[0]);
  }
}

