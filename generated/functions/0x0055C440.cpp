// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055C440 rf_matrix3_rotate_up_about_forward_axis
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): Rotates up row12 about forward row24 using559BD0 negative-stored-angle convention, writes up then right=up cross forward. Forward unchanged, no final right/up normalization or input validity checks. Returns right-row copy destination bits.
float *__thiscall rf_matrix3_rotate_up_about_forward_axis(float *this, float a2)
{
  float *v2; // eax
  float *v3; // eax
  float v6[3]; // [esp+14h] [ebp-3Ch] BYREF
  float v7[3]; // [esp+20h] [ebp-30h] BYREF
  float copy_result[3]; // [esp+2Ch] [ebp-24h] BYREF
  float v9[3]; // [esp+38h] [ebp-18h] BYREF
  float source[3]; // [esp+44h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(source);
  v2 = rf_vector3_set_components_return_destination(v9, 0.0, 0.0, 0.0);
  rf_point_rotate_about_axis_pivot(source, this + 3, a2, v2, this + 6);
  rf_vector_copy(this + 3, copy_result, source);
  v3 = rf_vector_cross(this + 3, v7, this + 6);
  return rf_vector_copy(this, v6, v3);
}

