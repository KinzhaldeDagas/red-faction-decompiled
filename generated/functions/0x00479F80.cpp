// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00479F80 rf_skybox_build_axis_rotation
// UNREALRED VERIFIED [authored-sky-renderer] Converts the accumulated sky angle from degrees to radians, starts with identity, lowercases the authored axis byte, and writes the exact X/Y/Z rotation matrix. An unrecognized axis leaves identity.
float *__cdecl rf_skybox_build_axis_rotation(float *a1)
{
  float *result; // eax
  float v2; // [esp+8h] [ebp-Ch]
  float v3; // [esp+Ch] [ebp-8h]
  float v4; // [esp+10h] [ebp-4h]

  v2 = rf_skybox_rotation_angle_degrees * 3.141592741012573 / 180.0;
  v4 = rf_sin_float(v2);
  v3 = rf_cos_float(v2);
  rf_identity_orientation_matrix(a1);
  result = (float *)tolower(rf_skybox_rotation_axis);
  if ( result == (float *)120 )
  {
    a1[4] = v3;
    a1[5] = -v4;
    a1[7] = v4;
    a1[8] = v3;
    return a1;
  }
  else if ( result == (float *)121 )
  {
    *a1 = v3;
    a1[2] = v4;
    a1[6] = -v4;
    a1[8] = v3;
    return a1;
  }
  else if ( result == (float *)122 )
  {
    *a1 = v3;
    a1[1] = -v4;
    a1[3] = v4;
    a1[4] = v3;
    return a1;
  }
  return result;
}

