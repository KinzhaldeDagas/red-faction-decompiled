// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CBAA0 sub_4CBAA0
// UNREALRED VERIFIED [combat-particle-wind-20261029]: Called only for particle wind nibble bits28..31 nonzero, after swirl/acceleration/gravity. Find first region at current post-move point; flag2 rejects unless particle current-frame contact flag8000 is set, without searching later regions. Otherwise direction is region forward(+48), or normalized particle-center if flag10. Nonzero region nibble bits16..19 OVERRIDES either with cone about region forward, min-dot1-(n/64)^2. Continuous branch adds direction*strength*delta to velocity. Flag2 branch preserves transverse velocity and replaces axial speed with min(strength,oldAxial+strength), no delta factor. Radial exact-center normalization has no native zero guard (558EF0); handle invalid direction explicitly in the Unreal adapter rather than inventing an axis.
float *__cdecl sub_4CBAA0(int a1, float a2)
{
  float *result; // eax
  const float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float v8[3]; // [esp-8h] [ebp-ACh] BYREF
  float scalar; // [esp+4h] [ebp-A0h]
  float v10; // [esp+8h] [ebp-9Ch]
  float v11[3]; // [esp+Ch] [ebp-98h] BYREF
  float v12[3]; // [esp+18h] [ebp-8Ch] BYREF
  float sum_result[3]; // [esp+24h] [ebp-80h] BYREF
  float v14[3]; // [esp+30h] [ebp-74h] BYREF
  float scaled_result[4]; // [esp+3Ch] [ebp-68h] BYREF
  float v16[3]; // [esp+4Ch] [ebp-58h] BYREF
  float copy_result[3]; // [esp+58h] [ebp-4Ch] BYREF
  _BYTE v18[12]; // [esp+64h] [ebp-40h] BYREF
  float v19; // [esp+70h] [ebp-34h]
  float lhs[3]; // [esp+74h] [ebp-30h] BYREF
  float v21; // [esp+80h] [ebp-24h] BYREF
  float destination[3]; // [esp+84h] [ebp-20h] BYREF
  float out_vector[3]; // [esp+90h] [ebp-14h] BYREF
  float v24; // [esp+9Ch] [ebp-8h]
  float *v25; // [esp+A0h] [ebp-4h]

  result = (float *)rf_push_region_find_containing_point((const float *)(a1 + 12));
  v25 = result;
  if ( result )
  {
    if ( ((_DWORD)v25[2] & 2) == 0 || (result = (float *)a1, (*(_DWORD *)(a1 + 88) & 0x8000) != 0) )
    {
      v24 = v25[25];
      rf_vector3_default_construct_noop(destination);
      rf_vector_subtract((const float *)(a1 + 12), out_vector, v25 + 3);
      if ( ((_DWORD)v25[2] & 0x10) != 0 )
      {
        v3 = (const float *)rf_vector3_normalized_copy_unchecked(out_vector, (int)v18);
        rf_vector_copy(destination, copy_result, v3);
      }
      else
      {
        rf_vector_copy(destination, v16, v25 + 12);
      }
      if ( ((_DWORD)v25[2] & 0xF0000) != 0 )
      {
        v21 = rf_flag_nibble_quadratic_attenuation((int)v25);
        rf_float_clamp_in_place(&v21, -1.0, 1.0);
        scalar = v21;
        rf_vector3_copy_return_destination(v8, v25 + 12);
        rf_random_unit_vector_in_cone(destination, v8[0], v8[1], v8[2], scalar);
      }
      if ( ((_DWORD)v25[2] & 2) != 0 )
      {
        v19 = rf_vector_dot((float *)(a1 + 24), destination);
        v4 = rf_vector_multiply_scalar(destination, scaled_result, v19);
        rf_vector_subtract((const float *)(a1 + 24), lhs, v4);
        v10 = v19 + v24;
        scalar = rf_float_minimum_two_values(v24, v10);
        v5 = rf_vector_multiply_scalar(destination, v14, scalar);
        v6 = rf_vector_add(lhs, sum_result, v5);
        return rf_vector_copy((float *)(a1 + 24), v12, v6);
      }
      else
      {
        v24 = v24 * a2;
        v7 = rf_vector_multiply_scalar(destination, v11, v24);
        return rf_vector_accumulate((float *)(a1 + 24), v7);
      }
    }
  }
  return result;
}

