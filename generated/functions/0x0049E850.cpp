// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049E850 rf_multiplayer_compact_scoreboard_render
// UNREALRED VERIFIED [multiplayer-hud] Draws the game-rule-gated compact Name/Team/Score table for 1-32 sorted players and a separate Red Team/Blue Team totals panel in team modes.
void __cdecl rf_multiplayer_compact_scoreboard_render(char a1)
{
  unsigned __int8 *v1; // eax
  unsigned __int8 *v2; // eax
  unsigned __int8 *v3; // eax
  unsigned __int8 *v4; // eax
  unsigned __int8 *v5; // eax
  unsigned __int8 *v6; // eax
  int v7; // [esp-4h] [ebp-124h]
  int v8; // [esp-4h] [ebp-124h]
  int v9; // [esp-4h] [ebp-124h]
  int v10; // [esp-4h] [ebp-124h]
  int v11; // [esp-4h] [ebp-124h]
  int v12; // [esp-4h] [ebp-124h]
  std::exception *v13; // [esp+4h] [ebp-11Ch]
  const void **v14; // [esp+Ch] [ebp-114h]
  std::exception *v15; // [esp+14h] [ebp-10Ch]
  const void **v16; // [esp+1Ch] [ebp-104h]
  std::exception *v17; // [esp+24h] [ebp-FCh]
  std::exception *v18; // [esp+2Ch] [ebp-F4h]
  int v19; // [esp+34h] [ebp-ECh]
  _BYTE v20[8]; // [esp+38h] [ebp-E8h] BYREF
  _DWORD v21[2]; // [esp+40h] [ebp-E0h] BYREF
  _BYTE v22[8]; // [esp+48h] [ebp-D8h] BYREF
  _DWORD v23[2]; // [esp+50h] [ebp-D0h] BYREF
  _DWORD v24[2]; // [esp+58h] [ebp-C8h] BYREF
  _DWORD v25[2]; // [esp+60h] [ebp-C0h] BYREF
  unsigned __int8 team0_score_byte; // [esp+6Ah] [ebp-B6h]
  unsigned __int8 team1_score_byte; // [esp+6Bh] [ebp-B5h]
  int v28; // [esp+6Ch] [ebp-B4h]
  int v29; // [esp+70h] [ebp-B0h]
  _DWORD v30[2]; // [esp+74h] [ebp-ACh] BYREF
  int Base; // [esp+7Ch] [ebp-A4h] BYREF
  int v32; // [esp+80h] [ebp-A0h]
  int i; // [esp+100h] [ebp-20h]
  signed int j; // [esp+104h] [ebp-1Ch]
  int v35; // [esp+108h] [ebp-18h]
  size_t NumOfElements; // [esp+10Ch] [ebp-14h]
  int v37; // [esp+110h] [ebp-10h]
  int v38; // [esp+11Ch] [ebp-4h]

  if ( a1 || (rf_multiplayer_game_flags & 1) != 0 )
  {
    NumOfElements = rf_player_runtime_list_count();
    if ( (int)NumOfElements > 0 && (int)NumOfElements <= 32 )
    {
      v35 = 200;
      rf_render_color_set_rgba8(0, 0, 0, 128);
      rf_renderer_fill_rectangle_clipped(185, 35, 305, 15 * (NumOfElements + 1) + 30, dword_182ABB8);
      rf_render_color_set_rgba8(0, 128, 0, 255);
      rf_font_draw_text_screen(200, 50, "Name", -1, dword_182ABBC);
      rf_font_draw_text_screen(300, 50, "Team", -1, dword_182ABBC);
      rf_font_draw_text_screen(400, 50, "Score", -1, dword_182ABBC);
      v37 = 70;
      j = 0;
      for ( i = dword_87C324; i; i = v19 )
      {
        *(&Base + j++) = i;
        if ( *(_DWORD *)i == dword_87C324 )
          v19 = 0;
        else
          v19 = *(_DWORD *)i;
      }
      if ( NumOfElements == 2 )
      {
        if ( *(__int16 *)(*(_DWORD *)(Base + 44) + 2) < *(__int16 *)(*(_DWORD *)(v32 + 44) + 2) )
        {
          v28 = Base;
          Base = v32;
          v32 = v28;
        }
      }
      else if ( (int)NumOfElements > 2 )
      {
        qsort(&Base, NumOfElements, 4u, rf_multiplayer_compare_player_scores_descending);
      }
      rf_string_construct_empty(v30);
      v38 = 0;
      for ( j = 0; j < (int)NumOfElements; ++j )
      {
        i = *(&Base + j);
        if ( *(_BYTE *)(i + 48) )
        {
          if ( *(_BYTE *)(i + 48) == 1 )
            rf_render_color_set_rgba8(0, 0, 255, 255);
        }
        else
        {
          rf_render_color_set_rgba8(192, 0, 0, 255);
        }
        v7 = dword_182ABBC;
        v1 = (unsigned __int8 *)rf_string_object_c_str_or_empty((const void *)(i + 8));
        rf_font_draw_text_screen(v35, v37, v1, -1, v7);
        if ( rf_multiplayer_copy_team_name_to_string((int)v30, *(unsigned __int8 *)(i + 48)) )
        {
          v8 = dword_182ABBC;
          v2 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v30);
          rf_font_draw_text_screen(v35 + 100, v37, v2, -1, v8);
        }
        else
        {
          v9 = dword_182ABBC;
          v18 = (std::exception *)rf_string_format_int32_decimal(v25, *(unsigned __int8 *)(i + 48));
          LOBYTE(v38) = 1;
          v3 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v18);
          rf_font_draw_text_screen(v35 + 100, v37, v3, -1, v9);
          LOBYTE(v38) = 0;
          rf_string_destroy_buffer(v25);
        }
        v10 = dword_182ABBC;
        v17 = (std::exception *)rf_string_format_int32_decimal(v24, *(__int16 *)(*(_DWORD *)(i + 44) + 2));
        LOBYTE(v38) = 2;
        v4 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v17);
        rf_font_draw_text_screen(v35 + 200, v37, v4, -1, v10);
        LOBYTE(v38) = 0;
        rf_string_destroy_buffer(v24);
        v37 += 15;
      }
      v29 = rf_multiplayer_game_mode_get();
      if ( v29 == 1 || v29 == 2 )
      {
        v35 = 300;
        v37 += 40;
        rf_render_color_set_rgba8(0, 0, 0, 128);
        rf_renderer_fill_rectangle_clipped(v35 - 15, v37 - 15, 115, 55, dword_182ABB8);
        if ( v29 == 1 )
        {
          team0_score_byte = rf_ctf_red_capture_byte_get();
          team1_score_byte = rf_ctf_blue_capture_byte_get();
        }
        else
        {
          team0_score_byte = rf_multiplayer_get_team0_score_byte();
          team1_score_byte = rf_multiplayer_get_team1_score_byte();
        }
        rf_render_color_set_rgba8(192, 0, 0, 255);
        v11 = dword_182ABBC;
        v16 = (const void **)rf_string_format_int32_decimal(v23, team0_score_byte);
        LOBYTE(v38) = 3;
        v15 = (std::exception *)rf_string_concat_cstr_object(v22, "Red Team: ", v16);
        LOBYTE(v38) = 4;
        v5 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v15);
        rf_font_draw_text_screen(v35, v37, v5, -1, v11);
        LOBYTE(v38) = 3;
        rf_string_destroy_buffer(v22);
        LOBYTE(v38) = 0;
        rf_string_destroy_buffer(v23);
        v37 += 15;
        rf_render_color_set_rgba8(0, 0, 255, 255);
        v12 = dword_182ABBC;
        v14 = (const void **)rf_string_format_int32_decimal(v21, team1_score_byte);
        LOBYTE(v38) = 5;
        v13 = (std::exception *)rf_string_concat_cstr_object(v20, "Blue Team: ", v14);
        LOBYTE(v38) = 6;
        v6 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v13);
        rf_font_draw_text_screen(v35, v37, v6, -1, v12);
        LOBYTE(v38) = 5;
        rf_string_destroy_buffer(v20);
        LOBYTE(v38) = 0;
        rf_string_destroy_buffer(v21);
      }
      v38 = -1;
      rf_string_destroy_buffer(v30);
    }
  }
}

