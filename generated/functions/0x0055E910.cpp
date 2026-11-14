// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E910 rf_packed3x4_z_rotation_degrees
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): cdecl(output48,degrees). Converts by floatpi/180, obtainscos/sin, produces packed3x4 rows(c,-s,0,0),(s,c,0,0),(0,0,1,0). Uses16byte row stride, staged48byte result. Returns output, no degrees/radians autodetection.
float *__cdecl rf_packed3x4_z_rotation_degrees(float *a1, float a2)
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
  v9 = rf_sin_float(v10);
  rf_matrix48_copy_raw_return_self(v7, &unk_6407A8);
  v2 = rf_packed_matrix_element_at_row16_column4_unchecked(v7, 0, 0);
  *v2 = v8;
  v3 = rf_packed_matrix_element_at_row16_column4_unchecked(v7, 1, 1);
  *v3 = v8;
  v6 = -v9;
  *rf_packed_matrix_element_at_row16_column4_unchecked(v7, 0, 1) = v6;
  v4 = rf_packed_matrix_element_at_row16_column4_unchecked(v7, 1, 0);
  *v4 = v9;
  qmemcpy(a1, v7, 0x30u);
  return a1;
}

