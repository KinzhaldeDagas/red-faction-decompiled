// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006197E9 crt_pow_sse2_kernel
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Private SSE2 pow kernel, ordinary caller-clean stack
// arguments binary64 x at entryESP+4 and y at entryESP+12. MOVLPD reloads x immediately; all incoming XMM/GPR values are scratch, not parameters. Returns one binary64 value via
// FLD64, FLD1 or FLDZ in x87 ST0; no incoming numeric ST0. EBX/EBP untouched; ESI/EDI saved/restored on delayed-scale paths only. Stack inputs are never overwritten. Existing
// function extent and machine bytes preserved. No repeated public CPU/control-word/MXCSR admission check here. SSE arithmetic and CVTSD2SI obey live MXCSR (including
// rounding/DAZ/FTZ/status); final FLD obeys x87 environment. No control-word/MXCSR restoration or numerical-error bound is claimed. Normal positive finite x is recognized by raw
// topWORD w in [0x0010,0x7FEF], using unsigned OR of w-0x10 and 0x7FEF-w. Extract normalized mantissa m from raw bits (fraction mask6539C0, OR1.0 at6539D0). Three original reciprocal
// stages produce a compensated split approximation to log2(abs(x)): R1 table650130 (129 binary64 records), split-log table650540 (129x16); R2 table650D50 / split651160 (129 records);
// C3 table651970 / split652180 (257 records). First index i=((BYTE(bits(x)>>44)+1)&0x1FE)/2, second i=((BYTE(bits(m*R1)>>38)+1)&0x1FE)/2, third i=(((bits(m*R1*R2)>>31)&0x1FF)+1
// &0x3FE)/2. Native byte offsets are 8*i for reciprocals and16*i for split logs; the first table's exponent split follows mantissa cutoff127. Verified split identities: table1
// Hi+Lo=-log2(R1)-[i>=64]; table2=-log2(R2); table3=-log2(C3/C0), C0=1.442694902420044. Exponent contribution uses ((bits(x)>>44)-P)>>8 converted signed lowDWORD, P=0x3FE7F for
// positive normal,0xBFE7F for negative normal,0x43E7F after 2^64 normalization of nonzero subnormal. Logical mask at653A18 is raw0xFFFFFFFFF8000000 (not a NaN numeric operand); split
// mantissa and reciprocal products reconstruct low residual in exact SUBSD/MULSD compensation order. The local residual is relative to C0; paired log-polynomial
// coefficients653190/6531A0 correct its powers in exact packed/scalar order. The y/log exponent estimate is accepted when 0x3C70<=Eyfield+Elogfield-0x3FF0<=0x40A0; otherwise compute
// packed y*splitLog and retry the actual low product exponent against the same range. Below that range return sign-encoded1.0 directly; above it choose overflow versus underflow from
// sign(y) XOR sign(raw exponent(abs(x))-0x3FF0). These are native thresholds/status paths, not a proof of uniform accuracy. Accepted path splits both y and logHi with653A18,
// evaluates W=128*yHi*logHi, and n=CVTSD2SI(W) with live MXCSR rounding, NOT C truncation. Low cross-products and split log residual retain native compensation; independent
// B=1.5*2^52 rounding of W supplies the fractional correction (W-((W+B)-B))/128. Do not conflate this floating rounded value with integer n in other rounding modes. Exponent
// table6531B0 has128x16 records (Hi,Lo) whose sum approximates2^(j/128), j=n&127. Reconstruct2^fraction with original ln2 constant653A10 and paired coefficients6539F0/653A00;
// preserve ADDSD/MULSD summation order, no FMA/reassociation claim. Fast integer n range is [-123391,130943] inclusive, from signed OR guard; exponent/sign scale encoded as
// (((n+signCode)&~127)+0x1FF80)<<45, signCode0 or0x40000. Apply scale to both split exp-table lanes, combine polynomial and low correction, store64/FLD/RET. Outside fast range,
// n>=0x40000 routes overflow and n<=-261632 routes underflow. Intermediate positive n uses D=(n-128)&~127, final signed scale(signCode+0x3FF00)<<45 and an extra doubling; negative n
// uses D=(n&~127)+0x3FE80 with signed min-normal scale(signCode+0x80)<<45. ESI/EDI are pushed only here; exponent(D) remains1..2046. Native PSLLQ builds a raw high-part mask using
// c=2+(0x1FF80-D)/128 followed by c+=(c&0x20); oversized/negative-as-unsigned counts yield zero mask, never a C shift modulo64. Compensation splits the scaled table base and rounds
// its high sum through that mask. D>0x1FF80 combines high/low before final scaling; other branch scales them separately before adding. Optional doubling is represented by saved
// EDI=0x3FF0 (1.0) versus0 (0.0). Restores EDI/ESI before classification: result exponent0x7FF ->selector24, exponent0 (zero OR subnormal)->25, other results return directly. Special
// x paths first classify raw y. y NaN/Inf is handled before integer tests: x NaN takes precedence and proposes x+x; otherwise y NaN proposes y+y (both selector1006). Thus even +1^NaN
// follows y NaN propagation here. For infinite y, exact +/-1 yields provisional1 through selector28; otherwise abs(x)<1 returns0 for +Inf / +Inf for -Inf, and abs(x)>1 reverses those
// results, using positive magnitudes. For finite y==+/-0, nonzero non-NaN x returns1 directly (including infinities); +/-0^0 proposes1 selector26; xNaN^0 proposes1 selector29.
// Positive normal x with y0 takes the later tiny-product return1 directly. Finite negative x requires integer y unless x is exactly signed zero. Integer classification ORs in
// exponent bits, shifts by max(Ey-1011,0), tests both lowDWORDs zero; odd classification shifts original y by Ey-1012 and compares to0x8000000000000000. Both masks derive native low8
// PMOVMSKB bits; all finite exponent classes checked. Odd integer y sets signCode0x40000, even y signCode0. Negative nonzero finite x with noninteger y proposes original negative
// quietNaN653A60, executes SNaN-square653A28 for invalid status, selector28. Raw x NaN proposes x+x selector1006 before this domain check. Positive or negative nonzero subnormal x is
// multiplied by2^64, original raw-zero check retained, and returns to the same log reduction with adjusted exponent P. Under DAZ these SSE operations retain their actual
// environment-sensitive behavior. For finite nonzero y and exact +/-0 x: negative y proposes signed infinity selected by odd-integer signCode and executes1/x for divide-by-zero
// status, selector27; positive y returns signed zero for odd integer negative zero, positive zero otherwise. +/-Inf x with finite nonzero y returns magnitude infinity for positive y,
// zero for negative y; negative sign is retained only for negative infinity with odd integer y, otherwise positive. No domain callback for noninteger powers of negative infinity on
// this native path. Common callback allocates28 bytes: provisional result at local+16, selector local+12, args(&originalX,&originalY,&localResult,selector), CALL61031A, FLD possibly
// replaced local result, ADD28/RET. Selectors24/25 denote overflow/underflow routes;26 zero-to-zero;27 zero-to-negative;28 invalid-power/one-with-infinite-y;29 NaN-to-zero;1006 NaN
// propagation. Direct overflow proposal computes (+/-2^1023)*(+2^1023); direct underflow computes minNormal^2 then ORs odd-negative sign. These operations generate live status and
// may produce a finite saturated/subnormal proposal under directed rounding, so do not replace them with unconditional Inf/zero. Callback remains authoritative for result/errno/fenv
// effects.
double __cdecl crt_pow_sse2_kernel(double x, double y)
{
  __m128d v2; // xmm0
  __m128d v3; // xmm1
  __m128d v4; // xmm2
  __m128d v5; // xmm3
  __m128d v6; // xmm4
  __m128d v7; // xmm5
  __m128d v8; // xmm7
  __m128d v9; // xmm7
  __m128i inserted; // xmm0
  int epi16; // ecx
  int v12; // eax
  __m128d v13; // xmm7
  __m128d v14; // xmm6
  int v15; // edx
  unsigned int v16; // ecx
  unsigned int v17; // edx
  __m128d v18; // xmm1
  __m128d v19; // xmm0
  __m128d v20; // xmm7
  int v21; // eax
  __m128d v22; // xmm6
  double v23; // xmm2_8
  int v24; // eax
  double v25; // xmm2_8
  double v26; // xmm5_8
  __m128d v27; // xmm3
  double v28; // xmm2_8
  double v29; // xmm2_8
  __m128i v30; // xmm1
  int v31; // edx
  double v32; // xmm2_8
  __m128d v33; // xmm0
  __m128d v34; // xmm6
  __m128d v35; // xmm7
  unsigned int v36; // eax
  double v37; // xmm2_8
  double v38; // xmm4_8
  double v39; // xmm3_8
  double v40; // xmm1_8
  double v41; // xmm3_8
  double v42; // xmm5_8
  double v43; // xmm5_8
  double v44; // xmm4_8
  double v45; // xmm5_8
  int v46; // eax
  __m128d v47; // xmm2
  __m128d v48; // xmm7
  __m128i v49; // xmm2
  __m128i v50; // xmm3
  __m128d v51; // xmm0
  __m128d v52; // xmm6
  double v53; // xmm4_8
  __m128d v54; // xmm0
  __m128i v55; // xmm7
  double result; // st7
  int v57; // eax
  __m128i v58; // xmm1
  unsigned int v59; // ecx
  __m128i v60; // xmm2
  __m128i v61; // xmm1
  __m128i v62; // xmm2
  unsigned __int8 v63; // al
  unsigned int v64; // edx
  __m128i v65; // xmm1
  int v66; // edx
  int v67; // eax
  __m128d v68; // xmm7
  int v69; // eax
  __m128d v70; // xmm0
  int v71; // edx
  __m128i v72; // xmm1
  int v73; // eax
  int v74; // eax
  int v75; // eax
  __m128i v76; // xmm4
  int v77; // ecx
  unsigned int v78; // eax
  int v79; // eax
  unsigned int v80; // ecx
  unsigned int v81; // edx
  unsigned int v82; // edi
  double v83; // xmm4_8
  __m128d v84; // xmm2
  __m128d v85; // xmm7
  __m128i v86; // xmm2
  __m128i v87; // xmm3
  __m128d v88; // xmm0
  __m128d v89; // xmm6
  double v90; // xmm4_8
  __m128i v91; // xmm7
  double v92; // xmm7_8
  double v93; // xmm1_8
  __int64 v94; // xmm4_8
  double v95; // xmm1_8
  double v96; // xmm6_8
  int v97; // eax
  int v98; // eax
  int v99; // eax
  int v100; // edx
  unsigned int v101; // eax
  double *v102; // [esp+0h] [ebp-1Ch] BYREF
  double v103; // [esp+10h] [ebp-Ch] BYREF

  v2.m128d_f64[0] = x;
  v8.m128d_f64[0] = COERCE_DOUBLE(0xFFFFFFFFFFFFFLL);
  v4.m128d_f64[0] = 1.0;
  v9 = _mm_and_pd(v8, v2);
  v6.m128d_f64[0] = x;
  inserted = _mm_srli_epi64((__m128i)v2, 0x2Cu);
  v13 = _mm_or_pd(v9, v4);
  epi16 = _mm_extract_epi16((__m128i)v6, 3);
  v12 = ((unsigned __int8)_mm_extract_epi16(inserted, 0) + 1) & 0x1FE;
  v13.m128d_f64[0] = v13.m128d_f64[0] * *(double *)((char *)&qword_650130 + 4 * v12);
  v7.m128d_f64[0] = *(double *)((char *)&qword_650130 + 4 * v12);
  v14 = *(__m128d *)((char *)&xmmword_650540 + 8 * v12);
  v15 = 32751 - epi16;
  if ( ((32751 - epi16) | (unsigned int)(epi16 - 16)) < 0x80000000 )
  {
    v16 = 0;
    v17 = 261759;
    goto BACK_MAIN;
  }
  v3.m128d_f64[0] = y;
  v5.m128d_f64[0] = NAN;
  v57 = _mm_cvtsi128_si32((__m128i)v3);
  v4.m128d_f64[0] = y;
  v58 = _mm_srli_epi64((__m128i)_mm_and_pd(v3, v5), 0x20u);
  v59 = _mm_cvtsi128_si32(v58);
  if ( v59 >= 0x7FF00000 )
  {
    v13.m128d_f64[0] = x;
    v6.m128d_f64[0] = x;
    v31 = _mm_cvtsi128_si32((__m128i)v13);
    v16 = _mm_cvtsi128_si32(_mm_srli_epi64((__m128i)v13, 0x20u));
    if ( (v16 & 0x7FFFFFFF) < 0x7FF00000 || (v16 & 0x7FFFFFFF) <= 0x7FF00000 && !v31 )
      goto Y_INF_NAN;
    goto X_NAN;
  }
  if ( !(v59 | v57) )
  {
    v75 = _mm_cvtsi128_si32((__m128i)v6);
    v76 = _mm_srli_epi64((__m128i)v6, 0x20u);
    v77 = v75;
    v70.m128d_f64[0] = 1.0;
    v71 = 26;
    if ( _mm_cvtsi128_si32(v76) & 0x7FFFFFFF | v75 )
    {
      v71 = 29;
      v78 = _mm_cvtsi128_si32(v76) & 0x7FFFFFFF;
      if ( v78 <= 0x7FF00000 && (v78 < 0x7FF00000 || !v77) )
      {
        v103 = 1.0;
        return 1.0;
      }
    }
    goto CALL_LIBM_ERROR_3;
  }
  if ( v15 >= 0 )
  {
    v16 = 0;
    goto DENORMAL_X;
  }
  v60 = (__m128i)_mm_or_pd(v4, (__m128d)_mm_slli_epi64((__m128i)v5, 0x34u));
  v5 = 0;
  v61 = _mm_max_epi16(_mm_sub_epi32(_mm_srli_epi64(v58, 0x14u), _mm_cvtsi32_si128(0x3F3u)), (__m128i)0LL);
  v62 = _mm_cmpeq_epi32(_mm_sll_epi64(v60, v61), (__m128i)0LL);
  v63 = _mm_movemask_epi8(v62);
  v64 = (32751 - v15) & 0x7FFF;
  if ( v64 >= 0x7FF0 )
  {
    v5.m128d_f64[0] = COERCE_DOUBLE(0xFFFFFFFFFFFFFLL);
    v72 = _mm_cmpeq_epi32((__m128i)0LL, (__m128i)_mm_and_pd(v5, v6));
    if ( (unsigned __int8)_mm_movemask_epi8(v72) == 255 )
    {
      if ( (_mm_extract_epi16((__m128i)v6, 3) & 0x8000) != 0 )
      {
        if ( v63 == 255 )
        {
          *(double *)v72.m128i_i64 = y;
          *(double *)v62.m128i_i64 = y;
          v72 = _mm_sub_epi32(
                  _mm_srli_epi64((__m128i)_mm_and_pd((__m128d)v72, (__m128d)xmmword_6539E0), 0x34u),
                  _mm_cvtsi32_si128(0x3F4u));
          if ( (unsigned __int8)_mm_movemask_epi8(_mm_cmpeq_epi32(_mm_sll_epi64(v62, v72), (__m128i)0LL)) != 255 )
          {
            *(double *)v72.m128i_i64 = y;
            if ( (_mm_extract_epi16(v72, 3) & 0x8000) == 0 )
              return -INFINITY;
            return -0.0;
          }
        }
        *(double *)v72.m128i_i64 = y;
        if ( (_mm_extract_epi16(v72, 3) & 0x8000) != 0 )
          return 0.0;
      }
      else
      {
        *(double *)v72.m128i_i64 = y;
        if ( (_mm_extract_epi16(v72, 3) & 0x8000) != 0 )
          return 0.0;
      }
      return INFINITY;
    }
X_NAN:
    v70.m128d_f64[0] = v6.m128d_f64[0] + v6.m128d_f64[0];
    v71 = 1006;
    goto CALL_LIBM_ERROR_3;
  }
  if ( v63 != 255 )
  {
    *(double *)v62.m128i_i64 = x;
    v73 = _mm_cvtsi128_si32(v62);
    v4 = (__m128d)_mm_srli_epi64(v62, 0x20u);
    v67 = _mm_cvtsi128_si32((__m128i)v4) & 0x7FFFFFFF | v73;
    v16 = 0;
    if ( v67 )
    {
      v70.m128d_f64[0] = NAN;
      v71 = 28;
      goto CALL_LIBM_ERROR_3;
    }
    goto ZERO_X;
  }
  *(double *)v61.m128i_i64 = y;
  *(double *)v62.m128i_i64 = y;
  v5 = (__m128d)_mm_cvtsi32_si128(0x3F4u);
  v65 = _mm_sub_epi32(_mm_srli_epi64((__m128i)_mm_and_pd((__m128d)v61, (__m128d)xmmword_6539E0), 0x34u), (__m128i)v5);
  v5.m128d_f64[0] = -0.0;
  v4 = (__m128d)_mm_cmpeq_epi32(_mm_sll_epi64(v62, v65), (__m128i)v5);
  v16 = ((unsigned __int8)_mm_movemask_epi8((__m128i)v4) + 261889) & 0x40000;
  if ( v64 >= 0x10 )
  {
    v17 = 786047;
    goto BACK_MAIN;
  }
DENORMAL_X:
  inserted = _mm_insert_epi16((__m128i)0LL, 0x43F0u, 3);
  v13.m128d_f64[0] = COERCE_DOUBLE(0xFFFFFFFFFFFFFLL);
  v4.m128d_f64[0] = 1.0;
  *(double *)inserted.m128i_i64 = *(double *)inserted.m128i_i64 * x;
  v66 = _mm_cvtsi128_si32((__m128i)v6);
  v6 = (__m128d)_mm_srli_epi64((__m128i)v6, 0x20u);
  v67 = _mm_cvtsi128_si32((__m128i)v6);
  if ( !v66 )
  {
ZERO_X:
    if ( (v67 & 0x7FFFFFFF) != 0 )
      goto BACK_DEN;
    if ( y < 0.0 )
    {
      *(_QWORD *)&v70.m128d_f64[0] = _mm_cvtsi32_si128((v16 << 13) & v67 | 0x7FF00000).m128i_u64[0] << 32;
      v71 = 27;
      goto CALL_LIBM_ERROR_3;
    }
    if ( ((v16 << 13) & v67) == 0 )
      return 0.0;
    return -0.0;
  }
BACK_DEN:
  v68 = _mm_and_pd(v13, (__m128d)inserted);
  v6.m128d_f64[0] = *(double *)inserted.m128i_i64;
  inserted = _mm_srli_epi64((__m128i)_mm_and_pd((__m128d)inserted, (__m128d)xmmword_6539E0), 0x2Cu);
  v13 = _mm_or_pd(v68, v4);
  v69 = ((unsigned __int8)_mm_extract_epi16(inserted, 0) + 1) & 0x1FE;
  v13.m128d_f64[0] = v13.m128d_f64[0] * *(double *)((char *)&qword_650130 + 4 * v69);
  v7.m128d_f64[0] = *(double *)((char *)&qword_650130 + 4 * v69);
  v14 = *(__m128d *)((char *)&xmmword_650540 + 8 * v69);
  v17 = 278143;
BACK_MAIN:
  v18 = (__m128d)_mm_cvtsi32_si128(v17);
  v19 = _mm_cvtepi32_pd(_mm_srli_epi64(_mm_sub_epi64(inserted, (__m128i)v18), 8u));
  v18.m128d_f64[0] = NAN;
  v5.m128d_f64[0] = v13.m128d_f64[0];
  v20 = (__m128d)_mm_srli_epi64((__m128i)v13, 0x26u);
  v21 = ((unsigned __int8)_mm_extract_epi16((__m128i)v20, 0) + 1) & 0x1FE;
  v5.m128d_f64[0] = v5.m128d_f64[0] * *(double *)((char *)&qword_650D50 + 4 * v21);
  v7.m128d_f64[0] = v7.m128d_f64[0] * *(double *)((char *)&qword_650D50 + 4 * v21);
  v22 = _mm_add_pd(v14, *(__m128d *)((char *)&xmmword_651160 + 8 * v21));
  v6 = _mm_or_pd(_mm_and_pd(v6, (__m128d)xmmword_6539C0), (__m128d)xmmword_6539D0);
  v22.m128d_f64[0] = v22.m128d_f64[0] + v19.m128d_f64[0];
  v30 = (__m128i)_mm_and_pd(v18, v6);
  v23 = v5.m128d_f64[0];
  v27 = (__m128d)_mm_srli_epi64((__m128i)v5, 0x1Fu);
  v19.m128d_f64[0] = NAN;
  v6.m128d_f64[0] = v6.m128d_f64[0] - *(double *)v30.m128i_i64;
  v24 = ((_mm_extract_epi16((__m128i)v27, 0) & 0x1FF) + 1) & 0x3FE;
  v7.m128d_f64[0] = v7.m128d_f64[0] * *(double *)((char *)&qword_651970 + 4 * v24);
  v25 = v23 * *(double *)((char *)&qword_651970 + 4 * v24);
  v34 = _mm_add_pd(v22, *(__m128d *)((char *)&xmmword_652180 + 8 * v24));
  v33 = _mm_and_pd(v19, v7);
  v26 = v7.m128d_f64[0] - v33.m128d_f64[0];
  v20.m128d_f64[0] = v25 + -1.442694902420044;
  v27.m128d_f64[0] = v33.m128d_f64[0];
  v28 = v25 - v33.m128d_f64[0] * *(double *)v30.m128i_i64;
  v33.m128d_f64[0] = v34.m128d_f64[0];
  v29 = v28 - *(double *)v30.m128i_i64 * v26;
  v34.m128d_f64[0] = v34.m128d_f64[0] + v20.m128d_f64[0];
  *(double *)v30.m128i_i64 = y;
  v31 = _mm_extract_epi16((__m128i)v34, 3);
  v32 = v29 - v27.m128d_f64[0] * v6.m128d_f64[0] - v6.m128d_f64[0] * v26;
  v6.m128d_f64[0] = v34.m128d_f64[0];
  v33.m128d_f64[0] = v33.m128d_f64[0] - v34.m128d_f64[0] + v20.m128d_f64[0];
  v20.m128d_f64[0] = v20.m128d_f64[0] - v32;
  v34.m128d_f64[0] = v34.m128d_f64[0] - v32;
  v35 = _mm_unpacklo_pd(v20, v20);
  v36 = _mm_extract_epi16(v30, 3) & 0x7FF0;
  if ( v36 >= 0x7FF0 )
  {
    v6.m128d_f64[0] = x;
    v4.m128d_f64[0] = y;
    v27.m128d_f64[0] = COERCE_DOUBLE(0xFFFFFFFFFFFFFLL);
    v5 = _mm_and_pd(v27, v4);
    if ( (unsigned __int8)_mm_movemask_epi8(_mm_cmpeq_epi32((__m128i)0LL, (__m128i)v5)) != 255 )
      goto RET_Y_NAN;
    if ( !_mm_cvtsi128_si32((__m128i)v6) )
    {
      v6 = (__m128d)_mm_srli_epi64((__m128i)v6, 0x20u);
      v31 = _mm_cvtsi128_si32((__m128i)v6);
      if ( v31 == 1072693248 )
        goto RET_ONE;
      if ( v31 == -1074790400 )
        return 1.0;
    }
Y_INF_NAN:
    v5.m128d_f64[0] = COERCE_DOUBLE(0xFFFFFFFFFFFFFLL);
    if ( (unsigned __int8)_mm_movemask_epi8(_mm_cmpeq_epi32((__m128i)0LL, (__m128i)_mm_and_pd(v5, v4))) == 255 )
    {
      v6.m128d_f64[0] = x;
      v74 = _mm_extract_epi16((__m128i)v4, 3) & 0x8000;
      if ( v16 ^ 0xBFF00000 | v31 )
      {
        if ( v74 )
        {
          if ( (_mm_extract_epi16((__m128i)v6, 3) & 0x7FF0u) >= 0x3FF0 )
            return 0.0;
        }
        else if ( (_mm_extract_epi16((__m128i)v6, 3) & 0x7FF0u) < 0x3FF0 )
        {
          return 0.0;
        }
        return INFINITY;
      }
RET_ONE:
      v70.m128d_f64[0] = 1.0;
      v71 = 28;
      goto CALL_LIBM_ERROR_3;
    }
RET_Y_NAN:
    v70.m128d_f64[0] = v4.m128d_f64[0] + v4.m128d_f64[0];
    v71 = 1006;
    goto CALL_LIBM_ERROR_3;
  }
  if ( (((v31 & 0x7FF0) + v36 - 16368 - 15472) | (16544 - ((v31 & 0x7FF0) + v36 - 16368))) < 0x80000000
    || (v6 = _mm_mul_pd((__m128d)_mm_shuffle_epi32(v30, 68), v34),
        v99 = _mm_extract_epi16((__m128i)v6, 3) & 0x7FF0,
        v100 = 16544 - v99,
        v101 = v99 - 15472,
        (v101 | v100) < 0x80000000) )
  {
    v37 = v32 - (v6.m128d_f64[0] - v34.m128d_f64[0]);
    *(_QWORD *)&v38 = COERCE_UNSIGNED_INT64(NAN) & *(_QWORD *)&v34.m128d_f64[0];
    v33.m128d_f64[0] = v33.m128d_f64[0] - v37;
    v39 = COERCE_DOUBLE(COERCE_UNSIGNED_INT64(NAN) & *(_QWORD *)&y)
        * COERCE_DOUBLE(COERCE_UNSIGNED_INT64(NAN) & *(_QWORD *)&v34.m128d_f64[0]);
    v34.m128d_f64[0] = v34.m128d_f64[0] - COERCE_DOUBLE(COERCE_UNSIGNED_INT64(NAN) & *(_QWORD *)&v34.m128d_f64[0]);
    v40 = y - COERCE_DOUBLE(COERCE_UNSIGNED_INT64(NAN) & *(_QWORD *)&y);
    v41 = v39 * *(double *)_mm_insert_epi16((__m128i)0LL, 0x4060u, 3).m128i_i64;
    v42 = COERCE_DOUBLE(COERCE_UNSIGNED_INT64(NAN) & *(_QWORD *)&y) * v34.m128d_f64[0];
    v34.m128d_f64[0] = v34.m128d_f64[0] * v40;
    v43 = v42 + v38 * v40;
    *(_QWORD *)&v44 = _mm_shuffle_epi32((__m128i)v34, 238).m128i_u64[0];
    v45 = v43 + v34.m128d_f64[0];
    v46 = (int)v41;
    if ( (((int)v41 + 123391) | (130943 - (int)v41)) > 0 )
    {
      v47 = _mm_mul_pd((__m128d)xmmword_653190, v35);
      v48 = _mm_mul_pd(v35, v35);
      v49 = (__m128i)_mm_add_pd(v47, _mm_mul_pd((__m128d)xmmword_6531A0, v48));
      *(double *)v49.m128i_i64 = *(double *)v49.m128i_i64 * v48.m128d_f64[0]
                               + *(double *)_mm_shuffle_epi32(v49, 238).m128i_i64
                               + v44
                               + v33.m128d_f64[0];
      v33.m128d_f64[0] = (v41 - (v41 + 6.755399441055744e15 - 6.755399441055744e15))
                       * *(double *)_mm_insert_epi16((__m128i)0LL, 0x3F80u, 3).m128i_i64;
      v50 = (__m128i)_mm_mul_pd(
                       *((__m128d *)&unk_6531B0 + ((int)v41 & 0x7F)),
                       (__m128d)_mm_shuffle_epi32(
                                  _mm_slli_epi64(_mm_cvtsi32_si128((((int)v41 + v16) & 0xFFFFFF80) + 130944), 0x2Du),
                                  68));
      v33.m128d_f64[0] = v33.m128d_f64[0] + v45 + *(double *)v49.m128i_i64 * y;
      v51 = _mm_unpacklo_pd(v33, v33);
      v52 = _mm_mul_pd((__m128d)xmmword_6539F0, v51);
      v53 = 0.6931471805599453 * v51.m128d_f64[0];
      v54 = _mm_mul_pd(v51, v51);
      v55 = (__m128i)_mm_mul_pd(_mm_add_pd((__m128d)xmmword_653A00, v52), v54);
      return v54.m128d_f64[0] * *(double *)v50.m128i_i64 * *(double *)v55.m128i_i64
           + *(double *)_mm_shuffle_epi32(v50, 238).m128i_i64
           + *(double *)_mm_shuffle_epi32(v55, 238).m128i_i64 * *(double *)v50.m128i_i64
           + v53 * *(double *)v50.m128i_i64
           + *(double *)v50.m128i_i64;
    }
    if ( v46 <= 0 )
    {
      if ( v46 <= -261632 )
      {
RET_ZERO_UF:
        *(_QWORD *)&v70.m128d_f64[0] = COERCE_UNSIGNED_INT64(2.225073858507201e-308 * 2.225073858507201e-308)
                                     | (_mm_cvtsi32_si128(v16).m128i_u64[0] << 45);
        v71 = 25;
        goto CALL_LIBM_ERROR_3;
      }
      v79 = (int)v41 & 0x7F;
      v80 = v16 + 128;
      v81 = ((int)v41 & 0xFFFFFF80) + 261760;
      v82 = 0;
    }
    else
    {
      if ( (unsigned int)v46 >= 0x40000 )
        goto RET_INF_OF;
      v79 = (int)v41 & 0x7F;
      v80 = v16 + 261888;
      v81 = ((int)v41 - 128) & 0xFFFFFF80;
      v82 = 16368;
    }
    v83 = v44 + v33.m128d_f64[0];
    v84 = _mm_mul_pd((__m128d)xmmword_653190, v35);
    v85 = _mm_mul_pd(v35, v35);
    v33.m128d_f64[0] = v41 - (v41 + 6.755399441055744e15 - 6.755399441055744e15);
    v86 = (__m128i)_mm_add_pd(v84, _mm_mul_pd((__m128d)xmmword_6531A0, v85));
    v87 = (__m128i)_mm_mul_pd(
                     *((__m128d *)&unk_6531B0 + v79),
                     (__m128d)_mm_shuffle_epi32(_mm_slli_epi64(_mm_cvtsi32_si128(v81), 0x2Du), 68));
    v33.m128d_f64[0] = v33.m128d_f64[0] * *(double *)_mm_insert_epi16((__m128i)0LL, 0x3F80u, 3).m128i_i64
                     + v45
                     + (*(double *)v86.m128i_i64 * v85.m128d_f64[0]
                      + *(double *)_mm_shuffle_epi32(v86, 238).m128i_i64
                      + v83)
                     * y;
    v88 = _mm_unpacklo_pd(v33, v33);
    v89 = _mm_mul_pd((__m128d)xmmword_6539F0, v88);
    v90 = 0.6931471805599453 * v88.m128d_f64[0];
    v70 = _mm_mul_pd(v88, v88);
    v91 = (__m128i)_mm_mul_pd(_mm_add_pd((__m128d)xmmword_653A00, v89), v70);
    v89.m128d_f64[0] = *(double *)_mm_shuffle_epi32(v91, 238).m128i_i64;
    v70.m128d_f64[0] = v70.m128d_f64[0] * *(double *)v87.m128i_i64 * *(double *)v91.m128i_i64;
    *(_QWORD *)&v92 = _mm_cvtsi32_si128(v80).m128i_u64[0] << 45;
    v86.m128i_i8[0] = _mm_cvtsi32_si128((((unsigned __int8)((int)(130944 - v81) >> 7) + 2) & 0x20u) + ((int)(130944 - v81) >> 7) + 2).m128i_u8[0];
    *(_QWORD *)&v93 = (-1LL << v86.m128i_i8[0]) & v87.m128i_i64[0];
    v70.m128d_f64[0] = v70.m128d_f64[0]
                     + *(double *)_mm_shuffle_epi32(v87, 238).m128i_i64
                     + v89.m128d_f64[0] * *(double *)v87.m128i_i64
                     + v90 * *(double *)v87.m128i_i64;
    v94 = -1LL << v86.m128i_i8[0];
    *(double *)v87.m128i_i64 = *(double *)v87.m128i_i64 - v93;
    *(double *)v86.m128i_i64 = v93;
    *(_QWORD *)&v95 = COERCE_UNSIGNED_INT64(v93 + v70.m128d_f64[0]) & v94;
    *(_QWORD *)&v96 = _mm_insert_epi16((__m128i)0LL, v82, 3).m128i_u64[0];
    v70.m128d_f64[0] = v70.m128d_f64[0] + *(double *)v86.m128i_i64 - v95 + *(double *)v87.m128i_i64;
    if ( (int)(v81 - 130944) > 0 )
    {
      v70.m128d_f64[0] = (v70.m128d_f64[0] + v95) * v92 + v96 * ((v70.m128d_f64[0] + v95) * v92);
      v98 = _mm_extract_epi16((__m128i)v70, 3) & 0x7FF0;
      v71 = 24;
      if ( v98 != 32752 )
      {
        v71 = 25;
        if ( v98 )
        {
          v103 = v70.m128d_f64[0];
          return v70.m128d_f64[0];
        }
      }
    }
    else
    {
      v70.m128d_f64[0] = v70.m128d_f64[0] * v92 + v95 * v92 + v96 * (v70.m128d_f64[0] * v92 + v95 * v92);
      v97 = _mm_extract_epi16((__m128i)v70, 3) & 0x7FF0;
      v71 = 24;
      if ( v97 != 32752 )
      {
        v71 = 25;
        if ( v97 )
        {
          v103 = v70.m128d_f64[0];
          return v70.m128d_f64[0];
        }
      }
    }
CALL_LIBM_ERROR_3:
    v103 = v70.m128d_f64[0];
    __libm_error_support((double *)&v102 + 4, &y, &v103, v71);
    return v103;
  }
  if ( v101 < 0x80000000 )
  {
    v6.m128d_f64[0] = x;
    if ( (((unsigned __int16)((_mm_extract_epi16((__m128i)v6, 3) & 0x7FF0) - 16368)
         ^ (unsigned __int16)_mm_extract_epi16(v30, 3))
        & 0x8000) == 0 )
    {
RET_INF_OF:
      v71 = 24;
      if ( v16 )
        v70.m128d_f64[0] = -8.98846567431158e307 * 8.98846567431158e307;
      else
        v70.m128d_f64[0] = 8.98846567431158e307 * 8.98846567431158e307;
      goto CALL_LIBM_ERROR_3;
    }
    goto RET_ZERO_UF;
  }
  *(_QWORD *)&result = _mm_cvtsi32_si128(v16 | 0x1FF80).m128i_u64[0] << 45;
  return result;
}

