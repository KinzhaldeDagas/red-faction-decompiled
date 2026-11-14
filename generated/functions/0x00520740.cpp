// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00520740 rf_world_render_rooms_with_authored_sky
// UNREALRED VERIFIED [authored-sky-renderer] Builds visible-room state, draws the selected authored sky room first when a normal room is visible, then draws ordinary rooms so world geometry occludes the sky shell.
void __cdecl rf_world_render_rooms_with_authored_sky(_DWORD *a1, int a2, int a3, int a4)
{
  int v4; // eax
  int v5; // [esp+0h] [ebp-18h]
  int v6; // [esp+8h] [ebp-10h]
  int v7; // [esp+Ch] [ebp-Ch]
  int i; // [esp+10h] [ebp-8h]
  int k; // [esp+10h] [ebp-8h]
  int j; // [esp+14h] [ebp-4h]

  if ( a2 && !rf_pointer_array_count_matches(a1 + 36, a2) )
    a2 = 0;
  unk_A42080 = a2;
  rf_render_pass_reset_counter_and_flags();
  rf_render_color_set_rgba8(255, 255, 255, 255);
  unk_A42088 = a3;
  ++a1[215];
  rf_world_collect_visible_rooms_and_sky((int)a1, a2, a3);
  if ( dword_A42078 && unk_A4207C )
  {
    rf_renderer_select_room_clip_aperture(dword_A42078);
    rf_world_render_sky_room_camera_centered((int)a1, dword_A42078, a4);
    rf_renderer_select_room_clip_aperture(0);
  }
  *(_DWORD *)&byte_98967F[756177] += dword_A42074;
  for ( i = 0; i < dword_A42074; ++i )
  {
    v7 = unk_940A48[i];
    for ( j = 0; j < rf_receiver_get_first_dword((void *)(v7 + 108)); ++j )
    {
      v4 = sub_552200((_DWORD *)(v7 + 108), j);
      v6 = *(_DWORD *)v4;
      if ( *(_DWORD *)(*(_DWORD *)v4 + 144) < SLODWORD(flt_18092A0[16])
        || *(_DWORD *)(v6 + 140) < SLODWORD(flt_18092A0[16]) )
      {
        *(float *)(v6 + 140) = flt_18092A0[16];
        *(float *)(v6 + 144) = flt_18092A0[16];
        *(_DWORD *)(v6 + 120) = v7;
      }
    }
  }
  rf_world_room_packets_backend_wrapper(a1, (void *const *)unk_940A48, dword_A42074);
  for ( k = dword_A42074 - 1; k >= 0; --k )
  {
    v5 = unk_940A48[k];
    rf_renderer_select_room_clip_aperture(v5);
    rf_world_render_room_liquid_and_effect_pass((int)a1, v5, k == 0);
    rf_renderer_select_room_clip_aperture(0);
  }
}

