// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402BA0 rf_point_segment_residual_squared_xy_projection
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Cdecl(point P,start A,end B,outProjected), four required three-float pointers; corrected stored pointer
// types, returns final squared residual in ST0. Computes direction D=B-A and offset V=P-A into separate local vectors. Numerator is ONLY float32(V.x*D.x)+float32(V.y*D.y), sum stored
// FLOAT64; the Z product is OMITTED. Divides this double numerator by full3D lengthSquared(D) returned by vector helper, then rounds parameter t to float32. Applies literal
// max(first=t,second0), roundsfloat32, then literal min(first=t,second1), roundsfloat32. Both literal helpers choose SECOND on unordered, so a NaN t collapses to0 in first clamp; no
// zero-denominator/finite/segment-length guard exists. This is not the ordinary full3D closest-point numerator. Computes all THREE components outProjected=A+t*D via temporary
// scale/add/copy helpers, then RE-READS P and already-written outProjected to return lengthSquared(outProjected-P), without a final float32 store in this wrapper. Output is written
// BEFORE residual computation; aliasing output with P changes what the final subtraction reads (typically zero residual for finite identical vectors), and no alias snapshot/guard
// preserves original P. NaN vector components can still propagate despite parameter clamp. EAX from vector helpers is incidental; floating return remains liveST0.
double __cdecl rf_point_segment_residual_squared_xy_projection(
        const float *a1,
        const float *rhs,
        const float *lhs,
        float *destination)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  double v8; // [esp+8h] [ebp-5Ch]
  float v9[3]; // [esp+10h] [ebp-54h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-48h] BYREF
  float sum_result[3]; // [esp+28h] [ebp-3Ch] BYREF
  int v12[3]; // [esp+34h] [ebp-30h] BYREF
  float v13[3]; // [esp+40h] [ebp-24h] BYREF
  float out_vector[3]; // [esp+4Ch] [ebp-18h] BYREF
  float v15; // [esp+58h] [ebp-Ch]
  float v16; // [esp+5Ch] [ebp-8h]
  float v17; // [esp+60h] [ebp-4h]

  rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_subtract(a1, v13, rhs);
  v17 = v13[0] * out_vector[0];
  v15 = v13[1] * out_vector[1];
  v8 = v17 + v15;
  v16 = v8 / rf_vector_length_squared(out_vector);
  v16 = rf_float_maximum_two_values(v16, 0.0);
  v16 = rf_float_minimum_two_values(v16, 1.0);
  v4 = rf_vector_scale((float *)v12, v16, out_vector);
  v5 = rf_vector_add(rhs, sum_result, v4);
  rf_vector_copy(destination, copy_result, v5);
  v6 = rf_vector_subtract(destination, v9, a1);
  return rf_vector_length_squared(v6);
}

