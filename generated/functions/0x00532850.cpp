// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00532850 sub_532850
// UNREALRED VERIFIED [combat-native-planes-20261104]: Spatial-fast Mode3 query uses supplied spatial-tree bounds for ray extent and terrain eligibility517CC0, resetting retry seed from the source face normal. It shares low-level531CD0/5337E0 math but is not the selected-room/portal-allowing Mode6 query.
char __thiscall sub_532850(float *this, int a2, float *a3)
{
  int v3; // eax
  float copy_result[3]; // [esp+Ch] [ebp-107Ch] BYREF
  int i; // [esp+18h] [ebp-1070h]
  float *v8; // [esp+1Ch] [ebp-106Ch]
  int v9; // [esp+20h] [ebp-1068h]
  char v10; // [esp+27h] [ebp-1061h]
  float v11; // [esp+28h] [ebp-1060h]
  int v12; // [esp+2Ch] [ebp-105Ch]
  float destination[3]; // [esp+30h] [ebp-1058h] BYREF
  float v14; // [esp+3Ch] [ebp-104Ch]
  _DWORD v15[1024]; // [esp+40h] [ebp-1048h]
  float v16[15]; // [esp+1040h] [ebp-48h] BYREF
  int v17[3]; // [esp+107Ch] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v17);
  rf_geomod_face_centroid(this, (float *)v17);
  v10 = 0;
  v14 = a3[3] - *a3;
  v14 = a3[4] - a3[1] + v14;
  v14 = a3[5] - a3[2] + v14;
  v14 = v14 + 0.00009999999747378752;
  ++rf_geomod_classification_attempt_count;
  v11 = 0.97530001;
  rf_geomod_face_ray_query_init((char *)v16);
  rf_vector3_copy_return_destination(destination, this);
  sub_531CD0(destination, 0.97530001);
  rf_geomod_face_ray_query_begin((int)v16, (int)this, (float *)v17, destination, v14, 0);
  v9 = 0;
LABEL_2:
  v15[0] = a3;
  v12 = 1;
  while ( v12 > 0 )
  {
    v8 = (float *)v15[--v12];
    if ( rf_geomod_face_query_segment_bounds_overlap(v16, v8, v8 + 3) )
    {
      if ( *((_DWORD *)v8 + 8) )
        v15[v12++] = *((_DWORD *)v8 + 8);
      if ( *((_DWORD *)v8 + 9) )
        v15[v12++] = *((_DWORD *)v8 + 9);
      for ( i = rf_receiver_get_first_dword(v8 + 6); i; i = rf_face_next_spatial_node_link(i) )
      {
        if ( rf_geomod_terrain_component_face_eligible((__int16 *)(i + 40)) )
        {
          if ( rf_geomod_face_ray_query_accumulate((int)v16, i) )
          {
            if ( ++v9 < 16 )
            {
              if ( v11 > -1.0 )
              {
                v11 = v11 - 0.1357900053262711;
                if ( v11 < -1.0 )
                  v11 = -1.0;
              }
              rf_vector_copy(destination, copy_result, this);
              sub_531CD0(destination, v11);
              rf_geomod_face_ray_query_begin((int)v16, (int)this, (float *)v17, destination, v14, v10);
              ++rf_geomod_classification_retry_count;
              goto LABEL_2;
            }
          }
        }
      }
    }
  }
  v3 = rf_geomod_face_ray_query_class_get((int)v16);
  rf_geomod_face_boolean_class_set((int *)this + 10, v3);
  return 1;
}

