// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00463470 rf_browser_draw_server_row
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Cdecl(displayIndex,visibleOrdinal). Resolve raw row=indexArray6F52D4[displayIndex],no bounds. Y=pixelRowHeight*ordinal+trunc(absListY*scaleY). Full mod64 strlen chooses
// mod/default color;selected displayIndex fills scaled list width rectangle and changes text color. ColumnX=trunc((absListX+logicalOffset)*scaleX),sum BEFORE conversion. Favorite
// glyphAA/AB from high80000000;server name;SIGNED pingWORD94 negative placeholder,0..999 decimal,>999 literal >999 with measured right alignment;map;unsignedBYTE players/max as%d/%d.
// Draw flag1 glyphA6 and flag2 glyphA7 at right edge spaced by measured6F51AC. FilterDWORD6F5994==3 and mod nonempty ->unbounded sprintf modeText : mod;otherwise mod if nonempty else
// dereferenced localized mode6F3AE4[mode80]. No mode bounds/pointer guard. Unbounded string copies/formatting into stack Buffer BEFORE trim-to-width(capacity32);trim is not pre-copy
// protection. Last width=trunc(columnWidth*scaleX)-2*glyphWidth. No row/string/width admission or render-color restore;returns last draw residue.
int __cdecl rf_browser_draw_server_row(int a1, int a2)
{
  char v3; // [esp+7h] [ebp-D1h]
  char *v4; // [esp+Ch] [ebp-CCh]
  char *v5; // [esp+10h] [ebp-C8h]
  char v6; // [esp+17h] [ebp-C1h]
  char *v7; // [esp+1Ch] [ebp-BCh]
  char *v8; // [esp+20h] [ebp-B8h]
  char v9; // [esp+27h] [ebp-B1h]
  char *v10; // [esp+2Ch] [ebp-ACh]
  char *v11; // [esp+30h] [ebp-A8h]
  char v12; // [esp+3Fh] [ebp-99h]
  char *v13; // [esp+44h] [ebp-94h]
  char *v14; // [esp+48h] [ebp-90h]
  char v15; // [esp+67h] [ebp-71h]
  char *p_Buffer; // [esp+6Ch] [ebp-6Ch]
  char *v17; // [esp+70h] [ebp-68h]
  char *v18; // [esp+88h] [ebp-50h]
  char *v19; // [esp+8Ch] [ebp-4Ch]
  char v20[7]; // [esp+94h] [ebp-44h] BYREF
  char v21; // [esp+9Bh] [ebp-3Dh]
  char Buffer; // [esp+9Ch] [ebp-3Ch] BYREF
  _BYTE v23[3]; // [esp+9Dh] [ebp-3Bh] BYREF
  BOOL v24; // [esp+C0h] [ebp-18h]
  int v25; // [esp+C4h] [ebp-14h]
  int v26; // [esp+C8h] [ebp-10h]
  int v27; // [esp+CCh] [ebp-Ch]
  int v28; // [esp+D0h] [ebp-8h]
  int v29; // [esp+D4h] [ebp-4h] BYREF

  v25 = *((_DWORD *)MEMORY[0x6F52D4] + a1);
  v26 = dword_6F299C * a2 + (int)((double)rf_ui_control_absolute_y(&dword_6F57B4) * rf_ui_scale_y);
  v18 = (char *)dword_6F52CC + 108 * v25 + 65;
  v19 = (char *)dword_6F52CC + 108 * v25 + strlen((const char *)dword_6F52CC + 108 * v25 + 64) + 65;
  v24 = v19 != v18;
  if ( v19 == v18 )
    rf_render_color_set_packed_rgba8(byte_6F29D0);
  else
    rf_render_color_set_packed_rgba8(byte_6F55EC);
  if ( a1 == unk_6F52E0 )
  {
    v27 = (int)((double)rf_ui_control_absolute_x(&dword_6F57B4) * rf_ui_scale_x);
    rf_renderer_fill_rectangle_clipped(
      v27,
      v26,
      (int)((double)dword_661FD8 * rf_ui_scale_x),
      dword_6F299C,
      dword_182ABB8);
    rf_render_color_set_packed_rgba8(byte_6F29CC);
  }
  v27 = (int)((double)(dword_661FA0 + rf_ui_control_absolute_x(&dword_6F57B4)) * rf_ui_scale_x);
  v21 = (*((int *)dword_6F52CC + 27 * v25 + 26) < 0) - 86;
  sprintf(&Buffer, "%c", v21);
  rf_font_draw_text_screen(v27, v26, (unsigned __int8 *)&Buffer, dword_6F29B4, dword_182ABBC);
  v27 = (int)((double)(dword_661FA4 + rf_ui_control_absolute_x(&dword_6F57B4)) * rf_ui_scale_x);
  v17 = (char *)dword_6F52CC + 108 * v25;
  p_Buffer = &Buffer;
  do
  {
    v15 = *v17;
    *p_Buffer++ = *v17++;
  }
  while ( v15 );
  rf_ui_trim_cstring_to_width_with_ellipsis(&Buffer, dword_6F29B4, (int)((double)dword_661FBC * rf_ui_scale_x), 32);
  rf_font_draw_text_screen(v27, v26, (unsigned __int8 *)&Buffer, dword_6F29B4, dword_182ABBC);
  v27 = (int)((double)(dword_661FA8 + rf_ui_control_absolute_x(&dword_6F57B4)) * rf_ui_scale_x);
  v28 = (int)((double)dword_661FC0 * rf_ui_scale_x);
  if ( *((__int16 *)dword_6F52CC + 54 * v25 + 47) >= 0 )
  {
    if ( *((__int16 *)dword_6F52CC + 54 * v25 + 47) <= 999 )
      sprintf(&Buffer, "%d", *((__int16 *)dword_6F52CC + 54 * v25 + 47));
    else
      sprintf(&Buffer, ">999");
    rf_ui_trim_cstring_to_width_with_ellipsis(&Buffer, dword_6F29B4, v28, 32);
  }
  else
  {
    sprintf(&Buffer, off_636A88);
  }
  rf_font_measure_text_extent(&v29, v20, (unsigned __int8 *)&Buffer, &v23[strlen(&Buffer)] - v23, dword_6F29B4);
  rf_font_draw_text_screen(v28 + v27 - v29, v26, (unsigned __int8 *)&Buffer, dword_6F29B4, dword_182ABBC);
  v27 = (int)((double)(dword_661FAC + rf_ui_control_absolute_x(&dword_6F57B4)) * rf_ui_scale_x);
  v14 = (char *)dword_6F52CC + 108 * v25 + 32;
  v13 = &Buffer;
  do
  {
    v12 = *v14;
    *v13++ = *v14++;
  }
  while ( v12 );
  rf_ui_trim_cstring_to_width_with_ellipsis(&Buffer, dword_6F29B4, (int)((double)dword_661FC4 * rf_ui_scale_x), 32);
  rf_font_draw_text_screen(v27, v26, (unsigned __int8 *)&Buffer, dword_6F29B4, dword_182ABBC);
  v27 = (int)((double)(dword_661FB0 + rf_ui_control_absolute_x(&dword_6F57B4)) * rf_ui_scale_x);
  sprintf(
    &Buffer,
    "%d/%d",
    *((unsigned __int8 *)dword_6F52CC + 108 * v25 + 92),
    *((unsigned __int8 *)dword_6F52CC + 108 * v25 + 93));
  rf_ui_trim_cstring_to_width_with_ellipsis(&Buffer, dword_6F29B4, (int)((double)dword_661FC8 * rf_ui_scale_x), 32);
  rf_font_draw_text_screen(v27, v26, (unsigned __int8 *)&Buffer, dword_6F29B4, dword_182ABBC);
  v21 = (*((_DWORD *)dword_6F52CC + 27 * v25 + 26) & 1) != 0 ? -90 : 32;
  sprintf(&Buffer, "%c", v21);
  v27 = (int)((double)(unk_6F57C8 + rf_ui_control_absolute_x(&dword_6F57B4)) * rf_ui_scale_x) - unk_6F51AC;
  rf_font_draw_text_screen(v27, v26, (unsigned __int8 *)&Buffer, dword_6F29B4, dword_182ABBC);
  v21 = (*((_DWORD *)dword_6F52CC + 27 * v25 + 26) & 2) != 0 ? -89 : 32;
  sprintf(&Buffer, "%c", v21);
  v27 -= unk_6F51AC;
  rf_font_draw_text_screen(v27, v26, (unsigned __int8 *)&Buffer, dword_6F29B4, dword_182ABBC);
  if ( unk_6F5994 == 3 )
  {
    if ( v24 )
    {
      sprintf(
        &Buffer,
        "%s : %s",
        *(const char **)dword_6F3AE4[*((_DWORD *)dword_6F52CC + 27 * v25 + 20)],
        (const char *)dword_6F52CC + 108 * v25 + 64);
    }
    else
    {
      v11 = *(char **)dword_6F3AE4[*((_DWORD *)dword_6F52CC + 27 * v25 + 20)];
      v10 = &Buffer;
      do
      {
        v9 = *v11;
        *v10++ = *v11++;
      }
      while ( v9 );
    }
  }
  else if ( v24 )
  {
    v8 = (char *)dword_6F52CC + 108 * v25 + 64;
    v7 = &Buffer;
    do
    {
      v6 = *v8;
      *v7++ = *v8++;
    }
    while ( v6 );
  }
  else
  {
    v5 = *(char **)dword_6F3AE4[*((_DWORD *)dword_6F52CC + 27 * v25 + 20)];
    v4 = &Buffer;
    do
    {
      v3 = *v5;
      *v4++ = *v5++;
    }
    while ( v3 );
  }
  v27 = (int)((double)(dword_661FB4 + rf_ui_control_absolute_x(&dword_6F57B4)) * rf_ui_scale_x);
  rf_ui_trim_cstring_to_width_with_ellipsis(
    &Buffer,
    dword_6F29B4,
    (int)((double)dword_661FCC * rf_ui_scale_x) - 2 * unk_6F51AC,
    32);
  return rf_font_draw_text_screen(v27, v26, (unsigned __int8 *)&Buffer, dword_6F29B4, dword_182ABBC);
}

