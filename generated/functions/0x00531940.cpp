// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00531940 rf_geomod_fragment_classify_linear_ray
// UNREALRED VERIFIED [combat-native-planes-20261104]: Mode3 linear classifier scans opposite-operand terrain-eligible faces via517CC0 (flags4/8 excluded and signed portal value<=0), with world-bounds extent-sum ray length. Each restart recopies source face normal before531CD0. This collection/filter/extent differs from selected-room Mode6 532310 even though retry/projection math is shared.
char __thiscall rf_geomod_fragment_classify_linear_ray(float *this, float *a2, int a3)
{
  BOOL v3; // esi
  int v4; // eax
  float copy_result[3]; // [esp+10h] [ebp-A4h] BYREF
  float destination[3]; // [esp+1Ch] [ebp-98h] BYREF
  int m; // [esp+28h] [ebp-8Ch]
  int k; // [esp+2Ch] [ebp-88h]
  int v11[3]; // [esp+30h] [ebp-84h] BYREF
  int v12[3]; // [esp+3Ch] [ebp-78h] BYREF
  int j; // [esp+48h] [ebp-6Ch]
  int v14; // [esp+4Ch] [ebp-68h]
  _DWORD v15[2]; // [esp+50h] [ebp-64h]
  int v16; // [esp+58h] [ebp-5Ch]
  char v17; // [esp+5Fh] [ebp-55h]
  float v18; // [esp+60h] [ebp-54h]
  float v19; // [esp+64h] [ebp-50h]
  int i; // [esp+68h] [ebp-4Ch]
  char v21[60]; // [esp+6Ch] [ebp-48h] BYREF
  int v22[3]; // [esp+A8h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v22);
  rf_geomod_face_centroid(this, (float *)v22);
  v17 = 0;
  v19 = a2[21] - a2[18];
  v19 = a2[22] - a2[19] + v19;
  v19 = a2[23] - a2[20] + v19;
  v19 = v19 + 0.00009999999747378752;
  ++rf_geomod_classification_attempt_count;
  v18 = 0.97530001;
  rf_vector_construct_no_unwind(v21, 0x3Cu, 1, (void *(__thiscall *)(void *))rf_geomod_face_ray_query_init);
  for ( i = 0; i < 1; ++i )
  {
    if ( i )
    {
      rf_vector3_default_construct_noop(v11);
      rf_random_unit_vector_from_z_and_azimuth((float *)v11);
      rf_geomod_face_ray_query_begin((int)&v21[60 * i], (int)this, (float *)v22, (float *)v11, v19, v17);
    }
    else
    {
      rf_vector3_copy_return_destination((float *)v12, this);
      sub_531CD0((float *)v12, v18);
      rf_geomod_face_ray_query_begin((int)&v21[60 * i], (int)this, (float *)v22, (float *)v12, v19, v17);
    }
  }
  v15[0] = a2 + 28;
  v16 = 1;
  if ( a3 )
    v15[v16++] = a3;
  v14 = 0;
LABEL_10:
  for ( i = 0; i < v16; ++i )
  {
    for ( j = rf_receiver_get_first_dword((void *)v15[i]); j; j = rf_solid_face_next_link(j) )
    {
      v3 = rf_geomod_face_operand_get((_DWORD *)(j + 40));
      if ( v3 != rf_geomod_face_operand_get((_DWORD *)this + 10)
        && rf_geomod_terrain_component_face_eligible((__int16 *)(j + 40)) )
      {
        for ( k = 0; k < 1; ++k )
        {
          if ( rf_geomod_face_ray_query_accumulate((int)&v21[60 * k], j) )
          {
            if ( ++v14 < 16 )
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
                rf_geomod_face_ray_query_begin((int)&v21[60 * m], (int)this, (float *)v22, destination, v19, v17);
              }
              ++rf_geomod_classification_retry_count;
              goto LABEL_10;
            }
          }
        }
      }
    }
  }
  v4 = rf_geomod_face_ray_query_class_get((int)v21);
  rf_geomod_face_boolean_class_set((int *)this + 10, v4);
  return 1;
}

