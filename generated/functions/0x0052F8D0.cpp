// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052F8D0 rf_world_collision_sweep
// UNREALRED VERIFIED [combat-selected-drop-20261111]: Selected drop439220 passes finalargument1 at43957D. Thus52F8D0 RESETS bestfraction to1 at entry, overriding callerFLT_MAX preload439577. Effective selected-drop maxT is1: interiorplaneT1 may win, edgeT1 rejects strictmax. Resetscount/edgeflag/face; zero-motion squaredlength0 produces no hit. Flags2000 has firsthitbit1OFF: traverse all eligible rooms/references/faces and keep ordered nearest/equal-plane replacements. Retained host traversal omits native process-global cache history explicitly.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: For geometry pickup query bit1, traverses eligible cached/current room references/spatial roots and exits on first accepted hit; world query bit4 means input already world-space, mover absence bit4 transforms start/end by supplied current frame. Radius0 chooses point face branch. All-zero squared displacement yields no hit. Existing global cache-history ordering is not evidence that render triangles or generic UE traces are equivalent.
void __thiscall rf_world_collision_sweep(char *this, int a2, int a3, char a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  int v9; // eax
  int first_dword; // eax
  int v11; // eax
  float v13[3]; // [esp+8h] [ebp-FCh] BYREF
  float v14[3]; // [esp+14h] [ebp-F0h] BYREF
  float v15[3]; // [esp+20h] [ebp-E4h] BYREF
  float v16[3]; // [esp+2Ch] [ebp-D8h] BYREF
  float sum_result[3]; // [esp+38h] [ebp-CCh] BYREF
  float v18[3]; // [esp+44h] [ebp-C0h] BYREF
  char v19[12]; // [esp+50h] [ebp-B4h] BYREF
  float v20[3]; // [esp+5Ch] [ebp-A8h] BYREF
  float out_vector[3]; // [esp+68h] [ebp-9Ch] BYREF
  float v22[3]; // [esp+74h] [ebp-90h] BYREF
  float copy_result[3]; // [esp+80h] [ebp-84h] BYREF
  float *k; // [esp+8Ch] [ebp-78h]
  int v25; // [esp+90h] [ebp-74h]
  int j; // [esp+94h] [ebp-70h]
  _BYTE *v27; // [esp+98h] [ebp-6Ch]
  float v28[3]; // [esp+9Ch] [ebp-68h] BYREF
  float v29[3]; // [esp+A8h] [ebp-5Ch] BYREF
  float v30[3]; // [esp+B4h] [ebp-50h] BYREF
  int i; // [esp+C0h] [ebp-44h]
  char v32; // [esp+C7h] [ebp-3Dh]
  float *m; // [esp+C8h] [ebp-3Ch]
  float *jj; // [esp+CCh] [ebp-38h]
  int v35; // [esp+D0h] [ebp-34h]
  float v36[3]; // [esp+D4h] [ebp-30h] BYREF
  int ii; // [esp+E0h] [ebp-24h]
  int n; // [esp+E4h] [ebp-20h]
  float lhs[3]; // [esp+E8h] [ebp-1Ch] BYREF
  float v40; // [esp+F4h] [ebp-10h]
  float destination[3]; // [esp+F8h] [ebp-Ch] BYREF

  ++rf_collision_query_serial;
  *(_DWORD *)a3 = 0;
  *(_DWORD *)(a3 + 32) = 0;
  *(_DWORD *)(a3 + 36) = 0;
  if ( a4 )
    *(float *)(a3 + 4) = 1.0;
  unk_D5557C = 1.0;
  unk_D54558 = 0;
  rf_vector3_default_construct_noop(destination);
  v40 = rf_vector_length_squared((float *)(a2 + 64));
  if ( v40 != 0.0 )
  {
    if ( (*(_DWORD *)(a2 + 80) & 4) != 0 )
    {
      rf_vector_copy((float *)(a2 + 84), copy_result, (const float *)(a2 + 52));
      rf_vector_copy((float *)(a2 + 96), v22, (const float *)(a2 + 64));
    }
    else
    {
      v4 = rf_vector_subtract((const float *)(a2 + 52), out_vector, (const float *)(a2 + 4));
      rf_vector_copy(destination, v20, v4);
      v5 = rf_vector3_transform_by_matrix_rows(destination, (float *)v19, (float *)(a2 + 16));
      rf_vector_copy((float *)(a2 + 84), v18, v5);
      v6 = rf_vector_add((const float *)(a2 + 52), sum_result, (const float *)(a2 + 64));
      v7 = rf_vector_subtract(v6, v16, (const float *)(a2 + 4));
      rf_vector_copy(destination, v15, v7);
      rf_vector3_transform_by_matrix_rows(destination, lhs, (float *)(a2 + 16));
      v8 = rf_vector_subtract(lhs, v14, (const float *)(a2 + 84));
      rf_vector_copy((float *)(a2 + 96), v13, v8);
    }
    if ( !*(_DWORD *)a2 || (*(_DWORD *)(a2 + 80) & 1) == 0 || !rf_collision_sweep_face_test(*(float **)a2, a2, a3) )
    {
      if ( rf_collision_cached_face_count <= 0 || rf_collision_cache_bypass )
      {
        if ( rf_receiver_get_first_dword(this + 144) >= 1 )
        {
          v32 = 0;
          rf_vector3_default_construct_noop(v30);
          rf_vector3_default_construct_noop(v28);
          rf_vector_add((const float *)(a2 + 84), v29, (const float *)(a2 + 96));
          rf_segment_bounds_build(v30, v28, (float *)(a2 + 84), v29);
          rf_vector3_subtract_scalar_in_place(v30, *(float *)(a2 + 76));
          rf_vector3_add_scalar_in_place(v28, *(float *)(a2 + 76));
          for ( i = 0; ; ++i )
          {
            first_dword = rf_receiver_get_first_dword(this + 156);
            if ( i >= first_dword )
              break;
            v27 = *(_BYTE **)sub_552200((_DWORD *)this + 39, i);
            if ( v32 )
              break;
            if ( ((*(_DWORD *)(a2 + 80) & 8) != 0 || !rf_room_is_authored_sky(v27))
              && rf_aabb_overlap_inclusive(v30, v28, (float *)v27 + 2, (float *)v27 + 5) )
            {
              rf_collision_spatial_tree_sweep_faces(*((void **)v27 + 15), a2, a3);
              if ( *(int *)a3 > 0 && (*(_DWORD *)(a2 + 80) & 1) != 0 )
              {
                v32 = 1;
                return;
              }
              if ( !v32 )
              {
                for ( j = 0; ; ++j )
                {
                  v11 = rf_receiver_get_first_dword(v27 + 108);
                  if ( j >= v11 )
                    break;
                  v25 = *(_DWORD *)sub_552200((_DWORD *)v27 + 27, j);
                  if ( rf_aabb_overlap_inclusive(v30, v28, (float *)(v25 + 8), (float *)(v25 + 20)) )
                  {
                    rf_collision_spatial_tree_sweep_faces(*(void **)(v25 + 60), a2, a3);
                    if ( *(int *)a3 > 0 && (*(_DWORD *)(a2 + 80) & 1) != 0 )
                    {
                      v32 = 1;
                      break;
                    }
                  }
                }
              }
            }
            if ( !v32 )
            {
              if ( (*(_DWORD *)(a2 + 80) & 0x1000) != 0
                && v27[388]
                && rf_aabb_overlap_inclusive(v30, v28, (float *)v27 + 2, (float *)v27 + 5) )
              {
                for ( k = (float *)rf_receiver_get_first_dword(v27 + 40); k; k = (float *)rf_face_next_room_link((int)k) )
                {
                  if ( rf_face_is_liquid((_DWORD *)k + 10) )
                  {
                    rf_collision_sweep_face_test(k, a2, a3);
                    if ( *(int *)a3 > 0 && (*(_DWORD *)(a2 + 80) & 1) != 0 )
                    {
                      v32 = 1;
                      break;
                    }
                  }
                }
              }
              if ( !v32 )
                continue;
            }
            return;
          }
        }
        else
        {
          for ( m = (float *)rf_receiver_get_first_dword(this + 112); m; m = (float *)rf_solid_face_next_link((int)m) )
            rf_collision_sweep_face_test(m, a2, a3);
        }
      }
      else
      {
        for ( n = 0; n < rf_collision_cached_face_count; ++n )
        {
          if ( rf_collision_sweep_face_test((float *)rf_collision_cached_faces[n], a2, a3)
            && (*(_DWORD *)(a2 + 80) & 1) != 0 )
          {
            return;
          }
        }
        if ( (*(_DWORD *)(a2 + 80) & 0x1000) != 0 )
        {
          v35 = 0;
          rf_vector_add((const float *)(a2 + 84), v36, (const float *)(a2 + 96));
          for ( ii = 0; ; ++ii )
          {
            v9 = rf_receiver_get_first_dword(this + 156);
            if ( ii >= v9 )
              break;
            v35 = *(_DWORD *)sub_552200((_DWORD *)this + 39, ii);
            if ( *(_BYTE *)(v35 + 388)
              && rf_segment_intersects_aabb(
                   (float *)(v35 + 8),
                   (float *)(v35 + 20),
                   (float *)(a2 + 84),
                   v36,
                   destination) )
            {
              for ( jj = (float *)rf_receiver_get_first_dword((void *)(v35 + 40));
                    jj;
                    jj = (float *)rf_face_next_room_link((int)jj) )
              {
                if ( rf_face_is_liquid((_DWORD *)jj + 10) )
                  rf_collision_sweep_face_test(jj, a2, a3);
              }
            }
          }
        }
      }
    }
  }
}

