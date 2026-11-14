// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055C3C0 rf_matrix3_rotate_forward_about_up_axis
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): Copies current up row, rotates forward row24 about up row12 using negative-stored-angle helper559BD0, then rebuilds whole orientation with55C190(rotatedForward,originalUp). Rebuild can normalize/reconstruct rows and use fallback; not raw multiplication preserving arbitrary scale. Returns builder bits.
float *__thiscall rf_matrix3_rotate_forward_about_up_axis(float *this, float a2)
{
  float *v2; // eax
  float v5[3]; // [esp+14h] [ebp-24h] BYREF
  int v6[3]; // [esp+20h] [ebp-18h] BYREF
  float v7[3]; // [esp+2Ch] [ebp-Ch] BYREF

  rf_vector3_copy_return_destination(v7, this + 3);
  rf_vector3_default_construct_noop(v6);
  v2 = rf_vector3_set_components_return_destination(v5, 0.0, 0.0, 0.0);
  rf_point_rotate_about_axis_pivot((float *)v6, this + 6, a2, v2, this + 3);
  return rf_orientation_from_forward_and_up_hint(this, (float *)v6, v7);
}

