// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056AFD0 rf_point_inside_radius_expanded_oriented_box
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl(point,radius,boxCenter,basis9,fullDimensions). Shared scratch localPoint=point-center,then inverse-rotate by matrix transpose5594A0. Builds lower=-0.5*dimensions-radius,upper=0.5*dimensions+radius per axis,then inclusive point/AABB test56AD40. Requires orthonormal basis for geometric inverse; no general inverse. This is componentwise expanded box containment,so corner cases are not exact sphere/OBB distance tests. Negative dimensions/radius unchecked; static scratch1809210/1809204/18091F8 and flags180921C without lock.
bool __cdecl rf_point_inside_radius_expanded_oriented_box(float *lhs, float a2, float *rhs, float *a4, float *vector)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float v9[3]; // [esp+8h] [ebp-54h] BYREF
  float v10[3]; // [esp+14h] [ebp-48h] BYREF
  float v11[3]; // [esp+20h] [ebp-3Ch] BYREF
  float scaled_result[3]; // [esp+2Ch] [ebp-30h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-24h] BYREF
  float out_vector[3]; // [esp+44h] [ebp-18h] BYREF
  int v15; // [esp+58h] [ebp-4h]

  if ( (dword_180921C & 1) == 0 )
  {
    dword_180921C |= 1u;
    rf_vector3_default_construct_noop(unk_1809210);
    v15 = -1;
  }
  v5 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(unk_1809210, copy_result, v5);
  rf_matrix3_inverse_rotate_vector(unk_1809210, a4);
  if ( (dword_180921C & 2) == 0 )
  {
    dword_180921C |= 2u;
    v15 = 1;
    rf_vector3_default_construct_noop(unk_1809204);
    v15 = -1;
  }
  if ( (dword_180921C & 4) == 0 )
  {
    dword_180921C |= 4u;
    v15 = 2;
    rf_vector3_default_construct_noop(unk_18091F8);
    v15 = -1;
  }
  v6 = rf_vector_multiply_scalar(vector, scaled_result, -0.5);
  rf_vector_copy(unk_1809204, v11, v6);
  v7 = rf_vector_multiply_scalar(vector, v10, 0.5);
  rf_vector_copy(unk_18091F8, v9, v7);
  rf_vector3_subtract_scalar_in_place(unk_1809204, a2);
  rf_vector3_add_scalar_in_place(unk_18091F8, a2);
  return rf_aabb_contains_point_inclusive(unk_1809210, unk_1809204, unk_18091F8);
}

