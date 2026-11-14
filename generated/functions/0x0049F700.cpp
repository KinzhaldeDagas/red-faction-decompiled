// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049F700 rf_multiplayer_chat_input_bar_render
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Logical cdecl(by-value prefix RFString8,by-value input RFString8),16 bytes; former saved3-DWORD signature omitted final word and is corrected to4 raw DWORDs. Concatenates original
// strings and compares to verified empty literal63A4AB; empty combination destroys both owned args and returns without drawing/toggling blink. Otherwise copies input to
// temporary,measures prefix/input font extents,available width=PHYSICAL screen width-330-prefixWidth. Repeatedly drops first input character via inclusive substring(1,-1) and
// remeasures until fits; no no-progress/negative-width guard,so narrow windows can loop with empty suffix. Original input remains unchanged.
// Uses VIEWPORT width for frame: sides(157,118,2,17)/(width-158,118,2,17),top/bottom(159,116/133,width-317,2),fill(159,118,width-317,15). White frame alpha255 if BYTE757658 nonzero
// else77; black fill alpha255 else128. Green(53,207,22,255) prefix+trimmed input at163,119. Viewport height queried but unused. Blink timer77FE68 only elapsed AL EXACT1 rearms350ms
// and maps state77FE2C(1=>0,all others=>1); state exactly1 draws5-pixel cursor from x=165+prefixWidth+suffixWidth,y=119+lastMeasuredHeight using187CC5C. Destroys temporaries and BOTH
// owned args (including SEH); does not send chat/change input content.
void __cdecl rf_multiplayer_chat_input_bar_render(int prefix_word0, int prefix_word1, int text_word0, int text_word1)
{
  unsigned __int8 *v4; // eax
  unsigned __int8 *v5; // eax
  unsigned __int8 *v6; // eax
  unsigned __int8 *v7; // eax
  float v8; // [esp+0h] [ebp-94h]
  float v9; // [esp+8h] [ebp-8Ch]
  float v10; // [esp+Ch] [ebp-88h]
  int v11; // [esp+10h] [ebp-84h]
  std::exception *v12; // [esp+28h] [ebp-6Ch]
  _DWORD *v13; // [esp+30h] [ebp-64h]
  void *v14; // [esp+38h] [ebp-5Ch]
  _BYTE v15[8]; // [esp+40h] [ebp-54h] BYREF
  _DWORD v16[2]; // [esp+48h] [ebp-4Ch] BYREF
  _BYTE v17[11]; // [esp+50h] [ebp-44h] BYREF
  bool v18; // [esp+5Bh] [ebp-39h]
  int v19; // [esp+5Ch] [ebp-38h] BYREF
  int v20; // [esp+60h] [ebp-34h] BYREF
  int v21; // [esp+64h] [ebp-30h] BYREF
  _DWORD v22[2]; // [esp+68h] [ebp-2Ch] BYREF
  int viewport_width; // [esp+70h] [ebp-24h]
  int v24; // [esp+74h] [ebp-20h]
  unsigned __int8 v25; // [esp+7Bh] [ebp-19h]
  int v26; // [esp+7Ch] [ebp-18h]
  int v27; // [esp+80h] [ebp-14h]
  int viewport_height; // [esp+84h] [ebp-10h]
  int v29; // [esp+90h] [ebp-4h]

  v29 = 1;
  v14 = rf_string_concat_two_objects(v17, &prefix_word0, (int)&text_word0);
  LOBYTE(v29) = 2;
  v18 = rf_string_equals_case_insensitive((int)v14, (char *)&byte_63A4AB);
  LOBYTE(v29) = 1;
  rf_string_destroy_buffer(v17);
  if ( v18 )
  {
    LOBYTE(v29) = 0;
    rf_string_destroy_buffer(&prefix_word0);
    v29 = -1;
    rf_string_destroy_buffer(&text_word0);
  }
  else
  {
    viewport_width = rf_renderer_get_viewport_width();
    viewport_height = rf_renderer_get_viewport_height();
    rf_string_copy_construct_from_object(v22, (char **)&text_word0);
    LOBYTE(v29) = 3;
    v4 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v22);
    rf_font_measure_text_extent(&v21, &v20, v4, -1, -1);
    v5 = (unsigned __int8 *)rf_string_object_c_str_or_empty(&prefix_word0);
    rf_font_measure_text_extent(&v19, &v20, v5, -1, -1);
    v24 = rf_renderer_get_physical_screen_width() - 330 - v19;
    while ( v21 > v24 )
    {
      v13 = rf_string_substring_inclusive(v22, v16, 1, -1);
      LOBYTE(v29) = 4;
      rf_string_assign_from_object(v22, (int)v13);
      LOBYTE(v29) = 3;
      rf_string_destroy_buffer(v16);
      v6 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v22);
      rf_font_measure_text_extent(&v21, &v20, v6, -1, -1);
    }
    v25 = byte_757658[0];
    v26 = 160;
    v27 = 119;
    rf_render_color_set_rgba8(255, 255, 255, byte_757658[0] != 0 ? 255 : 77);
    rf_renderer_fill_rectangle_clipped(157, 118, 2, 17, dword_182ABB8);
    rf_renderer_fill_rectangle_clipped(viewport_width - 158, 118, 2, 17, dword_182ABB8);
    rf_renderer_fill_rectangle_clipped(159, 116, viewport_width - 317, 2, dword_182ABB8);
    rf_renderer_fill_rectangle_clipped(159, 133, viewport_width - 317, 2, dword_182ABB8);
    rf_render_color_set_rgba8(0, 0, 0, v25 != 0 ? 255 : 128);
    rf_renderer_fill_rectangle_clipped(159, 118, viewport_width - 317, 15, dword_182ABB8);
    rf_render_color_set_rgba8(53, 207, 22, 255);
    v11 = dword_182ABBC;
    v12 = (std::exception *)rf_string_concat_two_objects(v15, &prefix_word0, (int)v22);
    LOBYTE(v29) = 5;
    v7 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v12);
    rf_font_draw_text_screen(163, 119, v7, -1, v11);
    LOBYTE(v29) = 3;
    rf_string_destroy_buffer(v15);
    if ( rf_replicator_has_elapsed(&unk_77FE68) )
    {
      rf_replicator_arm_milliseconds(&unk_77FE68, 350);
      byte_77FE2C[0] = byte_77FE2C[0] != 1;
    }
    if ( byte_77FE2C[0] == 1 )
    {
      v10 = (float)(v20 + v27);
      v9 = (float)(v19 + v26 + v21 + 10);
      v8 = (float)(v19 + v26 + v21 + 5);
      rf_renderer_draw_screen_line_clipped(v8, v10, v9, v10, dword_187CC5C);
    }
    LOBYTE(v29) = 1;
    rf_string_destroy_buffer(v22);
    LOBYTE(v29) = 0;
    rf_string_destroy_buffer(&prefix_word0);
    v29 = -1;
    rf_string_destroy_buffer(&text_word0);
  }
}

