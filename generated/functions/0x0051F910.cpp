// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051F910 rf_world_draw_sorted_callbacks_around_liquid
// UNREALRED VERIFIED [room-render-20261028]: Nonnull room passing unknown_libname_11 skips pass. Copies current camera position/matrix through0x581FA0. For48-byte entries in0xA420C8: sortbyte+20 nonzero gets distance+40=Euclidean position-camera length if radius>=0,else-FLT_MAX, appended local-global pointerlist0xA5E4F8. Nonsorted entries immediately invoked. Builds plane groups via0x520450; Shell-sorts ungrouped pointers0x92EA38 by distance DESCENDING. If room has liquid byte+388, partitions each group root and ungrouped entry by camera liquid containment and test position: camera inside uses optional point+36 else center.y+radius; outside uses optional point+32 else center.y-radius. One partition rendered before liquid,other after; without liquid room all go first partition. For each plane group invokes each member only if drawnbyte+21 clear,sets drawnbyte,then invokes group root; direct
// ungrouped entries invoked afterward. With room and supplied liquid-face count>0,flushes pending see-through faces then renders liquid faces using0x580090/color(8,32,8,255) when globalbit2,else0x580040,trailing flags1,1. Then draws second partition in same member/root order. Optional debug0xA420A4 draws spheres/plane-normal arrows green for first partition,blue for second. Fixed global scratch capacities not checked here; no general alpha sort across opposite liquid partitions and no return status.
void __cdecl rf_world_draw_sorted_callbacks_around_liquid(_BYTE *a1, int a2, int a3, int a4)
{
  double v4; // st7
  float *v5; // ecx
  float *v6; // eax
  float v7; // [esp+24h] [ebp-11Ch]
  float v8; // [esp+28h] [ebp-118h]
  float v9; // [esp+2Ch] [ebp-114h]
  float v10; // [esp+30h] [ebp-110h]
  float v11; // [esp+34h] [ebp-10Ch]
  float v12; // [esp+38h] [ebp-108h]
  float v13[3]; // [esp+3Ch] [ebp-104h] BYREF
  float v14[3]; // [esp+48h] [ebp-F8h] BYREF
  float v15[3]; // [esp+54h] [ebp-ECh] BYREF
  float v16[3]; // [esp+60h] [ebp-E0h] BYREF
  float v17[3]; // [esp+6Ch] [ebp-D4h] BYREF
  float v18[3]; // [esp+78h] [ebp-C8h] BYREF
  float v19[3]; // [esp+84h] [ebp-BCh] BYREF
  float copy_result[3]; // [esp+90h] [ebp-B0h] BYREF
  int jj; // [esp+9Ch] [ebp-A4h]
  float *v22; // [esp+A0h] [ebp-A0h]
  float *v23; // [esp+A4h] [ebp-9Ch]
  int ii; // [esp+A8h] [ebp-98h]
  float *v25; // [esp+ACh] [ebp-94h]
  float *v26; // [esp+B0h] [ebp-90h]
  int v27; // [esp+B4h] [ebp-8Ch]
  int n; // [esp+B8h] [ebp-88h]
  int v29; // [esp+BCh] [ebp-84h]
  int m; // [esp+C0h] [ebp-80h]
  int v31; // [esp+C4h] [ebp-7Ch]
  int v32; // [esp+C8h] [ebp-78h]
  bool v33; // [esp+CFh] [ebp-71h]
  float destination; // [esp+D0h] [ebp-70h] BYREF
  float v35; // [esp+D4h] [ebp-6Ch]
  int v36; // [esp+DCh] [ebp-64h]
  int k; // [esp+E0h] [ebp-60h]
  int j; // [esp+E4h] [ebp-5Ch]
  float out_vector[3]; // [esp+E8h] [ebp-58h] BYREF
  int v40; // [esp+F4h] [ebp-4Ch]
  int v41; // [esp+F8h] [ebp-48h]
  int v42; // [esp+FCh] [ebp-44h]
  int v43; // [esp+100h] [ebp-40h]
  float rhs[3]; // [esp+104h] [ebp-3Ch] BYREF
  int v45; // [esp+110h] [ebp-30h]
  float v46[9]; // [esp+114h] [ebp-2Ch] BYREF
  int i; // [esp+138h] [ebp-8h]
  int v48; // [esp+13Ch] [ebp-4h]

  v42 = 0;
  v48 = 0;
  v43 = 0;
  v41 = 0;
  if ( !a1 || !unknown_libname_11(a1) )
  {
    rf_vector3_default_construct_noop(rhs);
    rf_matrix3_construct((char *)v46);
    rf_renderer_copy_current_view_transform(rhs, v46);
    v45 = 0;
    for ( i = 0; i < *(int *)&byte_98967F[756169]; ++i )
    {
      v40 = (int)&unk_A420C8 + 48 * i;
      if ( *(_BYTE *)(v40 + 20) )
      {
        if ( *(float *)(v40 + 16) >= 0.0 )
        {
          rf_vector_subtract((const float *)(v40 + 4), out_vector, rhs);
          v4 = rf_vector3_length(out_vector);
          *(float *)(v40 + 40) = v4;
        }
        else
        {
          *(float *)(v40 + 40) = -3.4028235e38;
        }
        unk_A5E4F8[v45++] = v40;
      }
      else
      {
        rf_world_invoke_render_callback_entry(v40, *(_DWORD *)v40, a2);
      }
    }
    rf_world_group_render_entries_by_plane((int)rhs, (int)v46, (int)unk_A5E4F8, v45);
    for ( j = dword_940A40 / 2; j > 0; j /= 2 )
    {
      for ( i = j; i < dword_940A40; ++i )
      {
        for ( k = i - j; k >= 0 && *(float *)(unk_92EA38[j + k] + 40) > (double)*(float *)(unk_92EA38[k] + 40); k -= j )
        {
          v36 = unk_92EA38[k];
          unk_92EA38[k] = unk_92EA38[j + k];
          unk_92EA38[j + k] = v36;
        }
      }
    }
    if ( a1 && a1[388] )
    {
      v33 = rf_liquid_room_contains_point((int)a1, (int)rhs);
      rf_vector3_default_construct_noop(&destination);
      for ( i = 0; i < unk_940A44[0]; ++i )
      {
        v32 = **(_DWORD **)&byte_98967F[4 * i + 755657];
        if ( v33 )
        {
          if ( *(_DWORD *)(v32 + 36) )
          {
            rf_vector_copy(&destination, copy_result, *(const float **)(v32 + 36));
          }
          else
          {
            rf_vector_copy(&destination, v19, (const float *)(v32 + 4));
            v35 = v35 + *(float *)(v32 + 16);
          }
          if ( rf_liquid_room_contains_point((int)a1, (int)&destination) )
            unk_A5E2F8[v48++] = *(_DWORD *)&byte_98967F[4 * i + 755657];
          else
            unk_A5E0F8[v42++] = *(_DWORD *)&byte_98967F[4 * i + 755657];
        }
        else
        {
          if ( *(_DWORD *)(v32 + 32) )
          {
            rf_vector_copy(&destination, v18, *(const float **)(v32 + 32));
          }
          else
          {
            rf_vector_copy(&destination, v17, (const float *)(v32 + 4));
            v35 = v35 - *(float *)(v32 + 16);
          }
          if ( rf_liquid_room_contains_point((int)a1, (int)&destination) )
            unk_A5E0F8[v42++] = *(_DWORD *)&byte_98967F[4 * i + 755657];
          else
            unk_A5E2F8[v48++] = *(_DWORD *)&byte_98967F[4 * i + 755657];
        }
      }
      for ( i = 0; i < dword_940A40; ++i )
      {
        v31 = unk_92EA38[i];
        if ( v33 )
        {
          if ( *(_DWORD *)(v31 + 36) )
          {
            rf_vector_copy(&destination, v16, *(const float **)(v31 + 36));
          }
          else
          {
            rf_vector_copy(&destination, v15, (const float *)(v31 + 4));
            v35 = v35 + *(float *)(v31 + 16);
          }
          if ( rf_liquid_room_contains_point((int)a1, (int)&destination) )
            unk_A5C0F8[v41++] = v31;
          else
            unk_A5A0F8[v43++] = v31;
        }
        else
        {
          if ( *(_DWORD *)(v31 + 32) )
          {
            rf_vector_copy(&destination, v14, *(const float **)(v31 + 32));
          }
          else
          {
            rf_vector_copy(&destination, v13, (const float *)(v31 + 4));
            v35 = v35 - *(float *)(v31 + 16);
          }
          if ( rf_liquid_room_contains_point((int)a1, (int)&destination) )
            unk_A5A0F8[v43++] = v31;
          else
            unk_A5C0F8[v41++] = v31;
        }
      }
    }
    else
    {
      for ( i = 0; i < unk_940A44[0]; ++i )
        unk_A5E0F8[v42++] = *(_DWORD *)&byte_98967F[4 * i + 755657];
      for ( i = 0; i < dword_940A40; ++i )
        unk_A5A0F8[v43++] = unk_92EA38[i];
    }
    for ( i = 0; i < v42; ++i )
    {
      for ( m = 0; m < *(_DWORD *)(unk_A5E0F8[i] + 8196); ++m )
      {
        v29 = *(_DWORD *)(unk_A5E0F8[i] + 4 * m + 4);
        if ( !*(_BYTE *)(v29 + 21) )
        {
          rf_world_invoke_render_callback_entry(v29, *(_DWORD *)v29, a2);
          *(_BYTE *)(v29 + 21) = 1;
        }
      }
      rf_world_invoke_render_callback_entry(*(_DWORD *)unk_A5E0F8[i], **(_DWORD **)unk_A5E0F8[i], a2);
    }
    for ( i = 0; i < v43; ++i )
      rf_world_invoke_render_callback_entry(unk_A5A0F8[i], *(_DWORD *)unk_A5A0F8[i], a2);
    if ( a1 && a3 > 0 )
    {
      rf_world_flush_see_through_face_batch();
      if ( (unk_A42088 & 2) != 0 )
      {
        rf_render_color_set_rgba8(8, 32, 8, 255);
        rf_renderer_draw_face_batch_alternate_dispatch(a2, (int)a1, a3, a4, 1, 1);
      }
      else
      {
        rf_renderer_draw_face_batch_backend_dispatch(a2, (int)a1, a3, a4, 1, 1);
      }
    }
    for ( i = 0; i < v48; ++i )
    {
      for ( n = 0; n < *(_DWORD *)(unk_A5E2F8[i] + 8196); ++n )
      {
        v27 = *(_DWORD *)(unk_A5E2F8[i] + 4 * n + 4);
        if ( !*(_BYTE *)(v27 + 21) )
        {
          rf_world_invoke_render_callback_entry(v27, *(_DWORD *)v27, a2);
          *(_BYTE *)(v27 + 21) = 1;
        }
      }
      rf_world_invoke_render_callback_entry(*(_DWORD *)unk_A5E2F8[i], **(_DWORD **)unk_A5E2F8[i], a2);
    }
    for ( i = 0; i < v41; ++i )
      rf_world_invoke_render_callback_entry(unk_A5C0F8[i], *(_DWORD *)unk_A5C0F8[i], a2);
    if ( unk_A420A4 )
    {
      rf_render_color_set_rgba8(0, 255, 0, 255);
      for ( i = 0; i < v42; ++i )
      {
        for ( ii = 0; ii < *(_DWORD *)(unk_A5E0F8[i] + 8196); ++ii )
          rf_debug_draw_wire_sphere_backend_dispatch(
            *(_DWORD *)(unk_A5E0F8[i] + 4 * ii + 4) + 4,
            *(float *)(*(_DWORD *)(unk_A5E0F8[i] + 4 * ii + 4) + 16),
            dword_187CC5C);
        v5 = *(float **)unk_A5E0F8[i];
        v25 = v5 + 1;
        v26 = *(float **)(*(_DWORD *)unk_A5E0F8[i] + 28);
        v12 = v5[3] + v26[2];
        v11 = v5[2] + v26[1];
        v10 = v5[1] + *v26;
        rf_renderer_debug_endpoint_arrow_backend_wrapper(v5[1], v5[2], v5[3], v10, v11, v12, 0, 255, 0);
      }
      for ( i = 0; i < v43; ++i )
        rf_debug_draw_wire_sphere_backend_dispatch(unk_A5A0F8[i] + 4, *(float *)(unk_A5A0F8[i] + 16), dword_187CC5C);
      rf_render_color_set_rgba8(0, 0, 255, 255);
      for ( i = 0; i < v48; ++i )
      {
        for ( jj = 0; jj < *(_DWORD *)(unk_A5E2F8[i] + 8196); ++jj )
          rf_debug_draw_wire_sphere_backend_dispatch(
            *(_DWORD *)(unk_A5E2F8[i] + 4 * jj + 4) + 4,
            *(float *)(*(_DWORD *)(unk_A5E2F8[i] + 4 * jj + 4) + 16),
            dword_187CC5C);
        v6 = *(float **)unk_A5E2F8[i];
        v22 = v6 + 1;
        v23 = *(float **)(*(_DWORD *)unk_A5E2F8[i] + 28);
        v9 = v6[3] + v23[2];
        v8 = v6[2] + v23[1];
        v7 = v6[1] + *v23;
        rf_renderer_debug_endpoint_arrow_backend_wrapper(v6[1], v6[2], v6[3], v7, v8, v9, 0, 0, 255);
      }
      for ( i = 0; i < v41; ++i )
        rf_debug_draw_wire_sphere_backend_dispatch(unk_A5C0F8[i] + 4, *(float *)(unk_A5C0F8[i] + 16), dword_187CC5C);
    }
  }
}

