// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051C040 rf_geomod_component_recenter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mass sampling and inverse inertia,recentering,UV cuts and density,finite epsilon tests,original ECX/stack flow and PE bytes): Thiscall solid,outOffset RET4. Zero output before signed vertexcount120 check; count<1 returns that count without altering solid. For nonempty, derive bounds72/84 from first vertex and min-else-max point inclusion, expand by F32epsilon0.000099999997, compute offset=(min+max)*0.5 via F32 vector helpers. Subtract offset from both bounds and ALL vertices120. Radius96=sqrt(max ORDERED squared vertex distance from origin), starting0 (NaN distances ignored), set center100..108 EXACT zero. Finalize each face112 with arguments0,0. For signed lightmap WORD54>=0 fetch descriptor192[index], copy finalized face plane to descriptor108, select projection axes into92/96/100, subtract offset from descriptor
// vectors52/64. Scan face corners projected coordinates using axes96/100 and strict helper min/max. Rebuild scales76=(width24-2)/atlasWidth(page12+4)/(maxU-minU),80=(height28-2)/atlasHeight(page12+8)/(maxV-minV), offsets84=-minU*scaleU+(atlasX16+1)/atlasWidth,88 similarlyY20. No zero extent, page pointer, shared descriptor, or alias guard; each lightmapped face updates independently, so shared descriptor bounds may be subtracted repeatedly. Uses AABB midpoint, not vertex mean/mass centroid or Ritter sphere. EAX loop residue (normally0 after faces), no success status. Does not translate room/spatial tree bounds or rebuild tree.
int __thiscall rf_geomod_component_recenter(float *this, float *destination)
{
  int result; // eax
  int first_dword; // eax
  float *v4; // eax
  float *v5; // eax
  int v6; // eax
  int v7; // [esp+10h] [ebp-90h]
  float v9[3]; // [esp+18h] [ebp-88h] BYREF
  float scaled_result[3]; // [esp+24h] [ebp-7Ch] BYREF
  float sum_result[3]; // [esp+30h] [ebp-70h] BYREF
  float v12[3]; // [esp+3Ch] [ebp-64h] BYREF
  float copy_result[3]; // [esp+48h] [ebp-58h] BYREF
  float v14; // [esp+54h] [ebp-4Ch]
  float v15; // [esp+58h] [ebp-48h]
  int v16; // [esp+5Ch] [ebp-44h] BYREF
  float v17; // [esp+60h] [ebp-40h]
  float v18; // [esp+64h] [ebp-3Ch]
  int v19; // [esp+68h] [ebp-38h]
  float v20; // [esp+6Ch] [ebp-34h]
  int v21; // [esp+70h] [ebp-30h] BYREF
  float v22; // [esp+74h] [ebp-2Ch]
  int v23; // [esp+78h] [ebp-28h] BYREF
  int k; // [esp+7Ch] [ebp-24h]
  float v25; // [esp+80h] [ebp-20h]
  char v26; // [esp+87h] [ebp-19h]
  float v27; // [esp+88h] [ebp-18h]
  float v28; // [esp+8Ch] [ebp-14h]
  float *j; // [esp+90h] [ebp-10h]
  int i; // [esp+94h] [ebp-Ch]
  float *source; // [esp+98h] [ebp-8h]
  float v32; // [esp+9Ch] [ebp-4h]

  rf_vector3_zero_return_destination(destination);
  result = rf_receiver_get_first_dword(this + 30);
  if ( result >= 1 )
  {
    source = *(float **)sub_552200((_DWORD *)this + 30, 0);
    rf_vector_copy(this + 18, copy_result, source);
    rf_vector_copy(this + 21, v12, source);
    for ( i = 1; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword(this + 30);
      if ( i >= first_dword )
        break;
      source = *(float **)sub_552200((_DWORD *)this + 30, i);
      rf_aabb_include_point_min_else_max(this + 18, this + 21, source);
    }
    rf_vector3_subtract_scalar_in_place(this + 18, 0.000099999997);
    rf_vector3_add_scalar_in_place(this + 21, 0.000099999997);
    v4 = rf_vector_add(this + 18, sum_result, this + 21);
    v5 = rf_vector_multiply_scalar(v4, scaled_result, 0.5);
    rf_vector_copy(destination, v9, v5);
    rf_vector_subtract_in_place(this + 18, destination);
    rf_vector_subtract_in_place(this + 21, destination);
    v28 = 0.0;
    for ( i = 0; ; ++i )
    {
      v6 = rf_receiver_get_first_dword(this + 30);
      if ( i >= v6 )
        break;
      source = *(float **)sub_552200((_DWORD *)this + 30, i);
      rf_vector_subtract_in_place(source, destination);
      v32 = rf_vector_length_squared(source);
      if ( v28 < (double)v32 )
        v28 = v32;
    }
    *(this + 24) = rf_sqrt_float(v28);
    rf_vector3_zero_return_destination(this + 25);
    result = rf_receiver_get_first_dword(this + 28);
    for ( j = (float *)result; j; j = (float *)result )
    {
      rf_geomod_face_finalize_geometry((int)j, 0, 0);
      if ( *((__int16 *)j + 27) > -1 )
      {
        v19 = *(_DWORD *)sub_552200((_DWORD *)this + 48, *((__int16 *)j + 27));
        v26 = 1;
        v18 = 0.0;
        v22 = 0.0;
        v25 = 0.0;
        v20 = 0.0;
        rf_plane_copy((float *)(v19 + 108), j);
        rf_face_projection_axes_select(j, &v21, &v23, &v16);
        *(_DWORD *)(v19 + 92) = v21;
        *(_DWORD *)(v19 + 96) = v23;
        *(_DWORD *)(v19 + 100) = v16;
        rf_vector_subtract_in_place((float *)(v19 + 52), destination);
        rf_vector_subtract_in_place((float *)(v19 + 64), destination);
        for ( k = *((_DWORD *)j + 16); k; k = v7 )
        {
          v14 = *(float *)rf_vector_component_address_unchecked(*(char **)k, *(_DWORD *)(v19 + 96));
          v15 = *(float *)rf_vector_component_address_unchecked(*(char **)k, *(_DWORD *)(v19 + 100));
          if ( v26 )
          {
            v26 = 0;
            v25 = v14;
            v18 = v14;
            v20 = v15;
            v22 = v15;
          }
          else
          {
            v18 = rf_float_minimum_two_values(v14, v18);
            v22 = rf_float_minimum_two_values(v15, v22);
            v25 = rf_float_maximum_two_values(v14, v25);
            v20 = rf_float_maximum_two_values(v15, v20);
          }
          if ( *(_DWORD *)(k + 20) == *((_DWORD *)j + 16) )
            v7 = 0;
          else
            v7 = *(_DWORD *)(k + 20);
        }
        v27 = v25 - v18;
        v17 = v20 - v22;
        *(float *)(v19 + 76) = (double)(*(_DWORD *)(v19 + 24) - 2) / (double)*(int *)(*(_DWORD *)(v19 + 12) + 4) / v27;
        *(float *)(v19 + 80) = (double)(*(_DWORD *)(v19 + 28) - 2) / (double)*(int *)(*(_DWORD *)(v19 + 12) + 8) / v17;
        *(float *)(v19 + 84) = -v18 * *(float *)(v19 + 76)
                             + ((double)*(int *)(v19 + 16) + 1.0) / (double)*(int *)(*(_DWORD *)(v19 + 12) + 4);
        *(float *)(v19 + 88) = -v22 * *(float *)(v19 + 80)
                             + ((double)*(int *)(v19 + 20) + 1.0) / (double)*(int *)(*(_DWORD *)(v19 + 12) + 8);
      }
      result = rf_solid_face_next_link((int)j);
    }
  }
  return result;
}

