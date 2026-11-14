// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00532BA0 sub_532BA0
// UNREALRED VERIFIED [trigger-airlock-20261022] Room point query uses eligible oriented faces (including portal faces) and excludes authored sky rooms. Finite ray length is summed world bounds extents+.0001; starts from direction(0,1,0), perturbed by531CD0 at threshold.97530001. Positive near-boundary hits request retries, decrementing threshold by.1357900053 clamped-1, at most16 attempts. Current direction seeds each retry. Nearest class2 or no face returns null; otherwise returns winning face room+68. Spatial tree changes traversal order but does not replace face classification with containing room AABBs.
// UNREALRED VERIFIED [particle-contact-geometry-20261104] Resolves a point using ordinary world-room array +156, excluding detail rooms moved to +168 by 0x517BE0 and skipping authored sky rooms. Uses eligible oriented faces, finite ray length equal to world extent sum + 0.0001, initial RF direction (0,1,0), threshold 0.97530001, and up to 15 restarts with descending threshold clamped to -1. Each retry perturbs the current direction; unlike selected-room classifier 0x532310, it does not recopy a face-normal seed. Per room, scans ordered tree node faces with LIFO child order (+36 before +32), or the room face list if there is no root. Nearest query class 2 or no winning face returns null; otherwise returns winning face room +68. Room bounds alone are not the containment test.
int __cdecl sub_532BA0(float *a1, float *a2)
{
  int first_dword; // eax
  int k; // [esp+Ch] [ebp-1070h]
  int j; // [esp+10h] [ebp-106Ch]
  int v6; // [esp+14h] [ebp-1068h]
  int v7; // [esp+18h] [ebp-1064h]
  _DWORD v8[1024]; // [esp+1Ch] [ebp-1060h]
  _BYTE *v9; // [esp+101Ch] [ebp-60h]
  int v10; // [esp+1020h] [ebp-5Ch]
  float v11; // [esp+1024h] [ebp-58h]
  int v12[3]; // [esp+1028h] [ebp-54h] BYREF
  float v13; // [esp+1034h] [ebp-48h]
  int i; // [esp+1038h] [ebp-44h]
  float v15[10]; // [esp+103Ch] [ebp-40h] BYREF
  int v16; // [esp+1064h] [ebp-18h]
  int v17; // [esp+1078h] [ebp-4h]

  ++unk_D6560C;
  v13 = a1[21] - a1[18];
  v13 = a1[22] - a1[19] + v13;
  v13 = a1[23] - a1[20] + v13;
  v13 = v13 + 0.00009999999747378752;
  v11 = 0.97530001;
  rf_geomod_face_ray_query_init((char *)v15);
  rf_vector3_set_components_return_destination((float *)v12, 0.0, 1.0, 0.0);
  sub_531CD0((float *)v12, 0.97530001);
  rf_geomod_face_ray_query_begin((int)v15, 0, a2, (float *)v12, v13, 0);
  v10 = 0;
LABEL_2:
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(a1 + 39);
    if ( i >= first_dword )
      break;
    v9 = *(_BYTE **)sub_552200((_DWORD *)a1 + 39, i);
    if ( !rf_room_is_authored_sky(v9) )
    {
      if ( *((_DWORD *)v9 + 15) )
      {
        v8[0] = *((_DWORD *)v9 + 15);
        v7 = 1;
        while ( v7 > 0 )
        {
          v6 = v8[--v7];
          if ( rf_geomod_face_query_segment_bounds_overlap(v15, (float *)v6, (float *)(v6 + 12)) )
          {
            if ( *(_DWORD *)(v6 + 32) )
              v8[v7++] = *(_DWORD *)(v6 + 32);
            if ( *(_DWORD *)(v6 + 36) )
              v8[v7++] = *(_DWORD *)(v6 + 36);
            for ( j = rf_receiver_get_first_dword((void *)(v6 + 24)); j; j = rf_face_next_spatial_node_link(j) )
            {
              if ( rf_geomod_face_flags_eligible((_DWORD *)(j + 40)) )
              {
                if ( rf_geomod_face_ray_query_accumulate((int)v15, j) )
                {
                  if ( ++v10 < 16 )
                  {
                    if ( v11 > -1.0 )
                    {
                      v11 = v11 - 0.1357900053262711;
                      if ( v11 < -1.0 )
                        v11 = -1.0;
                    }
                    goto LABEL_23;
                  }
                }
              }
            }
          }
        }
      }
      else
      {
        for ( k = rf_receiver_get_first_dword(v9 + 40); k; k = rf_face_next_room_link(k) )
        {
          if ( rf_geomod_face_flags_eligible((_DWORD *)(k + 40)) )
          {
            if ( rf_geomod_face_ray_query_accumulate((int)v15, k) )
            {
              if ( ++v10 < 16 )
              {
                if ( v11 > -1.0 )
                {
                  v11 = v11 - 0.1357900053262711;
                  if ( v11 < -1.0 )
                    v11 = -1.0;
                }
LABEL_23:
                sub_531CD0((float *)v12, v11);
                rf_geomod_face_ray_query_begin((int)v15, 0, a2, (float *)v12, v13, 0);
                ++rf_geomod_classification_retry_count;
                goto LABEL_2;
              }
            }
          }
        }
      }
    }
  }
  if ( !v16 )
    return 0;
  v17 = rf_geomod_face_ray_query_class_get((int)v15);
  if ( v17 == 2 )
    return 0;
  else
    return *(_DWORD *)(v16 + 68);
}

