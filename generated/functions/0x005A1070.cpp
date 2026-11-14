// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A1070 rf_render_prepare_three_light_records
// UNREALRED VERIFIED [stream-serializers-20261029]: Arguments render-state pointer,world-position3f,orientation3x3. Writes THREE24-byte records (direction3f,color3f) through global pointer0x1C99898,plus globals0x1CF74E0/E4/E8=coefficients0x663B1C/20/24*255. Source RGB BYTEs state+40..42; weighted scalar=.33R+.66G+.33B (weights sum1.32). First direction: flag0x1C99894 chooses(.33686,.421076,.84215099) and scale1.3*global0x66481C;otherwise direction(.45584229,.56980199,.68376839) rotated by state matrix+44,scale1.3. First RGB individually clamps(source*scale,0,255). Second direction(-.44444439,-.22222219,-.44444439) rotated by state matrix+44; second R and G both(weighted+G)*.5*.75*global0x66481C,B uses(weighted+B),NO clamp. Third disabled when global0x1C99890 set or active world count0. Else scans rf_light_active_world_records for BYTE+77 enabled,chooses NEAREST with distanceSquared<=light
// float+128,strict nearest tie keeps earlier. Direction=light position+12 minus supplied world position,normalizes; state flag0x400 forces Y=.5 then normalizes again; inverse-rotates by orientation argument. RGB=(1-sqrt(distanceSquared/radiusSquared))*255 times light RGB floats+64,+68,+72. No qualifying light zeroes entire third record. No zero-radius,output-pointer or color-clamp guard for third light. Return is path-dependent pointer,not count; no light allocation or world-list mutation.
float *__cdecl rf_render_prepare_three_light_records(int a1, float *rhs, float *a3)
{
  float *result; // eax
  float v4; // [esp+Ch] [ebp-70h]
  float v5[3]; // [esp+1Ch] [ebp-60h] BYREF
  float copy_result[3]; // [esp+28h] [ebp-54h] BYREF
  float v7; // [esp+34h] [ebp-48h]
  int v8; // [esp+38h] [ebp-44h]
  float v9; // [esp+3Ch] [ebp-40h]
  float out_vector[3]; // [esp+40h] [ebp-3Ch] BYREF
  signed int i; // [esp+4Ch] [ebp-30h]
  float v12; // [esp+50h] [ebp-2Ch]
  float destination[3]; // [esp+54h] [ebp-28h] BYREF
  float *v14; // [esp+60h] [ebp-1Ch]
  float v15; // [esp+64h] [ebp-18h]
  float *v16; // [esp+68h] [ebp-14h]
  float v17; // [esp+6Ch] [ebp-10h]
  float v18; // [esp+70h] [ebp-Ch]
  float v19; // [esp+74h] [ebp-8h]
  float v20; // [esp+78h] [ebp-4h]

  v17 = (float)*(unsigned __int8 *)(a1 + 40);
  v15 = (float)*(unsigned __int8 *)(a1 + 41);
  v19 = (float)*(unsigned __int8 *)(a1 + 42);
  v18 = v17 * 0.3300000131130219 + v15 * 0.6600000262260437 + v19 * 0.3300000131130219;
  unk_1CF74E0 = flt_663B1C * 255.0;
  unk_1CF74E4 = flt_663B20 * 255.0;
  unk_1CF74E8 = flt_663B24 * 255.0;
  v16 = unk_1C99898;
  v20 = 1.3;
  if ( unk_1C99894 )
  {
    v20 = v20 * flt_66481C;
    rf_vector3_set_components_thiscall(v16, 0.33686, 0.421076, 0.84215099);
  }
  else
  {
    rf_vector3_set_components_thiscall(v16, 0.45584229, 0.56980199, 0.68376839);
    rf_vector_rotate_by_matrix3(v16, (float *)(a1 + 44));
  }
  v16[3] = v17 * v20;
  rf_float_clamp_in_place(v16 + 3, 0.0, 255.0);
  v16[4] = v15 * v20;
  rf_float_clamp_in_place(v16 + 4, 0.0, 255.0);
  v16[5] = v19 * v20;
  rf_float_clamp_in_place(v16 + 5, 0.0, 255.0);
  v16 += 6;
  rf_vector3_set_components_thiscall(v16, -0.44444439, -0.22222219, -0.44444439);
  rf_vector_rotate_by_matrix3(v16, (float *)(a1 + 44));
  v16[3] = (v18 + v15) * 0.5 * 0.75 * flt_66481C;
  v16[4] = (v18 + v15) * 0.5 * 0.75 * flt_66481C;
  v16[5] = (v18 + v19) * 0.5 * 0.75 * flt_66481C;
  v16 += 6;
  if ( unk_1C99890 || !rf_light_active_world_count )
    goto LABEL_18;
  v14 = nullptr;
  rf_vector3_set_components_return_destination(destination, 0.0, 0.0, 0.0);
  v12 = 3.4028235e38;
  for ( i = 0; i < (int)rf_light_active_world_count; ++i )
  {
    v8 = rf_light_active_world_records[i];
    if ( *(_BYTE *)(v8 + 77) )
    {
      rf_vector_subtract((const float *)(v8 + 12), out_vector, rhs);
      v9 = rf_vector_length_squared(out_vector);
      if ( *(float *)(v8 + 128) >= (double)v9 && v12 > (double)v9 )
      {
        v14 = (float *)v8;
        rf_vector_copy(destination, copy_result, out_vector);
        v12 = v9;
      }
    }
  }
  if ( v14 )
  {
    rf_vector_copy(v16, v5, destination);
    rf_vector_normalize(v16);
    if ( (*(_DWORD *)a1 & 0x400) != 0 )
    {
      v16[1] = 0.5;
      rf_vector_normalize(v16);
    }
    rf_matrix3_inverse_rotate_vector(v16, a3);
    v4 = v12 / v14[32];
    v7 = (1.0 - rf_sqrt_float(v4)) * 255.0;
    v16[3] = v7 * v14[16];
    result = v16;
    v16[4] = v7 * v14[17];
    v16[5] = v7 * v14[18];
  }
  else
  {
LABEL_18:
    rf_vector3_set_components_thiscall(v16, 0.0, 0.0, 0.0);
    return rf_vector3_set_components_thiscall(v16 + 3, 0.0, 0.0, 0.0);
  }
  return result;
}

