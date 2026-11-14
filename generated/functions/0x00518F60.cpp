// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518F60 sub_518F60
// UNREALRED VERIFIED [combat-panic-20261104]: Random endpoint:groundedY=chosenWorkingY; flyingY=random[-1,1]*(height-agentHeight)*.5+baseY. Radialdistance=random[0,nodeRadius-agentRadius] then angle=random[0,2pi]; store single-precision radius/angle before native single cos/sin. Coordinate stores remainfloat; disk radius uniform, not sqrt-area-uniform. This defines random local movement rather than geometric fleeing from source.
float *__cdecl sub_518F60(int a1, float *a2, float *a3)
{
  double v3; // st7
  float v5; // [esp+8h] [ebp-Ch]
  float v6; // [esp+Ch] [ebp-8h]
  float v7; // [esp+10h] [ebp-4h]

  if ( *(_BYTE *)(a1 + 32) == 1 )
    a3[1] = a2[4];
  else
    a3[1] = rf_random_float_range(-1.0, 1.0) * (a2[8] - *(float *)(a1 + 28)) * 0.5 + a2[1];
  v5 = a2[7] - *(float *)(a1 + 24);
  v6 = rf_random_float_range(0.0, v5);
  v7 = rf_random_float_range(0.0, 6.2831855);
  *a3 = rf_cos_float(v7) * v6 + *a2;
  v3 = rf_sin_float(v7);
  a3[2] = v3 * v6 + a2[2];
  return a2;
}

