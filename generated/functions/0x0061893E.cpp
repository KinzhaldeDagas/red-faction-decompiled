// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061893E crt_asin_sse2_kernel
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Private SSE2 asin kernel: scalar binary64 x in low64
// XMM0 plus matching binary64 originalImage at entryESP+4; public/intrinsic bridge supplies both, consistency is not checked. Other XMM/GPR scratch values and high incoming lanes are
// not semantic arguments; duplicated packed paths initialize their arithmetic lanes before use. Every numeric return is FLD of a binary64 local; no incoming ST0. Existing
// frame/chunks retained. No repeated public CPU/FP admission gate or own MXCSR/CW save: native SSE operations obey live rounding, DAZ/FTZ and exception state. No numerical
// error-bound or replacement-equivalence claim. Let q=(raw(x)>>44)&0x7FFFF. Native unsigned wraparound guards partition q: main3FB00..3FEBA; upper-table3FEBB..3FEFD; small
// polynomial3C300..3FAFF; endpoint polynomial3FEFE..3FEFF; tiny0..3C2FF; unit/domain/NaN3FF00..7FFFF. Thus main abs interval[1/16,443/512), upper[443/512,255/256),
// endpoint[255/256,1), small[2^-60,1/16), tiny<2^-60. Main computes s=SQRTSD(1-x*x), signed center c=(raw(x)&0xFFFFC00000000000)|0x0000200000000000 and
// j=((raw(x)>>46)&0x3FFF)-0x3EC0, equivalent native masked low16/4 index0..238. 240 paired records: angle low/high at64E960+16*j approximates asin(abs(c)); positive companion
// at64F860+8*j approximates sqrt(1-c*c). Center j has raw positive bits(0x3FB02+4*j)<<44. XOR angle lanes by center sign. r=x*companion-s*c, independently quotient
// t=(x-c)*(x+c)/(x*companion+s*c); ideal identities do not license native algebraic reordering. Accumulate t, signed table low/high and r^3*(1/6+r^2*(3/40+r^2*5/112)) in original
// scalar order. Upper-table path uses a=abs(x), ah=raw(a)&0x7FFFFFC000000000, al=a-ah; s=SQRTSD(1-x*x), center c from s using the same coarse mask/midpoint.
// j=((raw(s)>>46)&0xFFFF)-0xFEC0, independently bounded26..192 under all rounding directions. r=ah*c-s*companion+al*c, h=1-ah*ah-c*c-(a+ah)*al, t=h/(2*s*companion+r). Base is
// componentwise pi/2 split minus table asin(c). Add residual polynomial, subtract t, add second base component, then OR original input sign. Preserve compensated split operations and
// division order. Small path duplicates x, forms x^2/x^4 and paired coefficients6500B0/C0/D0; low lane x^9*(C0.low+B0.low*x^2+D0.low*x^4), high lane
// x^3*(C0.high+B0.high*x^2+D0.high*x^4), sum lanes then x. Coefficients are stored binary64 approximations of positive asin series coefficients through degree13. Endpoint path first
// forms s=SQRTSD(1-x*x), splits x and s with raw mask0xFFFFFFFFF8000000 clearing27 low bits, and constructs h=(1-xHi^2-2*xHi*xLo-sHi^2-xLo^2)+(2*s+(sHi-s))*(sHi-s). Divide h by2*s
// for the correction. Evaluate paired residual polynomial in s through degree13 plus the separate positive native term s^15*(6500E0.high+6500E0.low*s^2); combine pi/2 low, that term,
// polynomial/correction and a compensated subtraction of s around pi/2 high; OR original sign. Do not turn this native signed accumulation into an assumed Taylor identity.
// Unit/domain dispatch tests exact abs vector bits1.0 first: add original pi/2 low/high and OR original sign, no libm call. Otherwise classify absolute BACKUP bits by
// subtract0x7FF0000000000001 with SBB and signed high comparison: NaN backup proposes originalImage+0 and selector1009; finite domain/Inf proposes0*+Inf (invalid) and selector61. 28
// local bytes contain four C call arguments and proposed/result DOUBLE: __libm_error_support(&originalImage,&originalImage,&localResult,selector), then return helper-updated binary64
// result. Backup and vector are deliberately distinct sources. Tiny path reloads originalImage. Raw exponent1..2046 returns that binary64 unchanged. Exponent0/2047 path computes
// zero+backup, ORs sum bits into backup, and performs a discarded multiplication backup*modifiedBackup for floating status before returning the ORed scalar; this includes normal
// coherent zero/subnormal inputs. Preserve negative-zero sign/DAZ/FTZ/exception-sensitive operations instead of erasing them as an identity.
// local variable allocation has failed, the output may be wrong!
double __usercall crt_asin_sse2_kernel@<st0>(double x@<xmm0>, double originalImage)
{
  __m128d v2; // xmm1
  __m128d v3; // xmm2
  __m128i v4; // xmm3
  __m128d v5; // xmm7
  int v6; // edx
  __m128d inserted; // xmm5
  __m128i v8; // xmm0
  int v9; // edx
  __m128i v10; // xmm2
  double v11; // xmm3_8
  double v12; // xmm1_8
  double v13; // xmm0_8
  double v14; // xmm3_8
  __m128i v15; // xmm4
  double result; // st7
  unsigned int v17; // eax
  char v18; // al
  double v19; // xmm0_8
  __int64 v20; // xmm6_8
  double v21; // xmm1_8
  double v22; // xmm4_8
  double v23; // xmm0_8
  double v24; // xmm2_8
  int v25; // edx
  double v26; // xmm7_8
  double v27; // xmm6_8
  __m128i v28; // xmm3
  unsigned int v29; // eax
  __m128d v30; // xmm7
  __m128d v31; // xmm1
  __m128d v32; // xmm7
  __m128d v33; // xmm1
  __m128i v34; // xmm1
  unsigned int v35; // eax
  unsigned __int16 epi16; // ax
  __m128i v37; // xmm5
  double v38; // xmm0_8
  double v39; // xmm6_8
  double v40; // xmm3_8
  double v41; // xmm6_8
  double v42; // xmm4_8
  __m128i v43; // xmm3
  __m128d v44; // xmm7
  double v45; // xmm4_8
  __m128d v46; // xmm6
  double v47; // xmm4_8
  __m128i v48; // xmm1
  __m128d v49; // xmm7
  __m128d v50; // xmm2
  __m128i v51; // xmm7
  double v52; // xmm0_8
  int v53; // edx
  double v54; // [esp+10h] [ebp-Ch] BYREF

  v3.m128d_f64[0] = NAN;
  v2.m128d_f64[0] = x;
  v8 = _mm_srli_epi64(*(__m128i *)&x, 0x2Cu);
  v6 = _mm_cvtsi128_si32(v8);
  v5.m128d_f64[0] = v2.m128d_f64[0];
  inserted = (__m128d)_mm_insert_epi16((__m128i)0LL, 0x2000u, 2);
  *(double *)v8.m128i_i64 = v2.m128d_f64[0];
  if ( (v6 & 0x7FFFFu) - 260864 >= 0x3BB )
  {
    v17 = (v6 & 0x7FFFF) - 261819;
    if ( v17 >= 0x43 )
    {
      v29 = v17 + 15291;
      if ( v29 >= 0x3800 )
      {
        v35 = v29 - 15358;
        if ( v35 >= 2 )
        {
          if ( v35 + 261886 < 0x3FF00 )
          {
            *(double *)v8.m128i_i64 = originalImage;
            if ( (_mm_extract_epi16(v8, 3) & 0x7FF0u) - 16 >= 0x7FE0 )
              v8.m128i_i64[0] = *(_QWORD *)&originalImage | COERCE_UNSIGNED_INT64(originalImage + 0.0);
            return *(double *)v8.m128i_i64;
          }
          else if ( _mm_cvtsi128_si32(v8) | (1072693248 - (_mm_cvtsi128_si32(_mm_srli_epi64(v8, 0x20u)) & 0x7FFFFFFF)) )
          {
            v3.m128d_f64[0] = originalImage;
            if ( (((__PAIR64__(
                      _mm_cvtsi128_si32(_mm_srli_epi64((__m128i)v3, 0x20u)) & 0x7FFFFFFF,
                      _mm_cvtsi128_si32((__m128i)v3))
                  - 0x7FF0000000000001LL) >> 32)
                & 0x80000000) == 0LL )
            {
              v52 = originalImage + 0.0;
              v53 = 1009;
            }
            else
            {
              v52 = 0.0 * *(double *)_mm_insert_epi16((__m128i)0LL, 0x7FF0u, 3).m128i_i64;
              v53 = 61;
            }
            v54 = v52;
            __libm_error_support(&originalImage, &originalImage, &v54, v53);
            return v54;
          }
          else
          {
            *(_QWORD *)&result = COERCE_UNSIGNED_INT64(6.123233995736766e-17 + 1.570796326794897)
                               | ~COERCE__INT64(NAN) & *(_QWORD *)&v2.m128d_f64[0];
          }
        }
        else
        {
          *(double *)v4.m128i_i64 = sqrt(1.0 - v2.m128d_f64[0] * v2.m128d_f64[0]);
          epi16 = _mm_extract_epi16((__m128i)v5, 3);
          v37 = _mm_shuffle_epi32(v4, 68);
          v38 = v2.m128d_f64[0] - COERCE_DOUBLE(*(_QWORD *)&v2.m128d_f64[0] & 0xFFFFFFFFF8000000uLL);
          *(_QWORD *)&v39 = v4.m128i_i64[0] & 0xFFFFFFFFF8000000uLL;
          v40 = v39 * v39;
          v41 = v39 - *(double *)v37.m128i_i64;
          *(double *)v37.m128i_i64 = *(double *)v37.m128i_i64 + *(double *)v37.m128i_i64;
          v42 = 1.0
              - COERCE_DOUBLE(*(_QWORD *)&v2.m128d_f64[0] & 0xFFFFFFFFF8000000uLL)
              * COERCE_DOUBLE(*(_QWORD *)&v2.m128d_f64[0] & 0xFFFFFFFFF8000000uLL)
              - (COERCE_DOUBLE(*(_QWORD *)&v2.m128d_f64[0] & 0xFFFFFFFFF8000000uLL)
               + COERCE_DOUBLE(*(_QWORD *)&v2.m128d_f64[0] & 0xFFFFFFFFF8000000uLL))
              * v38
              - v40;
          v43 = _mm_shuffle_epi32(v37, 238);
          v44 = (__m128d)_mm_shuffle_epi32(v43, 238);
          v45 = v42 - v38 * v38 + (*(double *)v37.m128i_i64 + v41) * v41;
          v46 = (__m128d)_mm_shuffle_epi32((__m128i)v44, 238);
          v47 = v45 / (*(double *)v43.m128i_i64 + *(double *)v43.m128i_i64);
          v48.m128i_i64[1] = 0x3F8C99999999999ALL;
          v49 = _mm_mul_pd(v44, v44);
          *(double *)v43.m128i_i64 = v46.m128d_f64[0];
          *(double *)v48.m128i_i64 = 0.01155180089613689 * v49.m128d_f64[0];
          v50 = _mm_mul_pd(v46, v49);
          v46.m128d_f64[0] = v50.m128d_f64[0] * v50.m128d_f64[0];
          v50.m128d_f64[0] = v50.m128d_f64[0] * (v50.m128d_f64[0] * v50.m128d_f64[0]);
          v51 = (__m128i)_mm_mul_pd(
                           _mm_add_pd(
                             _mm_mul_pd(_mm_mul_pd(v49, v49), (__m128d)xmmword_6500D0),
                             _mm_add_pd((__m128d)xmmword_6500C0, _mm_mul_pd((__m128d)xmmword_6500B0, v49))),
                           v50);
          *(double *)v48.m128i_i64 = (*(double *)v48.m128i_i64 + *(double *)_mm_shuffle_epi32(v48, 238).m128i_i64)
                                   * (v46.m128d_f64[0]
                                    * v50.m128d_f64[0]);
          v46.m128d_f64[0] = *(double *)_mm_shuffle_epi32((__m128i)xmmword_650060, 238).m128i_i64;
          *(_QWORD *)&result = COERCE_UNSIGNED_INT64(
                                 *(double *)v48.m128i_i64
                               + 6.123233995736766e-17
                               - (*(double *)v51.m128i_i64
                                + *(double *)_mm_shuffle_epi32(v51, 238).m128i_i64
                                + v47)
                               - (*(double *)v43.m128i_i64
                                - (v46.m128d_f64[0]
                                 + *(double *)v43.m128i_i64
                                 - v46.m128d_f64[0]))
                               - (*(double *)v43.m128i_i64
                                - v46.m128d_f64[0]))
                             | _mm_insert_epi16((__m128i)0LL, epi16 & 0x8000, 3).m128i_u64[0];
        }
      }
      else
      {
        v30 = _mm_unpacklo_pd(v5, v5);
        v31 = _mm_unpacklo_pd(v2, v30);
        v32 = _mm_mul_pd(v30, v30);
        v33 = _mm_mul_pd(v31, v32);
        v33.m128d_f64[0] = v33.m128d_f64[0] * v33.m128d_f64[0] * v33.m128d_f64[0];
        v34 = (__m128i)_mm_mul_pd(
                         v33,
                         _mm_add_pd(
                           _mm_add_pd(_mm_mul_pd((__m128d)xmmword_6500B0, v32), (__m128d)xmmword_6500C0),
                           _mm_mul_pd((__m128d)xmmword_6500D0, _mm_mul_pd(v32, v32))));
        return *(double *)v8.m128i_i64 + *(double *)v34.m128i_i64 + *(double *)_mm_shuffle_epi32(v34, 238).m128i_i64;
      }
    }
    else
    {
      *(double *)v4.m128i_i64 = sqrt(1.0 - v2.m128d_f64[0] * v2.m128d_f64[0]);
      v18 = _mm_movemask_epi8((__m128i)v5);
      *(_QWORD *)&v19 = (unsigned __int64)(2LL * *(_QWORD *)&v2.m128d_f64[0]) >> 1;
      v20 = *(_QWORD *)&v2.m128d_f64[0] & 0x7FFFFFC000000000LL;
      v21 = v19 - COERCE_DOUBLE(*(_QWORD *)&v2.m128d_f64[0] & 0x7FFFFFC000000000LL);
      v22 = 1.0 - *(double *)&v20 * *(double *)&v20;
      v23 = (v19 + *(double *)&v20) * (v19 - *(double *)&v20);
      *(_QWORD *)&v24 = COERCE_UNSIGNED_INT64(NAN) & v4.m128i_i64[0] | *(_QWORD *)&inserted.m128d_f64[0];
      v25 = _mm_extract_epi16(_mm_slli_epi64(v4, 2u), 3) - 65216;
      v26 = *(double *)v4.m128i_i64 * *(double *)&qword_64F860[v25];
      v27 = *(double *)&v20 * v24 - v26 + v21 * v24;
      v28 = (__m128i)_mm_sub_pd((__m128d)xmmword_650060, (__m128d)xmmword_64E960[v25]);
      *(_QWORD *)&result = COERCE_UNSIGNED_INT64(
                             (0.04464285714285714 * (v27 * v27) + 0.075) * (v27 * (v27 * v27) * (v27 * v27))
                           + 0.1666666666666667 * (v27 * (v27 * v27))
                           + *(double *)v28.m128i_i64
                           - (v22 - v24 * v24 - v23) / (v26 + v26 + v27)
                           + *(double *)_mm_shuffle_epi32(v28, 238).m128i_i64)
                         | _mm_insert_epi16((__m128i)0LL, (unsigned __int8)(v18 & 0x80) << 8, 3).m128i_u64[0];
    }
  }
  else
  {
    v9 = (v6 & 0xFFFC) - 64256;
    v10 = (__m128i)_mm_or_pd(_mm_and_pd(v3, v5), inserted);
    v11 = sqrt(1.0 - v2.m128d_f64[0] * v2.m128d_f64[0]) * *(double *)v10.m128i_i64;
    v12 = v2.m128d_f64[0] * *(double *)((char *)qword_64F860 + 2 * v9);
    v13 = (*(double *)v8.m128i_i64 - *(double *)v10.m128i_i64)
        * (v5.m128d_f64[0] + *(double *)v10.m128i_i64)
        / (v12 + v11);
    v14 = v12 - v11;
    v15 = (__m128i)_mm_xor_pd(
                     *(__m128d *)((char *)xmmword_64E960 + 4 * v9),
                     (__m128d)_mm_shuffle_epi32(_mm_slli_epi64(_mm_srli_epi64(v10, 0x3Fu), 0x3Fu), 68));
    return v13
         + (0.04464285714285714 * (v14 * v14) + 0.075) * (v14 * (v14 * v14) * (v14 * v14))
         + 0.1666666666666667 * (v14 * (v14 * v14))
         + *(double *)v15.m128i_i64
         + *(double *)_mm_shuffle_epi32(v15, 238).m128i_i64;
  }
  return result;
}

