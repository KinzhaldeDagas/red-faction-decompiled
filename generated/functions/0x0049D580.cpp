// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049D580 rf_multiplayer_hud_render_three_line_intro
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): No arguments. If BYTE77FE4C is EXACT1, skips. Otherwise before shared deadline77FF14 elapsed draws opaque green; after elapsed subtracts
// frameDelta*500 from float alpha662944 and stores binary32. ONLY ordered alpha<0 clamps0, sets BYTE77FE4C=1 and returns without drawing; alpha==0 still draws, unordered does not
// clamp. Green alpha otherwise truncates stored float. Copies three RFStrings6FC314/6FC324/6FC32C into owned temporaries, individually measures default font(-1) and draws each
// centered x=trunc(viewportWidth/2)-trunc(ownWidth/2). Own measured heights place lines at viewportHeight-3*h-5, -2*h-5, -h-5 respectively. Each line uses its OWN height, not common
// stacked height. Destroys temporaries including SEH. No empty-string skip, color restore, viewport scaling or explicit return contract. Existing global visibility name does not
// imply this routine renders the time-left clock.
void rf_multiplayer_hud_render_three_line_intro()
{
  unsigned __int8 *v0; // eax
  int viewport_width; // eax
  unsigned __int8 *v2; // eax
  int v3; // eax
  unsigned __int8 *v4; // eax
  int v5; // eax
  int v6; // [esp-10h] [ebp-40h]
  int v7; // [esp-10h] [ebp-40h]
  int v8; // [esp-10h] [ebp-40h]
  unsigned __int8 *v9; // [esp-Ch] [ebp-3Ch]
  unsigned __int8 *v10; // [esp-Ch] [ebp-3Ch]
  unsigned __int8 *v11; // [esp-Ch] [ebp-3Ch]
  int v12; // [esp-4h] [ebp-34h]
  int v13; // [esp-4h] [ebp-34h]
  int v14; // [esp-4h] [ebp-34h]
  int v15; // [esp+4h] [ebp-2Ch] BYREF
  _DWORD v16[2]; // [esp+8h] [ebp-28h] BYREF
  int v17; // [esp+10h] [ebp-20h] BYREF
  _DWORD v18[2]; // [esp+14h] [ebp-1Ch] BYREF
  _DWORD v19[2]; // [esp+1Ch] [ebp-14h] BYREF
  int v20; // [esp+2Ch] [ebp-4h]

  if ( rf_multiplayer_time_left_visible != 1 )
  {
    if ( rf_replicator_has_elapsed(&unk_77FF14) )
    {
      flt_662944 = flt_662944 - rf_frame_delta_seconds * 500.0;
      if ( flt_662944 < 0.0 )
      {
        flt_662944 = 0.0;
        rf_multiplayer_time_left_visible = 1;
        return;
      }
      rf_render_color_set_rgba8(0, 255, 0, (int)flt_662944);
    }
    else
    {
      rf_render_color_set_rgba8(0, 255, 0, 255);
    }
    rf_string_copy_construct_from_object(v19, (char **)unk_6FC314);
    v20 = 0;
    rf_string_copy_construct_from_object(v16, (char **)unk_6FC324);
    LOBYTE(v20) = 1;
    rf_string_copy_construct_from_object(v18, (char **)unk_6FC32C);
    LOBYTE(v20) = 2;
    v0 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v19);
    rf_font_measure_text_extent(&v17, &v15, v0, -1, -1);
    v12 = dword_182ABBC;
    v9 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v19);
    v6 = rf_renderer_get_viewport_height() - 3 * v15 - 5;
    viewport_width = rf_renderer_get_viewport_width();
    rf_font_draw_text_screen(viewport_width / 2 - v17 / 2, v6, v9, -1, v12);
    v2 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v16);
    rf_font_measure_text_extent(&v17, &v15, v2, -1, -1);
    v13 = dword_182ABBC;
    v10 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v16);
    v7 = rf_renderer_get_viewport_height() - 2 * v15 - 5;
    v3 = rf_renderer_get_viewport_width();
    rf_font_draw_text_screen(v3 / 2 - v17 / 2, v7, v10, -1, v13);
    v4 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v18);
    rf_font_measure_text_extent(&v17, &v15, v4, -1, -1);
    v14 = dword_182ABBC;
    v11 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v18);
    v8 = rf_renderer_get_viewport_height() - v15 - 5;
    v5 = rf_renderer_get_viewport_width();
    rf_font_draw_text_screen(v5 / 2 - v17 / 2, v8, v11, -1, v14);
    LOBYTE(v20) = 1;
    rf_string_destroy_buffer(v18);
    LOBYTE(v20) = 0;
    rf_string_destroy_buffer(v16);
    v20 = -1;
    rf_string_destroy_buffer(v19);
  }
}

