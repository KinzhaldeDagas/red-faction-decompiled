// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055C330 rf_matrix3_rotate_up_about_right_axis
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): ECX matrix plus stored angle. Rotates up row12 around right row0 about origin via559BD0 (physical right-handed angle NEGATIVE stored), writes up, then forward=right cross up. Does not normalize original right or final forward, validate matrix, or rotate right. Returns final forward-row copy destination bits.
float *__thiscall rf_matrix3_rotate_up_about_right_axis(float *this, float a2)
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
  rf_point_rotate_about_axis_pivot(source, this + 3, a2, v2, this);
  rf_vector_copy(this + 3, copy_result, source);
  v3 = rf_vector_cross(this, v7, this + 3);
  return rf_vector_copy(this + 6, v6, v3);
}

