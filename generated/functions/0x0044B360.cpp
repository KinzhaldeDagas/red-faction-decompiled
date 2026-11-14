// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044B360 sub_44B360
// UNREALRED VERIFIED [hud-persona-presentation-20261027] Ordinary caption rendering uses separate queued state, wraps at coordinate pair 37 X (0x6EE038), starts at pair 37 Y, and draws each line centered using sentinel 0x8000 with font argument 0x663050. Persona uses 0x663048 for centered name (fixed X=193,Y=82 plus contextual offset) and 0x663050 for wrapped body. Both fields are image-initialized -1 and have no direct writers in this scoped xref audit; negative font arguments consume the current default font, not HUD bigfont/smallfont handles.
char sub_44B360()
{
  char *v0; // eax
  char Destination[264]; // [esp+0h] [ebp-140h] BYREF
  int v3; // [esp+10Ch] [ebp-34h]
  int line_lengths[4]; // [esp+110h] [ebp-30h] BYREF
  int line_offsets[4]; // [esp+120h] [ebp-20h] BYREF
  char *Source; // [esp+130h] [ebp-10h]
  int v7; // [esp+134h] [ebp-Ch]
  int height_select_current; // [esp+138h] [ebp-8h]
  int i; // [esp+13Ch] [ebp-4h]

  height_select_current = rf_font_get_height_select_current(-1);
  LOBYTE(v0) = rf_render_color_set_packed_rgba8(byte_6EE6A8);
  if ( dword_6616C8 >= 0 )
  {
    v0 = (char *)&unk_6EE6E0 + 272 * dword_6616C8;
    Source = v0;
    v7 = unk_6EE03C;
    if ( v0 )
    {
      Destination[256] = 0;
      v3 = rf_text_wrap_into_offset_length_arrays(line_lengths, line_offsets, Source, dword_6EE038, 4, 0, dword_663050);
      LOBYTE(v0) = (unsigned __int8)strncpy(Destination, Source, 0x100u);
      for ( i = 0; i < v3; ++i )
      {
        LOBYTE(v0) = i;
        Destination[line_lengths[i] + line_offsets[i]] = 0;
      }
      for ( i = 0; i < v3; ++i )
      {
        rf_font_draw_text_screen(
          0x8000,
          v7,
          (unsigned __int8 *)&Destination[line_offsets[i]],
          dword_663050,
          unk_182ABBC);
        v7 += height_select_current;
        LOBYTE(v0) = i + 1;
      }
    }
  }
  return (char)v0;
}

