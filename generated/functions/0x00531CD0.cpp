// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00531CD0 sub_531CD0
// UNREALRED VERIFIED [trigger-airlock-20261022] Retry direction first builds55C050 matrix from CURRENT direction, sorts abs(original seed components), derives angle from the two largest and (threshold+1)/2, then rotates local cone vector back. Near-vertical matrix snapping does not replace the original seed components used for angle selection.
// UNREALRED VERIFIED [combat-native-planes-20261104]: Deterministic retry cone has no RNG or input/output normalization. 55C050 basis is built from original seed; sorted abs(original seed) largest2 choose azimuth with float blend(threshold+1)/2 and float2pi. Near-vertical basis snapping must not alter original components used in azimuth. Native Mode3 classifiers531940/531E20/532850 and selected-room532310 reset seed from source-face normal on every restart; point-room532BA0 instead perturbs current direction.
float *__cdecl sub_531CD0(float *a1, float a2)
{
  double v2; // st7
  double v3; // st7
  float v5; // [esp+4h] [ebp-5Ch]
  float v6; // [esp+8h] [ebp-58h]
  float v7; // [esp+Ch] [ebp-54h]
  float v8; // [esp+10h] [ebp-50h]
  float v9; // [esp+14h] [ebp-4Ch]
  float v10; // [esp+18h] [ebp-48h]
  float v11; // [esp+1Ch] [ebp-44h]
  float v12[9]; // [esp+20h] [ebp-40h] BYREF
  float v13; // [esp+44h] [ebp-1Ch]
  float v14; // [esp+48h] [ebp-18h]
  float v15; // [esp+4Ch] [ebp-14h]
  float v16; // [esp+50h] [ebp-10h]
  float v17; // [esp+54h] [ebp-Ch]
  float v18; // [esp+58h] [ebp-8h]
  float v19; // [esp+5Ch] [ebp-4h]

  rf_matrix3_construct((char *)v12);
  rf_orientation_matrix_from_direction(v12, (int)a1);
  v8 = fabs(*a1);
  v18 = v8;
  v7 = fabs(a1[1]);
  v17 = v7;
  v6 = fabs(a1[2]);
  v15 = v6;
  if ( v7 > (double)v8 )
  {
    v11 = v18;
    v18 = v17;
    v17 = v11;
  }
  if ( v15 > (double)v17 )
  {
    v10 = v17;
    v17 = v15;
    v15 = v10;
    if ( v17 > (double)v18 )
    {
      v9 = v18;
      v18 = v17;
      v17 = v9;
    }
  }
  v13 = (a2 + 1.0) / 2.0;
  v16 = (v17 - v18) * v13 + v18;
  a1[2] = a2;
  v14 = v16 * 6.283185482025146;
  v5 = 1.0 - a1[2] * a1[2];
  v19 = rf_sqrt_float(v5);
  v2 = rf_cos_float(v14);
  *a1 = v2 * v19;
  v3 = rf_sin_float(v14);
  a1[1] = v3 * v19;
  return rf_vector_rotate_by_matrix3(a1, v12);
}

