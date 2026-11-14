// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045B8A0 rf_multiplayer_level_list_draw_row
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl(filteredRowIndex,visibleRowOrdinal),no own bounds/negative-row guard. Compute scaled absolute list x,width and
// y=scaled absoluteY+raw pixel rowHeight6F299C*visibleOrdinal,using truncation toward zero. Set packed color6F29D0;current row6F2D08
// fills(x-2,y,width+4,rowHeight,renderer182ABB8),then color6F29CC. Search rotation array for FIRST index equal row: glyphAB and one-based rotation position formatted " %c
// %2d";otherwise glyphAA and " %c --". Draw three columns using scaled offsets661ED0/4/8 and widths661EDC/E0/E4. Second column is record RFString+8 (extensionless filename);copy
// UNBOUNDED into128-byte stack buffer BEFORE trimming helper458CF0(font6F29B4,columnWidth,32). Third is "- " plus record RFString+0 display title,also unbounded copy/append before
// same trim. Actual record stride16 via45DEA0. Three font draws use fontID DWORD6F29B4 and renderMode DWORD182ABBC;no text escaping,UTF8 processing,capacity check or prior-color restore. Long source may
// overflow before trimming.
int __cdecl rf_multiplayer_level_list_draw_row(int a1, int a2)
{
  int v2; // eax
  const void *v3; // eax
  char *v6; // [esp+Ch] [ebp-D0h]
  const char *v7; // [esp+1Ch] [ebp-C0h]
  unsigned int v8; // [esp+20h] [ebp-BCh]
  char v9; // [esp+27h] [ebp-B5h]
  char *v10; // [esp+2Ch] [ebp-B0h]
  const char *v11; // [esp+30h] [ebp-ACh]
  int v12; // [esp+3Ch] [ebp-A0h]
  int v13; // [esp+3Ch] [ebp-A0h]
  int v14; // [esp+3Ch] [ebp-A0h]
  int i; // [esp+40h] [ebp-9Ch] BYREF
  char Buffer[128]; // [esp+44h] [ebp-98h] BYREF
  int v17; // [esp+C8h] [ebp-14h]
  int v18; // [esp+CCh] [ebp-10h]
  int v19; // [esp+D0h] [ebp-Ch]
  int v20; // [esp+D4h] [ebp-8h]
  char v21; // [esp+DBh] [ebp-1h]

  v17 = (int)((double)rf_ui_control_absolute_x(&dword_6F3334) * rf_ui_scale_x);
  v20 = (int)((double)unk_6F3348 * rf_ui_scale_x);
  v18 = dword_6F299C * a2 + (int)((double)rf_ui_control_absolute_y(&dword_6F3334) * rf_ui_scale_y);
  rf_render_color_set_packed_rgba8(byte_6F29D0);
  if ( a1 == unk_6F2D08 )
  {
    rf_renderer_fill_rectangle_clipped(v17 - 2, v18, v20 + 4, dword_6F299C, dword_182ABB8);
    rf_render_color_set_packed_rgba8(byte_6F29CC);
  }
  v21 = -86;
  for ( i = 0; i < rf_receiver_get_first_dword(unk_6F2E64); ++i )
  {
    if ( *(_DWORD *)sub_552200(unk_6F2E64, i) == a1 )
    {
      v21 = -85;
      break;
    }
  }
  v12 = v17 + (int)((double)dword_661ED0 * rf_ui_scale_x);
  v19 = (int)((double)dword_661EDC * rf_ui_scale_x);
  if ( i >= rf_receiver_get_first_dword(unk_6F2E64) )
    sprintf(Buffer, " %c --", v21);
  else
    sprintf(Buffer, " %c %2d", v21, i + 1);
  rf_font_draw_text_screen(v12, v18, (unsigned __int8 *)Buffer, dword_6F29B4, dword_182ABBC);
  v13 = v17 + (int)((double)dword_661ED4 * rf_ui_scale_x);
  v19 = (int)((double)dword_661EE0 * rf_ui_scale_x);
  v2 = rf_two_rfstring_array16_element_address_unchecked(dword_6F2DC4, a1);
  v11 = rf_string_object_c_str_or_empty((const void *)(v2 + 8));
  v10 = Buffer;
  do
  {
    v9 = *v11;
    *v10++ = *v11++;
  }
  while ( v9 );
  rf_ui_trim_cstring_to_width_with_ellipsis(Buffer, dword_6F29B4, v19, 32);
  rf_font_draw_text_screen(v13, v18, (unsigned __int8 *)Buffer, dword_6F29B4, dword_182ABBC);
  v14 = v17 + (int)((double)dword_661ED8 * rf_ui_scale_x);
  v19 = (int)((double)dword_661EE4 * rf_ui_scale_x);
  strcpy(Buffer, "- ");
  v3 = (const void *)rf_two_rfstring_array16_element_address_unchecked(dword_6F2DC4, a1);
  v7 = rf_string_object_c_str_or_empty(v3);
  v8 = (unsigned int)&v7[strlen(v7) + 1];
  v6 = (char *)&i + 3;
  while ( *++v6 )
    ;
  qmemcpy(v6, v7, v8 - (_DWORD)v7);
  rf_ui_trim_cstring_to_width_with_ellipsis(Buffer, dword_6F29B4, v19, 32);
  return rf_font_draw_text_screen(v14, v18, (unsigned __int8 *)Buffer, dword_6F29B4, dword_182ABBC);
}

