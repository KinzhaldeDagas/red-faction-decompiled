// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060FCFE crt_acos_sse2_kernel
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Private SSE2 acos kernel: scalar binary64 x in low64
// XMM0 plus matching original binary64 image at entryESP+4, provided by public/intrinsic bridges; kernel does not check consistency. Numeric return x87 ST0, no incoming numeric ST0.
// All scratch GPR/vector lanes initialized before semantic/packed arithmetic use; previous extra XMM1/2/3/4/7 formals were decompiler artifacts. Native return paths use a16-byte
// local scalar store/FLD/ADD16/RET. No repetition of public CPU/MXCSR/x87 admission gate and no FP environment save/restore: live MXCSR rounding, DAZ/FTZ, exception masks/status
// apply. Original approximation order and compensation retained; no proved global numerical error bound or C algebraic-reordering equivalence claimed. Let U=(raw64(x)>>44)&0x7FFFF.
// Native chained unsigned wraparound tests partition all524288 prefixes: U<0x3C300 tiny;0x3C300..0x3FAFF small polynomial;0x3FB00..0x3FEBA central table;0x3FEBB..0x3FEFB sqrt-reduced
// table;0x3FEFC..0x3FEFF near-one polynomial;U>=0x3FF00 exact endpoint/domain/NaN handling. Thus tiny cutoff is2^-60, small range reaches1/16, central abs range[1/16,443/512),
// reduced range[443/512,127/128), near-one[127/128,1). Main table j=((U&0xFFFC)-0xFB00)/4 is0..238. 240 records16 at64A230 contain asinLo,asinHi for positive center with
// bits(0x3FB02+4*j)<<44. Separate256-entry64B130 table stores sqrt(1-center^2). c is input-sign midpoint from(raw(x)&0xFFFFC00000000000)|0x0000200000000000. Compute s=sqrt(1-x*x),
// A=x*sqrtTable, B=c*s, r=A-B, and quotient q=((x+c)*(x-c))/(A+B), preserving native operation order. Signed table pair minus split pi/2 pair64B930, negative residual tail polynomial
// -r^3/6-3r^5/40-5r^7/112, q and split table pieces are accumulated in native subtraction order. Reduced-table path splits xH by clearing38 fraction bits, xL=x-xH, computes
// p=(x+xH)*xL, t=1-xH*xH, s=sqrt(t-p); chooses j=((bits(s)>>46)&0xFFFF)-0xFEC0. Exact split identity with conservative directed-rounding bounds proves j63..192 under all four modes.
// Form signed center from s bits and original x sign, r=xH*c-s*sqrtTable+xL*c, q=(t-c*c-p)/(2*s*sqrtTable+r). Add polynomial and compensated q/table pieces; add split -pi pair64B940
// for negative original sign, then XOR original sign bit into final scalar. Small path duplicates x, evaluates paired asin correction through x^13 using coefficients64B9B0..64B9D0,
// and compensated split pi/2-x subtraction. Near-one path t=.5-.5*abs(x),s=sqrt(t), same paired polynomial gives2*asin(s) correction; sH=s&0xFFFFFFFFF8000000,sL=s-sH,
// correction(t-sH*sH-sL*(2*s-sL))/s is accumulated with2*s and polynomial. Negative input adds split -pi then XORs sign, yielding native pi-minus behavior without algebraic rewrite.
// Tiny path ignores input arithmetic and adds original split pi/2 constants, retaining live rounding/inexact. Exact vector abs bits1 returns masked split pi sum for -1, positive zero
// sum for+1. Other out-of-domain vectors classify matching stack backup by raw abs bits: NaN(any payload) ->vector x+0,selector1008; finite abs>1 and infinities ->0*Inf invalid NaN
// proposal,selector58. Both call verified __libm_error_support(&originalImage,&originalImage,&localResult,selector) with28-byte local frame (16 argument bytes plus result slot
// at+16), reload possibly modified result, reclaim28, then common16-byte store/FLD return. Original backup is not overwritten by own paths; no errno work outside callback. Unmasked
// FP traps may escape before callback/return; no rollback claim.
// local variable allocation has failed, the output may be wrong!
double __usercall crt_acos_sse2_kernel@<st0>(double x@<xmm0>, double originalImage)
{
  __m128d v2; // xmm1
  __m128d v3; // xmm2
  __m128i v4; // xmm3
  __m128i v5; // xmm4
  __m128d v6; // xmm7
  int v7; // edx
  __m128d inserted; // xmm5
  __m128d v9; // xmm0
  int v10; // edx
  __m128i v11; // xmm2
  double v12; // xmm3_8
  double v13; // xmm1_8
  double v14; // xmm7_8
  double v15; // xmm3_8
  __m128i v16; // xmm4
  double result; // st7
  unsigned int v18; // eax
  double v19; // xmm7_8
  char v20; // al
  double v21; // xmm1_8
  double v22; // xmm6_8
  __int64 v23; // xmm5_8
  double v24; // xmm0_8
  double v25; // xmm4_8
  unsigned int v26; // eax
  double v27; // xmm2_8
  int v28; // edx
  double v29; // xmm7_8
  double v30; // xmm6_8
  double v31; // xmm4_8
  __m128i v32; // xmm3
  double v33; // xmm0_8
  unsigned int v34; // eax
  __m128d v35; // xmm0
  __m128d v36; // xmm1
  __m128d v37; // xmm0
  __m128d v38; // xmm1
  __m128d v39; // xmm6
  __m128i v40; // xmm1
  unsigned int v41; // eax
  __m128d v42; // xmm7
  __m128d v43; // xmm1
  __m128d v44; // xmm5
  unsigned __int16 epi16; // ax
  __m128d v46; // xmm7
  __m128d v47; // xmm2
  __m128i v48; // xmm0
  __m128d v49; // xmm2
  __m128i v50; // xmm3
  double v51; // xmm4_8
  double v52; // xmm4_8
  __m128d v53; // xmm3
  __m128d v54; // xmm3
  __m128i v55; // xmm2
  int v56; // ecx
  __m128i v57; // xmm7
  double v58; // xmm0_8
  int v59; // edx
  __int64 v60; // xmm7_8
  double v61; // [esp+10h] [ebp-Ch] BYREF

  v3.m128d_f64[0] = NAN;
  v2.m128d_f64[0] = x;
  v9 = (__m128d)_mm_srli_epi64(*(__m128i *)&x, 0x2Cu);
  v7 = _mm_cvtsi128_si32((__m128i)v9);
  v6.m128d_f64[0] = v2.m128d_f64[0];
  inserted = (__m128d)_mm_insert_epi16((__m128i)0LL, 0x2000u, 2);
  v9.m128d_f64[0] = v2.m128d_f64[0];
  if ( (v7 & 0x7FFFFu) - 260864 >= 0x3BB )
  {
    v18 = (v7 & 0x7FFFF) - 261819;
    if ( v18 >= 0x41 )
    {
      v34 = v18 + 15291;
      if ( v34 >= 0x3800 )
      {
        v41 = v34 - 15356;
        if ( v41 >= 4 )
        {
          if ( v41 + 261884 < 0x3FF00 )
          {
            v61 = 6.123233995736766e-17 + 1.570796326794897;
            return 6.123233995736766e-17 + 1.570796326794897;
          }
          else
          {
            v56 = _mm_cvtsi128_si32((__m128i)v6);
            v57 = _mm_srli_epi64((__m128i)v6, 0x20u);
            if ( v56 | (1072693248 - (_mm_cvtsi128_si32(v57) & 0x7FFFFFFF)) )
            {
              v3.m128d_f64[0] = originalImage;
              if ( (((__PAIR64__(
                        _mm_cvtsi128_si32(_mm_srli_epi64((__m128i)v3, 0x20u)) & 0x7FFFFFFF,
                        _mm_cvtsi128_si32((__m128i)v3))
                    - 0x7FF0000000000001LL) >> 32)
                  & 0x80000000) == 0LL )
              {
                v58 = v2.m128d_f64[0] + 0.0;
                v59 = 1008;
              }
              else
              {
                v58 = 0.0 * *(double *)_mm_insert_epi16((__m128i)0LL, 0x7FF0u, 3).m128i_i64;
                v59 = 58;
              }
              v61 = v58;
              __libm_error_support(&originalImage, &originalImage, &v61, v59);
              return v61;
            }
            else
            {
              v60 = _mm_shuffle_epi32(_mm_cvtsi32_si128(-((unsigned int)_mm_extract_epi16(v57, 1) >> 15)), 0).m128i_i64[0];
              return COERCE_DOUBLE(COERCE_UNSIGNED_INT64(3.141592653589793) & v60)
                   + COERCE_DOUBLE(COERCE_UNSIGNED_INT64(1.224646799147353e-16) & v60);
            }
          }
        }
        else
        {
          *(double *)v5.m128i_i64 = 0.5 - fabs(v2.m128d_f64[0]) * 0.5;
          v42 = (__m128d)_mm_shuffle_epi32(v5, 68);
          *(double *)v5.m128i_i64 = sqrt(*(double *)v5.m128i_i64);
          v43 = _mm_mul_pd((__m128d)xmmword_64B9B0, v42);
          v44 = (__m128d)_mm_shuffle_epi32((__m128i)v42, 68);
          epi16 = _mm_extract_epi16((__m128i)v9, 3);
          v46 = _mm_mul_pd(v42, v42);
          v47 = _mm_add_pd(_mm_add_pd((__m128d)xmmword_64B9C0, v43), _mm_mul_pd((__m128d)xmmword_64B9D0, v46));
          v47.m128d_f64[0] = v47.m128d_f64[0] * (v46.m128d_f64[0] * v44.m128d_f64[0]);
          v48 = (__m128i)_mm_and_pd(
                           (__m128d)_mm_shuffle_epi32((__m128i)_mm_cmplt_sd(v9, (__m128d)0LL), 68),
                           (__m128d)xmmword_64B940);
          v49 = _mm_mul_pd(v47, v44);
          *(_QWORD *)&v43.m128d_f64[0] = COERCE_UNSIGNED_INT64(NAN) & v5.m128i_i64[0];
          v50 = _mm_shuffle_epi32(v5, 68);
          v51 = *(double *)v5.m128i_i64 - COERCE_DOUBLE(COERCE_UNSIGNED_INT64(NAN) & v5.m128i_i64[0]);
          *(double *)v50.m128i_i64 = *(double *)v50.m128i_i64 + *(double *)v50.m128i_i64 - v51;
          v52 = v51 * *(double *)v50.m128i_i64;
          v53 = (__m128d)_mm_shuffle_epi32(v50, 238);
          v44.m128d_f64[0] = (v44.m128d_f64[0] - v43.m128d_f64[0] * v43.m128d_f64[0] - v52) / v53.m128d_f64[0];
          v54 = _mm_add_pd(v53, v53);
          v55 = (__m128i)_mm_mul_pd(v49, v54);
          *(_QWORD *)&result = COERCE_UNSIGNED_INT64(
                                 *(double *)_mm_shuffle_epi32(v48, 238).m128i_i64
                               + *(double *)v55.m128i_i64
                               + *(double *)v48.m128i_i64
                               + *(double *)_mm_shuffle_epi32(v55, 238).m128i_i64
                               + v44.m128d_f64[0]
                               + v54.m128d_f64[0])
                             ^ _mm_insert_epi16((__m128i)0LL, epi16 & 0x8000, 3).m128i_u64[0];
        }
      }
      else
      {
        v35 = _mm_unpacklo_pd(v9, v9);
        v36 = _mm_unpacklo_pd(v2, v35);
        v37 = _mm_mul_pd(v35, v35);
        v38 = _mm_mul_pd(v36, v37);
        v38.m128d_f64[0] = v38.m128d_f64[0] * v38.m128d_f64[0] * v38.m128d_f64[0];
        v39 = _mm_add_pd(
                _mm_add_pd(_mm_mul_pd((__m128d)xmmword_64B9B0, v37), (__m128d)xmmword_64B9C0),
                _mm_mul_pd((__m128d)xmmword_64B9D0, _mm_mul_pd(v37, v37)));
        v37.m128d_f64[0] = *(double *)_mm_shuffle_epi32((__m128i)xmmword_64B930, 238).m128i_i64;
        v40 = (__m128i)_mm_mul_pd(v38, v39);
        return v37.m128d_f64[0]
             - v6.m128d_f64[0]
             + 6.123233995736766e-17
             - *(double *)v40.m128i_i64
             - *(double *)_mm_shuffle_epi32(v40, 238).m128i_i64
             - (v6.m128d_f64[0]
              - (v37.m128d_f64[0]
               - (v37.m128d_f64[0]
                - v6.m128d_f64[0])));
      }
    }
    else
    {
      *(_QWORD *)&v19 = *(_QWORD *)&v2.m128d_f64[0] >> 38 << 38;
      v20 = _mm_movemask_epi8((__m128i)v9);
      v21 = v2.m128d_f64[0] - v19;
      v22 = v19;
      v23 = *(_QWORD *)&inserted.m128d_f64[0] | ~COERCE__INT64(NAN) & *(_QWORD *)&v9.m128d_f64[0];
      v24 = (v9.m128d_f64[0] + v19) * v21;
      v25 = 1.0 - v19 * v19;
      *(double *)v4.m128i_i64 = sqrt(v25 - v24);
      v26 = -((unsigned __int8)(v20 & 0x80) >> 7);
      *(_QWORD *)&v27 = COERCE_UNSIGNED_INT64(NAN) & v4.m128i_i64[0] | v23;
      v28 = _mm_extract_epi16(_mm_slli_epi64(v4, 2u), 3) - 65216;
      v29 = *(double *)v4.m128i_i64 * *(double *)&qword_64B130[v28];
      v30 = v22 * v27 - v29 + v21 * v27;
      v31 = v25 - v27 * v27 - v24;
      v32 = (__m128i)_mm_add_pd(
                       _mm_and_pd((__m128d)_mm_shuffle_epi32(_mm_cvtsi32_si128(v26), 0), (__m128d)xmmword_64B940),
                       (__m128d)xmmword_64A230[v28]);
      v33 = (-0.04464285714285714 * (v30 * v30) + -0.075) * (v30 * (v30 * v30) * (v30 * v30))
          + -0.1666666666666667 * (v30 * (v30 * v30))
          + *(double *)v32.m128i_i64;
      v32.m128i_i64[0] = _mm_shuffle_epi32(v32, 238).m128i_i64[0];
      *(_QWORD *)&result = COERCE_UNSIGNED_INT64(
                             v33
                           + v31 / (v29 + v29 + v30)
                           + *(double *)v32.m128i_i64
                           - (v31 / (v29 + v29 + v30)
                            + *(double *)v32.m128i_i64)
                           + v31 / (v29 + v29 + v30)
                           + *(double *)v32.m128i_i64)
                         ^ _mm_insert_epi16((__m128i)0LL, (unsigned __int16)v26 & 0x8000, 3).m128i_u64[0];
    }
  }
  else
  {
    v10 = (v7 & 0xFFFC) - 64256;
    v11 = (__m128i)_mm_or_pd(_mm_and_pd(v3, v6), inserted);
    v12 = sqrt(1.0 - v2.m128d_f64[0] * v2.m128d_f64[0]) * *(double *)v11.m128i_i64;
    v13 = v2.m128d_f64[0] * *(double *)((char *)qword_64B130 + 2 * v10);
    v14 = (v6.m128d_f64[0] + *(double *)v11.m128i_i64) * (v9.m128d_f64[0] - *(double *)v11.m128i_i64) / (v13 + v12);
    v15 = v13 - v12;
    v16 = (__m128i)_mm_sub_pd(
                     _mm_xor_pd(
                       *(__m128d *)((char *)xmmword_64A230 + 4 * v10),
                       (__m128d)_mm_shuffle_epi32(_mm_slli_epi64(_mm_srli_epi64(v11, 0x3Fu), 0x3Fu), 68)),
                     (__m128d)xmmword_64B930);
    return (-0.04464285714285714 * (v15 * v15) + -0.075) * (v15 * (v15 * v15) * (v15 * v15))
         + -0.1666666666666667 * (v15 * (v15 * v15))
         - *(double *)v16.m128i_i64
         - v14
         - *(double *)_mm_shuffle_epi32(v16, 238).m128i_i64;
  }
  return result;
}

