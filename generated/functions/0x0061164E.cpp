// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061164E crt_atan_sse2_kernel
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Private optimized kernel: scalar binary64 input in
// low64 of its input XMM register plus matching binary64 backup at entryESP+4; caller bridge supplies both, kernel does not check their consistency. Numeric return x87 ST0; no
// incoming numeric ST0. Incoming upper XMM lanes and other scratch vectors/GPRs are not semantic parameters: native lane-definedness review confirms packed arithmetic initializes
// them before use. No repeat of public CPU/FP admission gate; SSE arithmetic/conversion obeys live MXCSR, including rounding/DAZ/FTZ and exception flags. Original constants/tables
// verified bit-for-bit; comments describe native approximation and compensation order, not a proved public numerical error bound. Existing chunks preserved, no byte patches or
// floating environment rollback if a helper/trap escapes. Input low64 XMM7, UNPCKLPD duplicates it. Abs mask then COMISD vs original64BCB8 huge threshold; unordered ->NaN callback
// before other ranges. |x|<2^-27: compare exact floating zero, zero reloads backup preserving sign. Nonzero adds x87 square of original tiny constant2^-991 to backup; if
// |x|<minNormal first force square through binary64 store/reload, else retain extended square. These are status/rounding-sensitive operations, not just identity. [2^-27,1/32) uses
// four paired coefficients64BC30..60 in r^2/r^4 polynomial correction x-P*x; [1/32,3/8) uses eight pairs64BBB0..64BC20. [3/8,8) choose i=((bits(|x|+8)>>44).low32-0x40201), native
// i11..255 inclusive under every rounding mode; 24-byte row at653AF0+24*i contains atanHi,atanLo,center=(i+1)/32. r=(|x|-center)/(1+|x|*center). [8,hugeThreshold) uses row256
// (atanHi+Lo=pi/2) and r=-1/|x|; center field ignored here. Evaluate four-pair polynomial in duplicated r, combine row Hi/Lo and r in native subtraction order, OR original sign into
// low output bits; store through ORIGINAL backup slot and FLD. Huge ordered inputs(including infinities) select original signed pi/2 table64BBA0 by backup sign and add positive
// tiny2^-991 in x87 to affect rounding/status. NaNs call libm_error_support(&backup,&backup,&backup,1003),16 caller-popped bytes, then FLD possibly modified backup. No x87-core
// fallback, own CW/MXCSR save, errno write or SEH.
// local variable allocation has failed, the output may be wrong!
long double __usercall crt_atan_sse2_kernel@<st0>(double x@<xmm7>, double originalImage)
{
  __m128d v2; // xmm7
  __m128d v3; // xmm2
  __m128d v4; // xmm1
  __m128d v5; // xmm3
  __m128d v6; // xmm5
  long double result; // st7
  __m128d v8; // xmm1
  __m128d v9; // xmm3
  __m128d v10; // xmm5
  unsigned __int64 v11; // xmm6_8
  __m128i v12; // xmm3
  int v13; // eax
  __m128d v14; // xmm2
  double v15; // xmm0_8
  __m128d v16; // xmm1
  __m128d v17; // xmm3
  __m128d v18; // xmm5

  v2 = _mm_unpacklo_pd(*(__m128d *)&x, *(__m128d *)&x);
  v3 = _mm_and_pd(v2, (__m128d)xmmword_64BB90);
  if ( v3.m128d_f64[0] >= 1.633123935319537e16 )
    return dbl_64BBA0[HIDWORD(originalImage) >> 31] + 4.778309726736481e-299;
  if ( v3.m128d_f64[0] >= 0.03125 )
  {
    if ( v3.m128d_f64[0] >= 0.375 )
    {
      v11 = _mm_move_epi64((__m128i)v2).m128i_u64[0] ^ *(_QWORD *)&v3.m128d_f64[0];
      if ( v3.m128d_f64[0] >= 8.0 )
      {
        v13 = 768;
        v15 = *(double *)_mm_move_epi64((__m128i)v3).m128i_i64;
        v3 = (__m128d)_mm_loadl_epi64((const __m128i *)&qword_64BC80);
        v3.m128d_f64[0] = v3.m128d_f64[0] / v15;
      }
      else
      {
        v12 = _mm_move_epi64((__m128i)v3);
        *(double *)v12.m128i_i64 = *(double *)v12.m128i_i64 + 8.0;
        v13 = 3
            * _mm_cvtsi128_si32(_mm_sub_epi32(_mm_srli_epi64(v12, 0x2Cu), _mm_loadl_epi64((const __m128i *)&qword_64BC70)));
        v3.m128d_f64[0] = (v3.m128d_f64[0] - qword_653B00[v13])
                        / (*(double *)_mm_move_epi64((__m128i)v3).m128i_i64 * qword_653B00[v13] + 1.0);
      }
      v14 = _mm_unpacklo_pd(v3, v3);
      v16 = _mm_mul_pd(v14, v14);
      v17 = _mm_mul_pd(v16, v16);
      v18 = _mm_add_pd(
              _mm_mul_pd(
                _mm_add_pd(
                  _mm_mul_pd(_mm_add_pd(_mm_mul_pd((__m128d)xmmword_64BC60, v17), (__m128d)xmmword_64BC50), v17),
                  (__m128d)xmmword_64BC40),
                v17),
              (__m128d)xmmword_64BC30);
      v18.m128d_f64[0] = v18.m128d_f64[0] * v16.m128d_f64[0];
      *(_QWORD *)&result = COERCE_UNSIGNED_INT64(
                             *(double *)&qword_653AF0[v13]
                           - ((v18.m128d_f64[0] + _mm_shuffle_pd(v18, v18, 1).m128d_f64[0]) * v14.m128d_f64[0]
                            - *(double *)&qword_653AF8[v13]
                            - v14.m128d_f64[0]))
                         | v11;
    }
    else
    {
      v8 = _mm_mul_pd(v3, v3);
      v9 = _mm_mul_pd(v8, v8);
      v10 = _mm_add_pd(
              _mm_mul_pd(
                _mm_add_pd(
                  _mm_mul_pd(
                    _mm_add_pd(
                      _mm_mul_pd(
                        _mm_add_pd(
                          _mm_mul_pd(
                            _mm_add_pd(
                              _mm_mul_pd(
                                _mm_add_pd(
                                  _mm_mul_pd(
                                    _mm_add_pd(_mm_mul_pd((__m128d)xmmword_64BC20, v9), (__m128d)xmmword_64BC10),
                                    v9),
                                  (__m128d)xmmword_64BC00),
                                v9),
                              (__m128d)xmmword_64BBF0),
                            v9),
                          (__m128d)xmmword_64BBE0),
                        v9),
                      (__m128d)xmmword_64BBD0),
                    v9),
                  (__m128d)xmmword_64BBC0),
                v9),
              (__m128d)xmmword_64BBB0);
      v10.m128d_f64[0] = v10.m128d_f64[0] * v8.m128d_f64[0];
      return v2.m128d_f64[0] - (v10.m128d_f64[0] + _mm_shuffle_pd(v10, v10, 1).m128d_f64[0]) * v2.m128d_f64[0];
    }
  }
  else if ( v3.m128d_f64[0] < 0.000000007450580596923828 )
  {
    if ( v3.m128d_f64[0] == 0.0 )
      return originalImage;
    else
      return 4.778309726736481e-299 * 4.778309726736481e-299 + originalImage;
  }
  else
  {
    v4 = _mm_mul_pd(v3, v3);
    v5 = _mm_mul_pd(v4, v4);
    v6 = _mm_add_pd(
           _mm_mul_pd(
             _mm_add_pd(
               _mm_mul_pd(_mm_add_pd(_mm_mul_pd((__m128d)xmmword_64BC60, v5), (__m128d)xmmword_64BC50), v5),
               (__m128d)xmmword_64BC40),
             v5),
           (__m128d)xmmword_64BC30);
    v6.m128d_f64[0] = v6.m128d_f64[0] * v4.m128d_f64[0];
    return v2.m128d_f64[0] - (v6.m128d_f64[0] + _mm_shuffle_pd(v6, v6, 1).m128d_f64[0]) * v2.m128d_f64[0];
  }
  return result;
}

