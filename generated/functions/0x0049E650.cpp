// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049E650 rf_multiplayer_hud_render_target_notice
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): No arguments; requires showBYTE77FE4D!=0 and stored RFString77FE58 nonempty. When transitionBYTE77FE4E!=0: direction66291B!=0 adds
// frameDelta*500 to float alpha77FE50 with binary32 store, ordered STRICTLY>128 snaps to192, clears direction/transition and resets loss timer77FE6C. Direction0 subtracts same,
// ordered STRICTLY<0 clamps0, sets direction1, clears transition and resets loss timer. Equality128/0 does not finish transition; unordered comparisons do not finish it. In game
// modes1/2 teamDWORD77FE54==0 ->red,==1 ->blue,other ->green; all other modes green. Truncates alpha, measures medium font757BB0, draws centered x=viewportWidth/2-textWidth/2 with
// separate signed truncations, y=viewportHeight/2-3*textHeight. No active/health/range test, show clear after fade, font/bitmap ownership or color restoration. Return register
// incidental.
char rf_multiplayer_hud_render_target_notice()
{
  char result; // al
  unsigned __int8 *v1; // eax
  int viewport_width; // eax
  int v3; // [esp-10h] [ebp-1Ch]
  unsigned __int8 *v4; // [esp-Ch] [ebp-18h]
  int v5; // [esp-8h] [ebp-14h]
  int v6; // [esp-4h] [ebp-10h]
  int v7; // [esp-4h] [ebp-10h]
  int v8; // [esp+0h] [ebp-Ch]
  int v9; // [esp+4h] [ebp-8h] BYREF
  int v10; // [esp+8h] [ebp-4h] BYREF

  result = unk_77FE4D;
  if ( unk_77FE4D )
  {
    result = rf_string_equals_case_insensitive((int)dword_77FE58, (char *)&byte_63A407);
    if ( !result )
    {
      if ( byte_77FE4E[0] )
      {
        if ( byte_66291B )
        {
          unk_77FE50 = rf_frame_delta_seconds * 500.0 + unk_77FE50;
          if ( unk_77FE50 > 128.0 )
          {
            unk_77FE50 = 192.0;
            byte_66291B = 0;
            byte_77FE4E[0] = 0;
            rf_replicator_reset(&unk_77FE6C);
          }
        }
        else
        {
          unk_77FE50 = unk_77FE50 - rf_frame_delta_seconds * 500.0;
          if ( unk_77FE50 < 0.0 )
          {
            unk_77FE50 = 0.0;
            byte_66291B = 1;
            byte_77FE4E[0] = 0;
            rf_replicator_reset(&unk_77FE6C);
          }
        }
      }
      v8 = rf_multiplayer_game_mode_get();
      if ( v8 == 1 || v8 == 2 )
      {
        if ( !unk_77FE54 )
        {
          rf_render_color_set_rgba8(255, 0, 0, (int)unk_77FE50);
LABEL_17:
          v6 = dword_757BB0;
          v1 = (unsigned __int8 *)rf_string_object_c_str_or_empty(dword_77FE58);
          rf_font_measure_text_extent(&v10, &v9, v1, -1, v6);
          v7 = dword_182ABBC;
          v5 = dword_757BB0;
          v4 = (unsigned __int8 *)rf_string_object_c_str_or_empty(dword_77FE58);
          v3 = rf_renderer_get_viewport_height() / 2 - 3 * v9;
          viewport_width = rf_renderer_get_viewport_width();
          return rf_font_draw_text_screen(viewport_width / 2 - v10 / 2, v3, v4, v5, v7);
        }
        if ( unk_77FE54 == 1 )
        {
          rf_render_color_set_rgba8(0, 0, 255, (int)unk_77FE50);
          goto LABEL_17;
        }
      }
      rf_render_color_set_rgba8(0, 255, 0, (int)unk_77FE50);
      goto LABEL_17;
    }
  }
  return result;
}

