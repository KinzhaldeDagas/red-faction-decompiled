// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00454B50 rf_save_list_a_draw_record_row
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl(record index,visible row), signed rawDWORDs without own range validation. BaseX=605F00(x87 absoluteX(control6F235C)*scaleX),
// width=convert(DWORD6F2370*scaleX), Y=convert(absoluteY*scaleY)+wrapped DWORD6F299C*row. Set render color packed6F29D0; selected==DWORD6F1FA0 draws
// rectangle(baseX-2,Y,width+4,rowHeight,live182ABB8), then sets color6F29CC. No prior color restore. Three column X offsets are 661DD4,661DD8,661DDC and widths 661DE0,661DE4,661DE8,
// each signed FILD*scaleX then605F00, without intermediate FLOAT32 spill. Record address via4580B0(array6F21AC,index), stride272. Column1:strncpy exactly260 bytes to local then FORCE
// local[259]=NUL AFTER copy;458CF0(buffer,fontDWORD6F29B4,scaledColumnWidth,capacity260),58CFC0(X,Y,buffer,font6F29B4,live182ABBC). Column2:unchecked record+260 pointer passed to
// localtime64 adapter454EB0; strftime(buffer,260,literal%c,returned tm), ignore NULL/strftime status, trim same way then draw. No preclear or post-strftime terminator repair in this
// wrapper. Column3:re-fetch record FLOAT+268 separately for hours/minutes/seconds. hours=convert(duration)/3600 via signed IDIV; minutes=convert(duration-FILD(wrapped3600*hours))/60;
// seconds=convert(duration-FILD(wrapped3600*hours)-FILD(wrapped60*minutes)). Intermediate subtracts remain x87 until605F00. Unbounded sprintf literal%02d:%02d:%02d, then draw WITHOUT
// trim to the computed third-column width (width calculated but unused for duration). No nonnegative-duration clamp, date/time validation, array-count check or stable record snapshot
// across delegates. Cookie check before epilogue; return incidental. These reads prove packed filename[260],64-bit timestamp+260,FLOAT elapsed_seconds+268.
int __cdecl rf_save_list_a_draw_record_row(int a1, int a2)
{
  const char *v2; // eax
  int v3; // eax
  const struct tm *Tm; // [esp+14h] [ebp-134h]
  int v6; // [esp+18h] [ebp-130h]
  int v7; // [esp+18h] [ebp-130h]
  int v8; // [esp+18h] [ebp-130h]
  int v9; // [esp+1Ch] [ebp-12Ch]
  int v10; // [esp+20h] [ebp-128h]
  int v11; // [esp+24h] [ebp-124h]
  char Destination[268]; // [esp+28h] [ebp-120h] BYREF
  int v13; // [esp+138h] [ebp-10h]
  int v14; // [esp+13Ch] [ebp-Ch]
  int v15; // [esp+140h] [ebp-8h]
  int v16; // [esp+144h] [ebp-4h]

  v13 = (int)((double)rf_ui_control_absolute_x(&dword_6F235C) * rf_ui_scale_x);
  v15 = (int)((double)unk_6F2370 * rf_ui_scale_x);
  v14 = dword_6F299C * a2 + (int)((double)rf_ui_control_absolute_y(&dword_6F235C) * rf_ui_scale_y);
  rf_render_color_set_packed_rgba8(byte_6F29D0);
  if ( a1 == unk_6F1FA0 )
  {
    rf_renderer_fill_rectangle_clipped(v13 - 2, v14, v15 + 4, dword_6F299C, dword_182ABB8);
    rf_render_color_set_packed_rgba8(byte_6F29CC);
  }
  v6 = v13 + (int)((double)dword_661DD4 * rf_ui_scale_x);
  v16 = (int)((double)dword_661DE0 * rf_ui_scale_x);
  v2 = (const char *)rf_record272_array_element_address_unchecked(dword_6F21AC, a1);
  strncpy(Destination, v2, 0x104u);
  Destination[259] = 0;
  rf_ui_trim_cstring_to_width_with_ellipsis(Destination, unk_6F29B4, v16, 260);
  rf_font_draw_text_screen(v6, v14, (unsigned __int8 *)Destination, unk_6F29B4, dword_182ABBC);
  v7 = v13 + (int)((double)dword_661DD8 * rf_ui_scale_x);
  v16 = (int)((double)dword_661DE4 * rf_ui_scale_x);
  v3 = rf_record272_array_element_address_unchecked(dword_6F21AC, a1);
  Tm = rf_localtime64_adapter_454eb0((__time64_t *)(v3 + 260));
  strftime(Destination, 0x104u, "%c", Tm);
  rf_ui_trim_cstring_to_width_with_ellipsis(Destination, unk_6F29B4, v16, 260);
  rf_font_draw_text_screen(v7, v14, (unsigned __int8 *)Destination, unk_6F29B4, dword_182ABBC);
  v8 = v13 + (int)((double)dword_661DDC * rf_ui_scale_x);
  v16 = (int)((double)dword_661DE8 * rf_ui_scale_x);
  v9 = (int)*(float *)(rf_record272_array_element_address_unchecked(dword_6F21AC, a1) + 268) / 3600;
  v10 = (int)(*(float *)(rf_record272_array_element_address_unchecked(dword_6F21AC, a1) + 268) - (double)(3600 * v9))
      / 60;
  v11 = (int)(*(float *)(rf_record272_array_element_address_unchecked(dword_6F21AC, a1) + 268)
            - (double)(3600 * v9)
            - (double)(60 * v10));
  sprintf(Destination, "%02d:%02d:%02d", v9, v10, v11);
  return rf_font_draw_text_screen(v8, v14, (unsigned __int8 *)Destination, unk_6F29B4, dword_182ABBC);
}

