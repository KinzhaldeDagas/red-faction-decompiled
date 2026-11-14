// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471000 rf_ui_button_build_centered_label
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall(label,font), RET8. Measures whole label into DWORDs+60/+64; signed-truncates (logicalWidth-measuredWidth)/2 and
// (logicalHeight-measuredHeight)/2 into origin+52/+56. Only if EXISTING label bitmap+48 signed>=0: clears it and draws original label when measured width>0. Does not allocate/resize
// bitmap, split newlines, store text/font, change control geometry/state or release resources. Return register is incidental; existing stored prototype retained.
char *__thiscall rf_ui_button_build_centered_label(_DWORD *this, char *a2, int a3)
{
  char *result; // eax

  rf_font_measure_text_extent(this + 15, this + 16, (unsigned __int8 *)a2, strlen(a2), a3);
  *(this + 13) = (*(this + 5) - *(this + 15)) / 2;
  *(this + 14) = (*(this + 6) - *(this + 16)) / 2;
  result = (char *)this;
  if ( (int)*(this + 12) >= 0 )
  {
    rf_bitmap_clear_all_locked_texture_tile_bytes(*(this + 12));
    result = (char *)this;
    if ( (int)*(this + 15) > 0 )
      return rf_font_draw_text_into_bitmap(*(this + 13), *(this + 14), *(this + 12), a2, a3);
  }
  return result;
}

