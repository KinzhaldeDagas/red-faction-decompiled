// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583D20 rf_quaternion_interpolate
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Cdecl output,A,B,float alpha. Repeatedly adds1 while alpha<0 and subtracts1 while alpha>1 (can hang for infinity/very large float); does not clamp. Compares squared lengths of A+B and A-B; picks -B on <=, otherwise B. Dot(A,chosenB) NaN copies A and exits. Dot+1<=~1e-6 uses sine half-pi weights with orthogonal(-B.y,B.x,-B.w,B.z); otherwise1-dot>~1e-6 uses acos/sine weights. NEAR-IDENTICAL branch sets weights0,1 and copies chosen B even at alpha0, not a linear blend. Every non-NaN path forces output.w=~1e-6 if exactly0. No final normalization (some callers normalize separately), dot clamp or finite-alpha guard. Inputs assumed sensible; implementation is not robust general-purpose SLERP.
void __cdecl rf_quaternion_interpolate(float *a1, float *a2, float *a3, float a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  double v7; // st7
  double v8; // st7
  float *X_4; // [esp+4h] [ebp-90h]
  float *X_4a; // [esp+4h] [ebp-90h]
  float v11; // [esp+8h] [ebp-8Ch]
  float v12; // [esp+Ch] [ebp-88h]
  float v13; // [esp+10h] [ebp-84h]
  float v14; // [esp+14h] [ebp-80h]
  float v15[4]; // [esp+18h] [ebp-7Ch] BYREF
  float v16[4]; // [esp+28h] [ebp-6Ch] BYREF
  float v17[4]; // [esp+38h] [ebp-5Ch] BYREF
  float v18[4]; // [esp+48h] [ebp-4Ch] BYREF
  float v19[4]; // [esp+58h] [ebp-3Ch] BYREF
  float v20; // [esp+68h] [ebp-2Ch]
  float v21; // [esp+6Ch] [ebp-28h]
  float v22; // [esp+70h] [ebp-24h]
  float v23; // [esp+74h] [ebp-20h]
  float v24; // [esp+78h] [ebp-1Ch]
  float v25; // [esp+7Ch] [ebp-18h]
  float v26; // [esp+80h] [ebp-14h] BYREF
  float v27; // [esp+84h] [ebp-10h]
  float v28; // [esp+88h] [ebp-Ch]
  float v29; // [esp+8Ch] [ebp-8h]
  float v30; // [esp+90h] [ebp-4h]

  while ( a4 < 0.0 )
    a4 = a4 + 1.0;
  while ( a4 > 1.0 )
    a4 = a4 - 1.0;
  rf_float4_construct_zero_zero_zero_one(&v26);
  X_4 = rf_float4_subtract_to_destination(a2, v19, a3);
  v4 = rf_float4_subtract_to_destination(a2, v18, a3);
  v25 = rf_float4_dot(v4, X_4);
  X_4a = rf_float4_add_to_destination(a2, v17, a3);
  v5 = rf_float4_add_to_destination(a2, v16, a3);
  v22 = rf_float4_dot(v5, X_4a);
  if ( v22 <= (double)v25 )
  {
    v6 = rf_float4_negate_to_destination(a3, v15);
    rf_float4_copy_return_destination(&v26, v6);
  }
  else
  {
    rf_float4_copy_return_destination(&v26, a3);
  }
  v30 = rf_float4_dot(a2, &v26);
  if ( _isnan(v30) )
  {
    rf_float4_copy_return_destination(a1, a2);
  }
  else if ( v30 + 1.0 <= 0.0000009999999974752427 )
  {
    v12 = (1.0 - a4) * 1.570796370506287;
    v23 = rf_sin_float(v12);
    v11 = a4 * 1.570796370506287;
    v24 = rf_sin_float(v11);
    *a1 = -v27;
    a1[1] = v26;
    a1[2] = -v29;
    a1[3] = v28;
    *a1 = v23 * *a2 + v24 * *a1;
    a1[1] = v23 * a2[1] + v24 * a1[1];
    a1[2] = v23 * a2[2] + v24 * a1[2];
    a1[3] = v23 * a2[3] + v24 * a1[3];
    if ( a1[3] == 0.0 )
      a1[3] = 0.000001;
  }
  else
  {
    if ( 1.0 - v30 > 0.0000009999999974752427 )
    {
      v20 = rf_acos_float(v30);
      v21 = 1.0 / rf_sin_float(v20);
      v14 = (1.0 - a4) * v20;
      v7 = rf_sin_float(v14);
      v23 = v7 * v21;
      v13 = a4 * v20;
      v8 = rf_sin_float(v13);
      v24 = v8 * v21;
    }
    else
    {
      v23 = 0.0;
      v24 = 1.0;
    }
    *a1 = v23 * *a2 + v24 * v26;
    a1[1] = v23 * a2[1] + v24 * v27;
    a1[2] = v23 * a2[2] + v24 * v28;
    a1[3] = v23 * a2[3] + v24 * v29;
    if ( a1[3] == 0.0 )
      a1[3] = 0.000001;
  }
}

