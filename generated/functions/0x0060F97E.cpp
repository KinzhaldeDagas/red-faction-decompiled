// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F97E crt_cos_sse2_kernel
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Private optimized kernel: scalar binary64 input in
// low64 of its input XMM register plus matching binary64 backup at entryESP+4; caller bridge supplies both, kernel does not check their consistency. Numeric return x87 ST0; no
// incoming numeric ST0. Incoming upper XMM lanes and other scratch vectors/GPRs are not semantic parameters: native lane-definedness review confirms packed arithmetic initializes
// them before use. No repeat of public CPU/FP admission gate; SSE arithmetic/conversion obeys live MXCSR, including rounding/DAZ/FTZ and exception flags. Original constants/tables
// verified bit-for-bit; comments describe native approximation and compensation order, not a proved public numerical error bound. Existing chunks preserved, no byte patches or
// floating environment rollback if a helper/trap escapes. Input low64 XMM0. Let w=absolute input topWORD, d=WORD(w-0x3030). Unsigned d<=0x10C5 selects main range (w0x3030..0x40F5).
// Rejected d then signed JG selects large fallback when w>=0x40F6; w<0x3030 takes tiny path. Main: K=32/pi constant, n=CVTSD2SI(K*x) (MXCSR rounding, NOT C truncation); independently
// t=((K*x)+B)-B with original B=1.5*2^52. Do not conflate integer n with floating t in non-nearest modes. Row index=(n+0x1C7610)&63, byte offset32*index;64 records at0x006490D0. Each
// row four binary64 words cFine,sHi,sLo,cCoarse: sHi+sLo approximates sin(j*pi/32),cFine+cCoarse approximates cos(j*pi/32). Cos shifts phase+16; sin phase+0. Both tables are
// byte-identical. Reduce r1=x-t*pi32Hi, r=r1-t*pi32Mid; tail correction e=t*pi32Tail-((r1-r)-t*pi32Mid). Packed coefficient pairs at0x006498D0 implement sine/cosine residual
// corrections (nominal r^3/r^2 terms using r^2,r^4 and mixed r1*r term). Row cosine is split for r*cFine and r*cCoarse; sHi/sLo, residual e and both polynomial lanes are accumulated
// through the exact compensated ADDSD/SUBSD sequence, then16-byte local scalar store/FLD/ADD16/RET. No FMA or algebraic reordering assumed. Tiny path clears vector input sign via
// PINSRW and returns verified1.0-|x| through binary64 temporary; this generates live rounding/inexact behavior, not a hardcoded unconditional1. Large/Inf/NaN path tail-JMP public
// default entry60625F: EDX=&backup, fload_withFB, then fall through x87 cos core606268 with loader EAX/ZF/ST0. Original backup remains unchanged on own SSE paths.
// local variable allocation has failed, the output may be wrong!
long double __usercall crt_cos_sse2_kernel@<st0>(double x@<xmm0>, double originalImage)
{
  bool v2; // zf
  unsigned int v3; // eax
  long double v4; // st7
  __m128d v5; // xmm1
  __int16 v6; // ax
  double v7; // xmm3_8
  __m128d v8; // xmm1
  double *v10; // eax
  __m128d v11; // xmm2
  __m128d v12; // xmm0
  __m128d v13; // xmm0
  double v14; // xmm3_8
  double v15; // xmm4_8
  __m128d v16; // xmm5
  __m128d v17; // xmm0
  double v18; // xmm7_8
  __m128d v19; // xmm5
  __m128d v20; // xmm0
  double v21; // xmm3_8
  __m128d v22; // xmm2
  double v23; // xmm3_8
  double v24; // xmm7_8
  __m128d v25; // xmm6
  __m128d v26; // xmm2
  __m128d v27; // xmm5
  double v28; // xmm3_8
  __m128d v29; // xmm6
  unsigned int epi16; // eax

  v6 = (_mm_extract_epi16(*(__m128i *)&x, 3) & 0x7FFF) - 12336;
  if ( (unsigned __int16)v6 > 0x10C5u )
  {
    if ( v6 > 4293 )
    {
      v4 = _fload_withFB(&originalImage);
      return crt_cos_x87_core(v4, v3, v2, originalImage);
    }
    else
    {
      epi16 = _mm_extract_epi16(*(__m128i *)&x, 3);
      LOWORD(epi16) = epi16 & 0x7FFF;
      return 1.0 - *(double *)_mm_insert_epi16(*(__m128i *)&x, epi16, 3).m128i_i64;
    }
  }
  else
  {
    v5.m128d_f64[0] = 10.1859163578813 * x + 6.755399441055744e15 - 6.755399441055744e15;
    v7 = 0.09817477042088285 * v5.m128d_f64[0];
    v8 = _mm_unpacklo_pd(v5, v5);
    v10 = (double *)((char *)&unk_6490D0 + 32 * (((unsigned __int8)(int)(10.1859163578813 * x) + 16) & 0x3F));
    v11 = _mm_mul_pd((__m128d)xmmword_649920, v8);
    v12.m128d_f64[0] = x - v7;
    v13 = _mm_unpacklo_pd(v12, v12);
    v14 = x - v7;
    v15 = v14 - v11.m128d_f64[0];
    v16 = _mm_mul_pd((__m128d)xmmword_649900, v13);
    v17 = _mm_sub_pd(v13, v11);
    v18 = v10[1] * (v14 - v11.m128d_f64[0]);
    v19 = _mm_mul_pd(v16, v17);
    v20 = _mm_mul_pd(v17, v17);
    v21 = v14 - (v14 - v11.m128d_f64[0]) - v11.m128d_f64[0];
    v22 = *(__m128d *)v10;
    v8.m128d_f64[0] = v8.m128d_f64[0] * 1.263916405497469e-22 - v21;
    v23 = v10[3];
    v22.m128d_f64[0] = *v10 + v23;
    v24 = v18 - v22.m128d_f64[0];
    v22.m128d_f64[0] = v22.m128d_f64[0] * v15;
    v25 = _mm_mul_pd((__m128d)xmmword_6498E0, v20);
    v26 = _mm_mul_pd(v22, v20);
    v27 = _mm_mul_pd(_mm_add_pd(v19, (__m128d)xmmword_6498F0), _mm_mul_pd(v20, v20));
    v20.m128d_f64[0] = v23 * v15;
    v28 = v20.m128d_f64[0] + v10[1];
    v29 = _mm_mul_pd(_mm_add_pd(_mm_add_pd(v25, (__m128d)xmmword_6498D0), v27), v26);
    return v15 * *v10
         + v28
         + v8.m128d_f64[0] * v24
         + v10[2]
         + v10[1]
         - v28
         + v20.m128d_f64[0]
         + v28
         - (v15 * *v10
          + v28)
         + v15 * *v10
         + v29.m128d_f64[0]
         + _mm_unpackhi_pd(v29, v29).m128d_f64[0];
  }
}

