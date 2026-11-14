// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046BBF0 rf_gameplay_priority_draw_weapon_row
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Cdecl(rowIndex,visibleOrdinal). Compute scaled absolute listXY (Y plus raw pixelRowHeight*ordinal),set default color. Selected index highlights
// scaled width662430/pixel height and changes color BEFORE row/player admission. Native SIGNED guards require0<=rowIndex<32,localPlayer nonNULL,then0<=weaponID(player4436+4*row)<64.
// Decompiler unsigned notation hides explicit negative guards. ValidID:display-name RFString at rf_weapon_records_display_name+1360*ID,c_str_or_empty,strncpy127 tostack,force
// destination127NUL,draw text. No qualifyingCount/weapon flag/name eligibility filter,ellipsis/width trimming or save. Invalid row/ID can still have highlighted background;EAX/AL
// return incidental mixed delegate residues.
char __cdecl rf_gameplay_priority_draw_weapon_row(unsigned int a1, int a2)
{
  unsigned int v2; // eax
  const char *v3; // eax
  char Destination[132]; // [esp+Ch] [ebp-90h] BYREF
  int v6; // [esp+94h] [ebp-8h]
  int v7; // [esp+98h] [ebp-4h]

  v6 = dword_6F299C * a2 + (int)((double)rf_ui_control_absolute_y(&dword_6F7C94) * rf_ui_scale_y);
  v7 = (int)((double)rf_ui_control_absolute_x(&dword_6F7C94) * rf_ui_scale_x);
  LOBYTE(v2) = rf_render_color_set_packed_rgba8(byte_6F29D0);
  if ( a1 == unk_6F7B88 )
  {
    rf_renderer_fill_rectangle_clipped(v7, v6, (int)((double)dword_662430 * rf_ui_scale_x), dword_6F299C, dword_182ABB8);
    LOBYTE(v2) = rf_render_color_set_packed_rgba8(byte_6F29CC);
  }
  if ( a1 < 0x20 )
  {
    if ( rf_local_fpgun_player )
    {
      v2 = *(_DWORD *)(rf_local_fpgun_player + 4 * a1 + 4436);
      if ( v2 < 0x40 )
      {
        v3 = rf_string_object_c_str_or_empty((char *)&rf_weapon_records_display_name + 1360 * v2);
        strncpy(Destination, v3, 0x7Fu);
        Destination[127] = 0;
        LOBYTE(v2) = rf_font_draw_text_screen(v7, v6, (unsigned __int8 *)Destination, dword_6F29B4, dword_182ABBC);
      }
    }
  }
  return v2;
}

