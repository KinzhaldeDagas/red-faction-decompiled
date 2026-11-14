// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E7B0 rf_packed3x4_x_rotation_degrees_cosine_quirk
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): cdecl(output48,angleDegrees). Converts degrees via floatpi/180, calls COSINE TWICE (4108A0) for both nominal cosine and sine terms. Copies packed3x4 identity template, writes m11=c,m22=c,m12=-c,m21=c using16byte row stride. So rows(1,0,0,0),(0,c,-c,0),(0,c,c,0); at0degrees result is not identity. This is original instruction behavior, not a decompiler alias error. Final48byte copy staged; returns output.
float *__cdecl rf_packed3x4_x_rotation_degrees_cosine_quirk(float *a1, float a2)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float v6; // [esp+Ch] [ebp-3Ch]
  _BYTE v7[48]; // [esp+10h] [ebp-38h] BYREF
  float v8; // [esp+40h] [ebp-8h]
  float v9; // [esp+44h] [ebp-4h]
  float v10; // [esp+54h] [ebp+Ch]

  v10 = a2 * 3.141592741012573 / 180.0;
  v8 = rf_cos_float(v10);
  v9 = rf_cos_float(v10);
  rf_matrix48_copy_raw_return_self(v7, &unk_6407A8);
  v2 = rf_packed_matrix_element_at_row16_column4_unchecked(v7, 1, 1);
  *v2 = v8;
  v3 = rf_packed_matrix_element_at_row16_column4_unchecked(v7, 2, 2);
  *v3 = v8;
  v6 = -v9;
  *rf_packed_matrix_element_at_row16_column4_unchecked(v7, 1, 2) = v6;
  v4 = rf_packed_matrix_element_at_row16_column4_unchecked(v7, 2, 1);
  *v4 = v9;
  qmemcpy(a1, v7, 0x30u);
  return a1;
}

