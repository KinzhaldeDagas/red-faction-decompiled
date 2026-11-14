// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E0F0 rf_affine3x4_set_identity
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Builds3x3 identity from axis vectors(1,0,0),(0,1,0),(0,0,1), then uses55EB80 to copy rotation and zero translation. Returns destination. RF affine layout is contiguous9 rotation floats followed by3 translation floats, not interleaved per-row translation.
float *__thiscall rf_affine3x4_set_identity(float *this)
{
  float *v1; // eax
  float *v2; // eax
  float *v4; // [esp+Ch] [ebp-54h]
  float *v5; // [esp+10h] [ebp-50h]
  float v7[3]; // [esp+18h] [ebp-48h] BYREF
  float v8[3]; // [esp+24h] [ebp-3Ch] BYREF
  float v9[3]; // [esp+30h] [ebp-30h] BYREF
  _BYTE v10[36]; // [esp+3Ch] [ebp-24h] BYREF

  v5 = rf_vector3_set_components_return_destination(v9, 0.0, 0.0, 1.0);
  v4 = rf_vector3_set_components_return_destination(v8, 0.0, 1.0, 0.0);
  v1 = rf_vector3_set_components_return_destination(v7, 1.0, 0.0, 0.0);
  v2 = (float *)rf_matrix3_construct_from_three_rows((int)v10, v1, v4, v5);
  return rf_affine3x4_copy_rotation_zero_translation(this, v2);
}

