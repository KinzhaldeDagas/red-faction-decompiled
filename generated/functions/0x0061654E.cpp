// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061654E crt_exp_sse2_kernel
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Private optimized kernel: scalar binary64 input in
// low64 of its input XMM register plus matching binary64 backup at entryESP+4; caller bridge supplies both, kernel does not check their consistency. Numeric return x87 ST0; no
// incoming numeric ST0. Incoming upper XMM lanes and other scratch vectors/GPRs are not semantic parameters: native lane-definedness review confirms packed arithmetic initializes
// them before use. No repeat of public CPU/FP admission gate; SSE arithmetic/conversion obeys live MXCSR, including rounding/DAZ/FTZ and exception flags. Original constants/tables
// verified bit-for-bit; comments describe native approximation and compensation order, not a proved public numerical error bound. Existing chunks preserved, no byte patches or
// floating environment rollback if a helper/trap escapes. Input low64 XMM0, duplicate. Main absolute topWORD interval0x3C90..0x408F via unsigned OR of lower/upper differences. Else
// read BACKUP bits: tiny coherent input returns1+backup via SSE; |backup|>=1024 handles finite sign (maxFinite squared ->overflow14, minNormal squared ->underflow15), +infinity
// ->+infinity,-infinity ->+0, NaN ->selector1002. Main quantization: u=K*x+B, K=64*log2(e),B=1.5*2^52, t=u-B, n=signed lowDWORD of u's bits; j=n&63,k=arithmetic n>>6.64 records16
// bytes at64C440: low relative correction L, high mantissa-only bit pattern H (not a numeric denormal coefficient). H OR ((k+1023)<<52) forms scale F. r=x-t*ln2_64Hi-t*ln2_64Lo;
// paired polynomial yields z=r+L+r^4*(Alo*r+Blo)+r^2*(Ahi*r+Bhi), retaining native separate operations. If unsigned(k+894)<=0x77C (k=-894..1022), return F*z+F via scalar binary64
// temporary/FLD. Else18-byte local ADJUST: save x87 CW WORD at+16, load CW|0x300 (preserve other raw fields), split k1=k>>1,k2=k-k1; construct D1 from H fraction and
// exponent(k1+1023),D2=2^k2. In x87 compute (D1*z+D1)*D2, STORE binary64, reload SSE, RESTORE saved CW, reclaim18. Pseudocode omits this real x87 precision/CW protocol. Result
// exponent all-ones ->selector14 overflow; zero exponent (zero OR subnormal) ->selector15 underflow; normal ->return. Error call
// libm_error_support(&backup,&backup,&localResult,selector),28 local bytes incl16 call slots/result, then return callback-modified result. Selector1002 callee overwrites proposed
// result from original NaN before callback. Internal block6166E8..616706 has NO incoming native xrefs and is unreachable from primary entry: it compares raw ECX with80000000/C086232B
// then backup lowDWORD withFEFA39EF, branching to existing return/overflow/underflow labels. Reviewed/preserved as orphan bytes, not a primary input or active threshold guarantee. No
// own SSE-state restoration/finally on traps.
// local variable allocation has failed, the output may be wrong!
long double __usercall crt_exp_sse2_kernel@<st0>(double x@<xmm0>, double originalImage)
{
  __m128d v2; // xmm0
  int v3; // eax
  __m128d v4; // xmm7
  __m128d v5; // xmm1
  int v6; // eax
  int v7; // ecx
  int v8; // eax
  __m128d v9; // xmm0
  __m128d v10; // xmm2
  __m128d v11; // xmm4
  __m128d v12; // xmm0
  __m128d v13; // xmm0
  __m128i v14; // xmm2
  int v16; // edx
  int v17; // eax
  unsigned int v18; // ecx
  int v19; // edx
  unsigned int v20; // eax
  _TBYTE v21; // [esp+10h] [ebp-Ch] BYREF

  v2 = _mm_unpacklo_pd(*(__m128d *)&x, *(__m128d *)&x);
  v3 = _mm_extract_epi16((__m128i)v2, 3) & 0x7FFF;
  if ( ((v3 - 15504) | (unsigned int)(16527 - v3)) < 0x80000000 )
  {
    v4 = _mm_add_pd(_mm_mul_pd((__m128d)xmmword_64C3F0, v2), (__m128d)xmmword_64C3D0);
    v5 = _mm_sub_pd(v4, (__m128d)xmmword_64C3D0);
    v6 = _mm_cvtsi128_si32((__m128i)v4);
    v7 = 16 * (v6 & 0x3F);
    v8 = v6 >> 6;
    v9 = _mm_sub_pd(_mm_sub_pd(v2, _mm_mul_pd((__m128d)xmmword_64C400, v5)), _mm_mul_pd((__m128d)xmmword_64C410, v5));
    v10 = *(__m128d *)(v7 + 6603840);
    v11 = _mm_mul_pd((__m128d)xmmword_64C420, v9);
    v5.m128d_f64[0] = v9.m128d_f64[0];
    v12 = _mm_mul_pd(v9, v9);
    v12.m128d_f64[0] = v12.m128d_f64[0] * v12.m128d_f64[0];
    v13 = _mm_mul_pd(v12, _mm_add_pd((__m128d)xmmword_64C430, v11));
    v5.m128d_f64[0] = v5.m128d_f64[0] + v10.m128d_f64[0] + v13.m128d_f64[0];
    v14 = (__m128i)_mm_or_pd(
                     _mm_unpackhi_pd(v10, v10),
                     (__m128d)_mm_slli_epi64(
                                _mm_add_epi64(
                                  _mm_and_si128((__m128i)v4, _mm_load_si128((const __m128i *)&xmmword_64C3B0)),
                                  _mm_load_si128((const __m128i *)&xmmword_64C3C0)),
                                0x2Eu));
    v2 = _mm_unpackhi_pd(v13, v13);
    v2.m128d_f64[0] = v2.m128d_f64[0] + v5.m128d_f64[0];
    if ( (unsigned int)(v8 + 894) <= 0x77C )
      return v2.m128d_f64[0] * *(double *)v14.m128i_i64 + *(double *)v14.m128i_i64;
    v16 = v8;
    v17 = v8 >> 1;
    *(_QWORD *)((char *)&v21 + 2) = _mm_andnot_si128(_mm_load_si128((const __m128i *)&xmmword_64C3A0), v14).m128i_u64[0]
                                  | (_mm_cvtsi32_si128(v17 + 1023).m128i_u64[0] << 52);
    v2.m128d_f64[0] = (v2.m128d_f64[0] * *(double *)((char *)&v21 + 2) + *(double *)((char *)&v21 + 2))
                    * COERCE_DOUBLE(_mm_cvtsi32_si128(v16 - v17 + 1023).m128i_u64[0] << 52);
    v18 = _mm_extract_epi16((__m128i)v2, 3) & 0x7FF0;
    if ( v18 >= 0x7FF0 )
    {
      v19 = 14;
    }
    else
    {
      if ( v18 )
        goto RETURN_0;
      v19 = 15;
    }
CALL_LIBM_ERROR_0:
    *(double *)&v21 = v2.m128d_f64[0];
    __libm_error_support(&originalImage, &originalImage, (double *)&v21, v19);
    v2.m128d_f64[0] = *(double *)&v21;
RETURN_0:
    *(double *)&v21 = v2.m128d_f64[0];
    return v2.m128d_f64[0];
  }
  v20 = HIDWORD(originalImage) & 0x7FFFFFFF;
  if ( (HIDWORD(originalImage) & 0x7FFFFFFFu) < 0x40900000 )
    return originalImage + 1.0;
  if ( v20 < 0x7FF00000 )
  {
    if ( HIDWORD(originalImage) >= 0x80000000 )
    {
      v2.m128d_f64[0] = 2.225073858507201e-308 * 2.225073858507201e-308;
      v19 = 15;
    }
    else
    {
      v2.m128d_f64[0] = 1.797693134862316e308 * 1.797693134862316e308;
      v19 = 14;
    }
    goto CALL_LIBM_ERROR_0;
  }
  if ( v20 > 0x7FF00000 || LODWORD(originalImage) )
  {
    v19 = 1002;
    goto CALL_LIBM_ERROR_0;
  }
  if ( HIDWORD(originalImage) == 2146435072 )
    return INFINITY;
  else
    return 0.0;
}

