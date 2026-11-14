// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00531E20 rf_geomod_fragment_classify_spatial_ray
// UNREALRED VERIFIED [combat-native-planes-20261104]: Mode3 spatial classifier uses opposite-operand terrain policy517CC0 and source-face-normal reseeding on every531CD0 restart. Its geometry owner/extent and traversal are distinct from selected-room liquid classifier532310. Preserve historical host replay math separately when correcting current retry/projection semantics.
char __thiscall rf_geomod_fragment_classify_spatial_ray(float *this, float *a2)
{
  int first_dword; // eax
  BOOL v3; // esi
  int v4; // eax
  float copy_result[3]; // [esp+10h] [ebp-10A8h] BYREF
  float destination[3]; // [esp+1Ch] [ebp-109Ch] BYREF
  int m; // [esp+28h] [ebp-1090h]
  int k; // [esp+2Ch] [ebp-108Ch]
  int j; // [esp+30h] [ebp-1088h]
  float *v12; // [esp+34h] [ebp-1084h]
  _DWORD *v13; // [esp+38h] [ebp-1080h]
  int v14[3]; // [esp+3Ch] [ebp-107Ch] BYREF
  int v15[3]; // [esp+48h] [ebp-1070h] BYREF
  int v16; // [esp+54h] [ebp-1064h]
  char v17; // [esp+5Bh] [ebp-105Dh]
  float v18; // [esp+5Ch] [ebp-105Ch]
  int v19; // [esp+60h] [ebp-1058h]
  float v20; // [esp+64h] [ebp-1054h]
  _DWORD v21[1025]; // [esp+68h] [ebp-1050h]
  int i; // [esp+106Ch] [ebp-4Ch]
  float v23[15]; // [esp+1070h] [ebp-48h] BYREF
  int v24[3]; // [esp+10ACh] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v24);
  rf_geomod_face_centroid(this, (float *)v24);
  v17 = 0;
  v20 = a2[21] - a2[18];
  v20 = a2[22] - a2[19] + v20;
  v20 = a2[23] - a2[20] + v20;
  v20 = v20 + 0.00009999999747378752;
  ++rf_geomod_classification_attempt_count;
  v18 = 0.97530001;
  rf_vector_construct_no_unwind((char *)v23, 0x3Cu, 1, (void *(__thiscall *)(void *))rf_geomod_face_ray_query_init);
  for ( i = 0; i < 1; ++i )
  {
    if ( i )
    {
      rf_vector3_default_construct_noop(v14);
      rf_random_unit_vector_from_z_and_azimuth((float *)v14);
      rf_geomod_face_ray_query_begin((int)&v23[15 * i], (int)this, (float *)v24, (float *)v14, v20, v17);
    }
    else
    {
      rf_vector3_copy_return_destination((float *)v15, this);
      sub_531CD0((float *)v15, v18);
      rf_geomod_face_ray_query_begin((int)&v23[15 * i], (int)this, (float *)v24, (float *)v15, v20, v17);
    }
  }
  v16 = 0;
LABEL_8:
  v19 = 0;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(a2 + 36);
    if ( i >= first_dword )
      break;
    v13 = *(_DWORD **)sub_552200((_DWORD *)a2 + 36, i);
    if ( !unknown_libname_11(v13) )
      v21[v19++] = v13[15];
  }
  while ( v19 > 0 )
  {
    v12 = (float *)v21[--v19];
    if ( rf_geomod_face_query_segment_bounds_overlap(v23, v12, v12 + 3) )
    {
      if ( *((_DWORD *)v12 + 8) )
        v21[v19++] = *((_DWORD *)v12 + 8);
      if ( *((_DWORD *)v12 + 9) )
        v21[v19++] = *((_DWORD *)v12 + 9);
      for ( j = rf_receiver_get_first_dword(v12 + 6); j; j = rf_face_next_spatial_node_link(j) )
      {
        if ( (float *)j != this )
        {
          v3 = rf_geomod_face_operand_get((_DWORD *)(j + 40));
          if ( v3 != rf_geomod_face_operand_get((_DWORD *)this + 10)
            && rf_geomod_terrain_component_face_eligible((__int16 *)(j + 40)) )
          {
            for ( k = 0; k < 1; ++k )
            {
              if ( rf_geomod_face_ray_query_accumulate((int)&v23[15 * k], j) )
              {
                if ( ++v16 < 16 )
                {
                  if ( v18 > -1.0 )
                  {
                    v18 = v18 - 0.1357900053262711;
                    if ( v18 < -1.0 )
                      v18 = -1.0;
                  }
                  for ( m = 0; m < 1; ++m )
                  {
                    rf_vector3_default_construct_noop(destination);
                    if ( m )
                    {
                      rf_random_unit_vector_from_z_and_azimuth(destination);
                    }
                    else
                    {
                      rf_vector_copy(destination, copy_result, this);
                      sub_531CD0(destination, v18);
                    }
                    rf_geomod_face_ray_query_begin((int)&v23[15 * m], (int)this, (float *)v24, destination, v20, v17);
                  }
                  ++rf_geomod_classification_retry_count;
                  goto LABEL_8;
                }
              }
            }
          }
        }
      }
    }
  }
  v4 = rf_geomod_face_ray_query_class_get((int)v23);
  rf_geomod_face_boolean_class_set((int *)this + 10, v4);
  return 1;
}

