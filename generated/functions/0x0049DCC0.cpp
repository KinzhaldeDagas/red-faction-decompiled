// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049DCC0 rf_multiplayer_team_ctf_status_render
// UNREALRED VERIFIED [multiplayer-hud] Draws the 185x55 lower-left team status panel, CTF carrier/at-base/missing rows, team/flag art, local-carrier microflag, and right-aligned red/blue totals.
void rf_multiplayer_team_ctf_status_render()
{
  unsigned __int8 *v0; // eax
  unsigned __int8 *v1; // eax
  unsigned __int8 *v2; // eax
  unsigned __int8 *v3; // eax
  unsigned __int8 *v4; // eax
  unsigned __int8 *v5; // eax
  int v6; // [esp-8h] [ebp-7Ch]
  int v7; // [esp-8h] [ebp-7Ch]
  int v8; // [esp-8h] [ebp-7Ch]
  int v9; // [esp-8h] [ebp-7Ch]
  int v10; // [esp-4h] [ebp-78h]
  int v11; // [esp-4h] [ebp-78h]
  int v12; // [esp-4h] [ebp-78h]
  int v13; // [esp-4h] [ebp-78h]
  int v14; // [esp-4h] [ebp-78h]
  int v15; // [esp-4h] [ebp-78h]
  void *v16; // [esp+4h] [ebp-70h]
  void *v17; // [esp+Ch] [ebp-68h]
  _BYTE v18[8]; // [esp+14h] [ebp-60h] BYREF
  _BYTE v19[8]; // [esp+1Ch] [ebp-58h] BYREF
  char *v20[2]; // [esp+24h] [ebp-50h] BYREF
  char *v21[2]; // [esp+2Ch] [ebp-48h] BYREF
  int v22; // [esp+34h] [ebp-40h]
  int v23; // [esp+38h] [ebp-3Ch]
  int v24; // [esp+3Ch] [ebp-38h]
  _DWORD v25[3]; // [esp+40h] [ebp-34h] BYREF
  int viewport_height; // [esp+4Ch] [ebp-28h]
  int v27; // [esp+50h] [ebp-24h] BYREF
  int v28; // [esp+54h] [ebp-20h] BYREF
  int team0_score_byte; // [esp+58h] [ebp-1Ch]
  int team1_score_byte; // [esp+5Ch] [ebp-18h]
  _DWORD v31[2]; // [esp+60h] [ebp-14h] BYREF
  int v32; // [esp+70h] [ebp-4h]

  v25[2] = rf_renderer_get_viewport_width();
  viewport_height = rf_renderer_get_viewport_height();
  rf_render_color_set_rgba8(0, 0, 0, 150);
  rf_renderer_fill_rectangle_clipped(10, viewport_height - 65, 185, 55, dword_182ABB8);
  v24 = rf_multiplayer_game_mode_get();
  if ( v24 == 1 )
  {
    if ( byte_662919 )
    {
      flt_66291C = flt_66291C - rf_frame_delta_seconds * 500.0;
      if ( flt_66291C <= 50.0 )
      {
        flt_66291C = 50.0;
        byte_662919 = 0;
      }
    }
    else
    {
      flt_66291C = rf_frame_delta_seconds * 500.0 + flt_66291C;
      if ( flt_66291C >= 255.0 )
      {
        flt_66291C = 255.0;
        byte_662919 = 1;
      }
    }
    rf_render_color_set_rgba8(53, 207, 22, 255);
    v22 = rf_ctf_red_carrier_get();
    if ( v22 )
    {
      rf_string_copy_construct_from_object(v21, (char **)(v22 + 8));
      v32 = 0;
      if ( (int)rf_string_length_from_cstr((const char **)v21) > 15 )
      {
        v17 = rf_string_left_count(v21, v19, 7);
        LOBYTE(v32) = 1;
        rf_string_assign_from_object(v21, (int)v17);
        LOBYTE(v32) = 0;
        rf_string_destroy_buffer(v19);
        rf_string_append_cstr_in_place(v21, (int)&unk_63A424);
      }
      v10 = dword_182ABBC;
      v6 = dword_662934;
      v0 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v21);
      rf_font_draw_text_screen(43, viewport_height - 57, v0, v6, v10);
      if ( v22 == rf_local_fpgun_player )
      {
        rf_render_color_set_rgba8(255, 255, 255, (int)flt_66291C);
        rf_bitmap_draw_unscaled_clipped(
          rf_compact_score_red_microflag_bitmap,
          205,
          viewport_height - 65,
          rf_particle_glow_billboard_render_state);
      }
      v32 = -1;
      rf_string_destroy_buffer(v21);
    }
    else if ( rf_ctf_red_flag_home_or_uninitialized() )
    {
      rf_font_draw_text_screen(43, viewport_height - 57, "at base", dword_662934, dword_182ABBC);
    }
    else
    {
      rf_font_draw_text_screen(43, viewport_height - 57, "missing", dword_662934, dword_182ABBC);
    }
    rf_render_color_set_rgba8(53, 207, 22, 255);
    v23 = rf_ctf_blue_carrier_get();
    if ( v23 )
    {
      rf_string_copy_construct_from_object(v20, (char **)(v23 + 8));
      v32 = 2;
      if ( (int)rf_string_length_from_cstr((const char **)v20) > 15 )
      {
        v16 = rf_string_left_count(v20, v18, 7);
        LOBYTE(v32) = 3;
        rf_string_assign_from_object(v20, (int)v16);
        LOBYTE(v32) = 2;
        rf_string_destroy_buffer(v18);
        rf_string_append_cstr_in_place(v20, (int)"...");
      }
      v11 = dword_182ABBC;
      v7 = dword_662934;
      v1 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v20);
      rf_font_draw_text_screen(43, viewport_height - 31, v1, v7, v11);
      if ( v23 == rf_local_fpgun_player )
      {
        rf_render_color_set_rgba8(255, 255, 255, (int)flt_66291C);
        rf_bitmap_draw_unscaled_clipped(
          rf_compact_score_blue_microflag_bitmap,
          205,
          viewport_height - 65,
          rf_particle_glow_billboard_render_state);
      }
      v32 = -1;
      rf_string_destroy_buffer(v20);
    }
    else if ( rf_ctf_blue_flag_home_or_uninitialized() )
    {
      rf_font_draw_text_screen(43, viewport_height - 31, "at base", dword_662934, dword_182ABBC);
    }
    else
    {
      rf_font_draw_text_screen(43, viewport_height - 31, "missing", dword_662934, dword_182ABBC);
    }
  }
  if ( v24 )
  {
    if ( rf_local_fpgun_player )
    {
      if ( *(_BYTE *)(rf_local_fpgun_player + 48) )
      {
        if ( *(_BYTE *)(rf_local_fpgun_player + 48) == 1 )
        {
          rf_render_color_set_rgba8(255, 255, 255, 255);
          rf_bitmap_draw_unscaled_clipped(
            rf_compact_score_team_logo_bitmap,
            17,
            viewport_height - 35,
            rf_particle_glow_billboard_render_state);
        }
      }
      else
      {
        rf_render_color_set_rgba8(255, 255, 255, 255);
        rf_bitmap_draw_unscaled_clipped(
          rf_compact_score_team_logo_bitmap,
          17,
          viewport_height - 61,
          rf_particle_glow_billboard_render_state);
      }
    }
    rf_render_color_set_rgba8(255, 255, 255, 255);
    rf_bitmap_draw_unscaled_clipped(
      rf_compact_score_red_flag_bitmap,
      17,
      viewport_height - 61,
      rf_particle_glow_billboard_render_state);
    rf_bitmap_draw_unscaled_clipped(
      rf_compact_score_blue_flag_bitmap,
      17,
      viewport_height - 35,
      rf_particle_glow_billboard_render_state);
  }
  if ( v24 == 1 )
  {
    team0_score_byte = (unsigned __int8)rf_ctf_red_capture_byte_get();
    team1_score_byte = (unsigned __int8)rf_ctf_blue_capture_byte_get();
  }
  else if ( v24 == 2 )
  {
    rf_render_color_set_rgba8(53, 207, 22, 255);
    team0_score_byte = (unsigned __int8)rf_multiplayer_get_team0_score_byte();
    team1_score_byte = (unsigned __int8)rf_multiplayer_get_team1_score_byte();
  }
  rf_string_format_int32_decimal(v31, team0_score_byte);
  v32 = 4;
  rf_string_format_int32_decimal(v25, team1_score_byte);
  LOBYTE(v32) = 5;
  v12 = dword_662934;
  v2 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v31);
  rf_font_measure_text_extent(&v28, &v27, v2, -1, v12);
  v13 = dword_182ABBC;
  v8 = dword_662934;
  v3 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v31);
  rf_font_draw_text_screen(190 - v28, viewport_height - 57, v3, v8, v13);
  v14 = dword_662934;
  v4 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v25);
  rf_font_measure_text_extent(&v28, &v27, v4, -1, v14);
  v15 = dword_182ABBC;
  v9 = dword_662934;
  v5 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v25);
  rf_font_draw_text_screen(190 - v28, viewport_height - 31, v5, v9, v15);
  LOBYTE(v32) = 4;
  rf_string_destroy_buffer(v25);
  v32 = -1;
  rf_string_destroy_buffer(v31);
}

