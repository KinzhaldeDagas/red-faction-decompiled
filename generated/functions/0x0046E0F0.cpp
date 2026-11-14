// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046E0F0 rf_persona_history_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): cdecl suppressInput LOW BYTE: zero calls history input46E4D0; nonzero skips it. Calls442950 with NO explicit arguments (incoming ECX unused there), then
// player_render_view(localPlayer,0) with no own null check. Draws black alpha100 viewport overlay and centered message_log bitmap scaled by6F8990 for BOTH dimensions. Draws
// EVERY6F8B90 control virtual0 with ECX=this/no arguments, no own BYTE9 gate. Draws localized centered title at y=centerY+9 in large font, green empty message at centerY+200 in
// medium font when count0. Nonempty branch sets history clip6F8970/7C/94/74, y=5, index=newest-viewoffset; loops while j<count-viewoffset. Negative index is adjusted by ADD80
// (differs from height helper EXACT79); entry lookup has no null guard. Visible when y+SIGNED WORD entry+0x106>=0 AND y<=clipHeight. Uses signed persona WORD+0x104
// bounded0..personaCount-1, nonempty display RFString6EF1B0+296*persona else base persona record string; draws persona at x5 and inline entry text at x70. Visible entries j>0 get
// line from(5,y-5) to(clipWidth-5,y-5). Advances y by signed layout height and index--. Resets full viewport at nonempty end; empty branch skips that final reset. Existing
// persona-lifecycle note retained; this resolves its prior callback/menu-control uncertainty without changing stored types.
int __cdecl rf_persona_history_render(char a1)
{
  int viewport_width; // eax
  _DWORD *v2; // eax
  unsigned __int8 *v4; // eax
  int viewport_height; // [esp+Ch] [ebp-34h]
  int v6; // [esp+Ch] [ebp-34h]
  int v7; // [esp+10h] [ebp-30h]
  int v8; // [esp+10h] [ebp-30h]
  float v9; // [esp+18h] [ebp-28h]
  float v10; // [esp+1Ch] [ebp-24h]
  rf_persona_history_entry *v11; // [esp+2Ch] [ebp-14h]
  int j; // [esp+30h] [ebp-10h]
  int v13; // [esp+34h] [ebp-Ch]
  int index; // [esp+38h] [ebp-8h]
  int indexa; // [esp+38h] [ebp-8h]
  int i; // [esp+3Ch] [ebp-4h]

  if ( !a1 )
    rf_persona_history_process_input();
  rf_render_local_player_auxiliary_views_and_visibility_union();
  rf_player_render_view(rf_local_fpgun_player, 0);
  rf_render_color_set_rgba8(0, 0, 0, 100);
  v7 = dword_182ABB8;
  viewport_height = rf_renderer_get_viewport_height();
  viewport_width = rf_renderer_get_viewport_width();
  rf_renderer_fill_rectangle_clipped(0, 0, viewport_width, viewport_height, v7);
  rf_render_color_set_rgba8(0, 0, 0, 255);
  rf_bitmap_blit_subrectangle_backend_dispatch(
    dword_6F89A0,
    unk_6F89AC,
    dword_6F89B0,
    (int)((double)dword_6F89A4 * unk_6F8990),
    (int)((double)dword_6F89A8 * unk_6F8990),
    0,
    0,
    dword_6F89A4,
    dword_6F89A8,
    0,
    0,
    dword_187CC7C);
  for ( i = 0; i < rf_receiver_get_first_dword(unk_6F8B90); ++i )
  {
    v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8B90, i);
    (**(void (__thiscall ***)(_DWORD))*v2)(*v2);
  }
  rf_render_color_set_rgba8(0, 0, 0, 255);
  rf_font_draw_text_screen(0x8000, dword_6F89B0 + 9, unk_88D780, unk_757664, dword_182ABBC);
  rf_render_color_set_rgba8(0, 192, 0, 255);
  if ( !rf_persona_history_get_count() )
    return rf_font_draw_text_screen(0x8000, dword_6F89B0 + 200, unk_88D784, dword_757BB0, dword_182ABBC);
  rf_renderer_set_viewport_and_relative_clip(unk_6F8970, unk_6F897C, unk_6F8994, dword_6F8974);
  v13 = 5;
  index = rf_persona_history_get_newest_index() - dword_6F899C;
  for ( j = 0; j < rf_persona_history_get_count() - dword_6F899C; ++j )
  {
    indexa = index + (index < 0 ? 0x50 : 0);
    v11 = rf_persona_history_entry_at(indexa);
    if ( v13 + v11->layout_height >= 0 && v13 <= dword_6F8974 )
    {
      rf_render_color_set_packed_rgba8(byte_6EE6A4);
      if ( v11->persona_index >= 0 && v11->persona_index < rf_hud_persona_count )
      {
        if ( rf_string_is_empty((int *)&unk_6EF1B0 + 74 * v11->persona_index) )
        {
          v8 = dword_182ABBC;
          v6 = dword_757BB0;
          v4 = (unsigned __int8 *)rf_string_object_c_str_or_empty(&rf_hud_persona_records[296 * v11->persona_index]);
        }
        else
        {
          v8 = dword_182ABBC;
          v6 = dword_757BB0;
          v4 = (unsigned __int8 *)rf_string_object_c_str_or_empty((char *)&unk_6EF1B0 + 296 * v11->persona_index);
        }
        rf_font_draw_text_screen(5, v13, v4, v6, v8);
      }
      rf_render_color_set_packed_rgba8(byte_6EE6A8);
      rf_font_draw_text_screen(70, v13, (unsigned __int8 *)v11, dword_757BB0, dword_182ABBC);
      if ( j > 0 )
      {
        v10 = (double)v13 - 5.0;
        v9 = (double)unk_6F8994 - 5.0;
        rf_renderer_draw_screen_line_clipped(5.0, v10, v9, v10, dword_187CC5C);
      }
    }
    v13 += v11->layout_height;
    index = indexa - 1;
  }
  return rf_renderer_reset_viewport_full_screen();
}

