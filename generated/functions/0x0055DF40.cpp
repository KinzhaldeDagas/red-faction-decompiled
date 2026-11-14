// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055DF40 rf_affine48_rigid_inverse_to_output
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): ECX source affine(rotation first9floats,translation9..11) plus output, RET4. Creates identity temporary, transposes source3x3, negates source translation then transforms it by transposed rotation with temporary translation0, stores resulting translation and copies48bytes to output. Assumes orthonormal rotation: transpose is not a general inverse for scale/shear. Source/output may coincide because final copy staged. Returns output.
float *__thiscall rf_affine48_rigid_inverse_to_output(const float *this, float *a2)
{
  float *v2; // eax
  float *translation; // eax
  float *v4; // eax
  float *v6; // [esp+Ch] [ebp-B0h]
  float *v7; // [esp+10h] [ebp-ACh]
  float *v8; // [esp+14h] [ebp-A8h]
  float copy_result[3]; // [esp+24h] [ebp-98h] BYREF
  float v11[3]; // [esp+30h] [ebp-8Ch] BYREF
  float v12[3]; // [esp+3Ch] [ebp-80h] BYREF
  float v13[3]; // [esp+48h] [ebp-74h] BYREF
  float v14[3]; // [esp+54h] [ebp-68h] BYREF
  float v15[3]; // [esp+60h] [ebp-5Ch] BYREF
  float v16[3]; // [esp+6Ch] [ebp-50h] BYREF
  int j; // [esp+78h] [ebp-44h]
  int i; // [esp+7Ch] [ebp-40h]
  float v19[12]; // [esp+80h] [ebp-3Ch] BYREF
  float destination[3]; // [esp+B0h] [ebp-Ch] BYREF

  v8 = rf_vector3_set_components_return_destination(v16, 0.0, 0.0, 0.0);
  v7 = rf_vector3_set_components_return_destination(v15, 0.0, 0.0, 1.0);
  v6 = rf_vector3_set_components_return_destination(v14, 0.0, 1.0, 0.0);
  v2 = rf_vector3_set_components_return_destination(v13, 1.0, 0.0, 0.0);
  rf_affine3x4_set_rows_translation(v19, v2, v6, v7, v8);
  for ( i = 0; i < 3; ++i )
  {
    for ( j = 0; j < 3; ++j )
      v19[3 * i + j] = *(this + 3 * j + i);
  }
  translation = rf_affine3x4_get_translation((float *)this, v12);
  rf_vector3_negated_copy(translation, destination);
  v4 = rf_affine3x4_transform_point(v19, v11, destination);
  rf_vector_copy(destination, copy_result, v4);
  rf_affine3x4_set_translation_return_source(v19, destination);
  qmemcpy(a2, v19, 0x30u);
  return a2;
}

