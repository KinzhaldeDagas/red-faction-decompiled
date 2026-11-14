// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D6C00 rf_renderer_draw_context_faces_sorted_translucent
// UNREALRED VERIFIED [renderer-overlays-20261028]: Builds contextlist containing input plus up to255 entries from input+108 collection; includes entry when rawbytequery0x5211F0 returns0 OR global0xA420A8 set. Lazily initializes opaque/translucent packedstates(1,1,2,3,4,3)/(1,1,2,3,1,3). Walks each context face list+40; skips invisible unless0xA420A8. Computes plane point=-D*normal via0x556E10 plus globaloffset0xA5A0EC and tests camera-facing. Non-see-through faces drawn immediately; see-through faces queued with keymean Euclidean vertex distance from0x18CD4A8,then Shellsorted descending and drawn farthestfirst. Both paths construct25 local48-byte clipvertices,transform each corner worldpoint plusglobaloffset; if matrix0xA42064 active,instead subtract0xA420BC,inverserotate,and add0x18CD4A8. Rejects only sharedoutcodeANDnonzero; sets pendingfacebitmap+48 and baseUV fromcorner+4/+8,submits
// attributemask1 with appropriate state. Translucentqueue nominal256slots but append has no capacityguard; facevertexcount<=25 and nonemptydistance denominator unguarded. Does not infer semantic role of rawbyte+2 filter. Returns translucentcount after drawloop,not totaldrawcount; leaves pendingtexture/state changed.
int __cdecl rf_renderer_draw_context_faces_sorted_translucent(int a1)
{
  int first_dword; // eax
  float *v2; // eax
  float *v3; // eax
  double v4; // st7
  float *v5; // eax
  float *v6; // eax
  char v7; // al
  int result; // eax
  float *v9; // eax
  float *v10; // eax
  char v11; // al
  int v12; // [esp+8h] [ebp-1748h]
  int v13; // [esp+Ch] [ebp-1744h]
  int v14; // [esp+10h] [ebp-1740h]
  int v15; // [esp+14h] [ebp-173Ch]
  int v16; // [esp+18h] [ebp-1738h]
  float v17[3]; // [esp+1Ch] [ebp-1734h] BYREF
  float v18[3]; // [esp+28h] [ebp-1728h] BYREF
  float v19[3]; // [esp+34h] [ebp-171Ch] BYREF
  float v20[3]; // [esp+40h] [ebp-1710h] BYREF
  float v21[3]; // [esp+4Ch] [ebp-1704h] BYREF
  float v22[3]; // [esp+58h] [ebp-16F8h] BYREF
  float copy_result[3]; // [esp+64h] [ebp-16ECh] BYREF
  float v24[3]; // [esp+70h] [ebp-16E0h] BYREF
  float sum_result[3]; // [esp+7Ch] [ebp-16D4h] BYREF
  float v26[3]; // [esp+88h] [ebp-16C8h] BYREF
  float v27[3]; // [esp+94h] [ebp-16BCh] BYREF
  int v28; // [esp+A0h] [ebp-16B0h]
  int v29[27]; // [esp+A4h] [ebp-16ACh] BYREF
  int v30; // [esp+110h] [ebp-1640h]
  char v31[1205]; // [esp+114h] [ebp-163Ch] BYREF
  char v32; // [esp+5C9h] [ebp-1187h]
  int v33; // [esp+5CCh] [ebp-1184h]
  float v34; // [esp+5D0h] [ebp-1180h]
  int n; // [esp+5D4h] [ebp-117Ch]
  int m; // [esp+5D8h] [ebp-1178h]
  float destination[3]; // [esp+5DCh] [ebp-1174h] BYREF
  int v38; // [esp+5E8h] [ebp-1168h]
  int v39[27]; // [esp+5ECh] [ebp-1164h] BYREF
  int v40; // [esp+658h] [ebp-10F8h]
  char v41[1205]; // [esp+65Ch] [ebp-10F4h] BYREF
  char v42; // [esp+B11h] [ebp-C3Fh]
  float out_vector[3]; // [esp+B14h] [ebp-C3Ch] BYREF
  int v44; // [esp+B20h] [ebp-C30h]
  int k; // [esp+B24h] [ebp-C2Ch]
  _BYTE *v46; // [esp+B28h] [ebp-C28h]
  _DWORD v47[257]; // [esp+B2Ch] [ebp-C24h]
  int v48; // [esp+F30h] [ebp-820h]
  _DWORD v49[256]; // [esp+F34h] [ebp-81Ch]
  int v50; // [esp+1334h] [ebp-41Ch]
  const float *j; // [esp+1338h] [ebp-418h]
  float v52[257]; // [esp+133Ch] [ebp-414h]
  int i; // [esp+1740h] [ebp-10h]
  int v54; // [esp+174Ch] [ebp-4h]

  v50 = 0;
  v47[0] = a1;
  v48 = 1;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a1 + 108));
    if ( i >= first_dword || i >= 255 )
      break;
    v46 = *(_BYTE **)sub_552200((_DWORD *)(a1 + 108), i);
    if ( !sub_5211F0(v46) || unk_A420A8 )
      v47[v48++] = v46;
  }
  if ( (dword_1E01520 & 1) == 0 )
  {
    dword_1E01520 |= 1u;
    v54 = 0;
    rf_render_state_pack(&unk_1E0151C, 1, 1, 2, 3, 4, 3);
    v54 = -1;
  }
  if ( (dword_1E01520 & 2) == 0 )
  {
    dword_1E01520 |= 2u;
    v54 = 1;
    rf_render_state_pack(&unk_1E01518, 1, 1, 2, 3, 1, 3);
    v54 = -1;
  }
  for ( i = 0; i < v48; ++i )
  {
    for ( j = (const float *)rf_receiver_get_first_dword((void *)(v47[i] + 40));
          j;
          j = (const float *)rf_face_next_room_link((int)j) )
    {
      if ( unk_A420A8 || !rf_face_is_invisible((_DWORD *)j + 10) )
      {
        v2 = rf_plane_point_from_negative_offset_normal(j, v26);
        v3 = rf_vector_add(v2, sum_result, &flt_A5A0EC);
        if ( rf_renderer_plane_faces_camera_backend_wrapper((int)j, v3) )
        {
          if ( rf_face_is_see_through((_DWORD *)j + 10) )
          {
            v49[v50] = j;
            v52[v50] = 0.0;
            v44 = 0;
            for ( k = *((_DWORD *)j + 16); k; k = v16 )
            {
              rf_vector_subtract(*(const float **)k, out_vector, unk_18CD4A8);
              v4 = rf_vector3_length(out_vector);
              v52[v50] = v4 + v52[v50];
              ++v44;
              if ( *(_DWORD *)(k + 20) == *((_DWORD *)j + 16) )
                v16 = 0;
              else
                v16 = *(_DWORD *)(k + 20);
            }
            v52[v50] = v52[v50] / (double)v44;
            ++v50;
          }
          else
          {
            rf_vector_construct_no_unwind(v41, 0x30u, 25, rf_vector_prefix_construct_noop);
            v40 = 0;
            v42 = -1;
            v38 = *((_DWORD *)j + 16);
            while ( v38 )
            {
              v39[v40] = (int)&v41[48 * v40];
              rf_vector3_default_construct_noop(destination);
              if ( *(_DWORD *)&byte_98967F[756197] )
              {
                v5 = rf_vector_subtract(*(const float **)v38, v24, &flt_A420BC);
                rf_vector_copy(destination, copy_result, v5);
                rf_matrix3_inverse_rotate_vector(destination, *(float **)&byte_98967F[756197]);
                rf_vector_accumulate(destination, unk_18CD4A8);
              }
              else
              {
                v6 = rf_vector_add(*(const float **)v38, v22, &flt_A5A0EC);
                rf_vector_copy(destination, v21, v6);
              }
              v7 = rf_renderer_transform_world_point_backend_wrapper((int)&v41[48 * v40], destination);
              v42 &= v7;
              if ( *(_DWORD *)(v38 + 20) == *((_DWORD *)j + 16) )
                v15 = 0;
              else
                v15 = *(_DWORD *)(v38 + 20);
              v38 = v15;
              ++v40;
            }
            if ( !v42 )
            {
              rf_renderer_set_pending_texture_handles(*((_DWORD *)j + 12), -1);
              v40 = 0;
              v38 = *((_DWORD *)j + 16);
              while ( v38 )
              {
                *(float *)&v41[48 * v40 + 28] = *(float *)(v38 + 4);
                *(float *)&v41[48 * v40 + 32] = *(float *)(v38 + 8);
                if ( *(_DWORD *)(v38 + 20) == *((_DWORD *)j + 16) )
                  v14 = 0;
                else
                  v14 = *(_DWORD *)(v38 + 20);
                v38 = v14;
                ++v40;
              }
              rf_renderer_submit_immediate_polygon(v40, (int)v39, 1, unk_1E0151C, 0, 0.0);
            }
          }
        }
      }
    }
  }
  for ( m = v50 / 2; m > 0; m /= 2 )
  {
    for ( i = m; i < v50; ++i )
    {
      for ( n = i - m; n >= 0 && v52[m + n] > (double)v52[n]; n -= m )
      {
        v33 = v49[n];
        v34 = v52[n];
        v52[n] = v52[m + n];
        v49[n] = v49[m + n];
        v52[m + n] = v34;
        v49[m + n] = v33;
      }
    }
  }
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= v50 )
      break;
    rf_vector_construct_no_unwind(v31, 0x30u, 25, rf_vector_prefix_construct_noop);
    v30 = 0;
    v32 = -1;
    j = (const float *)v49[i];
    v28 = *((_DWORD *)j + 16);
    while ( v28 )
    {
      v29[v30] = (int)&v31[48 * v30];
      rf_vector3_default_construct_noop(v27);
      if ( *(_DWORD *)&byte_98967F[756197] )
      {
        v9 = rf_vector_subtract(*(const float **)v28, v20, &flt_A420BC);
        rf_vector_copy(v27, v19, v9);
        rf_matrix3_inverse_rotate_vector(v27, *(float **)&byte_98967F[756197]);
        rf_vector_accumulate(v27, unk_18CD4A8);
      }
      else
      {
        v10 = rf_vector_add(*(const float **)v28, v18, &flt_A5A0EC);
        rf_vector_copy(v27, v17, v10);
      }
      v11 = rf_renderer_transform_world_point_backend_wrapper((int)&v31[48 * v30], v27);
      v32 &= v11;
      if ( *(_DWORD *)(v28 + 20) == *((_DWORD *)j + 16) )
        v13 = 0;
      else
        v13 = *(_DWORD *)(v28 + 20);
      v28 = v13;
      ++v30;
    }
    if ( !v32 )
    {
      rf_renderer_set_pending_texture_handles(*((_DWORD *)j + 12), -1);
      v30 = 0;
      v28 = *((_DWORD *)j + 16);
      while ( v28 )
      {
        *(float *)&v31[48 * v30 + 28] = *(float *)(v28 + 4);
        *(float *)&v31[48 * v30 + 32] = *(float *)(v28 + 8);
        if ( *(_DWORD *)(v28 + 20) == *((_DWORD *)j + 16) )
          v12 = 0;
        else
          v12 = *(_DWORD *)(v28 + 20);
        v28 = v12;
        ++v30;
      }
      rf_renderer_submit_immediate_polygon(v30, (int)v29, 1, unk_1E01518, 0, 0.0);
    }
  }
  return result;
}

