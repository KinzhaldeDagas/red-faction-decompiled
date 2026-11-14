// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005693B0 rf_segment_plane_hit_point_and_fraction
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl(output4,start,delta,planePoint,normal). denominator=float(-dot(normal,delta)); exactzero returns0 without output. t=float(dot(normal,start-planePoint)/denominator); rejects t<0 or t>1,so finite endpoint hits included and both directions accepted. On accepted path writes XYZ=start+delta*t then output[3]=t,returnsAL1. Shared scratch1809104 and static flag1809110; no lock or pointer/alias validation. Not an endpoint-pair input and not restricted to front faces; no finite/epsilon guard.
char __cdecl rf_segment_plane_hit_point_and_fraction(
        float *destination,
        float *lhs,
        float *vector,
        float *rhs,
        float *a5)
{
  float *v6; // eax
  double v7; // st7
  float *v8; // eax
  float *v9; // eax
  float v10[3]; // [esp+8h] [ebp-50h] BYREF
  float sum_result[3]; // [esp+14h] [ebp-44h] BYREF
  float scaled_result[3]; // [esp+20h] [ebp-38h] BYREF
  float copy_result[3]; // [esp+2Ch] [ebp-2Ch] BYREF
  float out_vector[3]; // [esp+38h] [ebp-20h] BYREF
  float scalar; // [esp+44h] [ebp-14h]
  float v16; // [esp+48h] [ebp-10h]
  int v17; // [esp+54h] [ebp-4h]

  if ( (dword_1809110 & 1) == 0 )
  {
    dword_1809110 |= 1u;
    rf_vector3_default_construct_noop(unk_1809104);
    v17 = -1;
  }
  v16 = -rf_vector_dot(a5, vector);
  if ( v16 == 0.0 )
    return 0;
  v6 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(unk_1809104, copy_result, v6);
  v7 = rf_vector_dot(a5, unk_1809104);
  scalar = v7 / v16;
  if ( scalar < 0.0 )
    return 0;
  if ( scalar > 1.0 )
    return 0;
  v8 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
  v9 = rf_vector_add(lhs, sum_result, v8);
  rf_vector_copy(destination, v10, v9);
  destination[3] = scalar;
  return 1;
}

