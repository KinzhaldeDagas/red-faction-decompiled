// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00470270 rf_ui_modal_text_surface_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall(text,font), RET8. Measures strlen(text) into+56/+60; resets text origin+48=1/+52=0. Operates ONLY when EXISTING text bitmap+44 is
// signed>=0; does not create one from absent handle. Reads its actual dimensions. If measured width OR height exceeds existing dimensions, gets old bitmap format, recycles old
// handle, sets logical dimensions to max(measured,old) independently, creates same-format replacement and reads new dimensions. Does NOT shrink, add texture reference to replacement,
// or recheck new handle validity. Clears current bitmap and draws original text/font only when measured width>0. No own source/null/size guard, state gate or color change. Existing
// name and stored prototype retained; result register is incidental.
char *__thiscall rf_ui_modal_text_surface_initialize(int *this, char *a2, int a3)
{
  char *result; // eax
  int resolved_format_code; // [esp+14h] [ebp-Ch]
  int v6; // [esp+18h] [ebp-8h] BYREF
  int v7; // [esp+1Ch] [ebp-4h] BYREF

  rf_font_measure_text_extent(this + 14, this + 15, (unsigned __int8 *)a2, strlen(a2), a3);
  *(this + 12) = 1;
  *(this + 13) = 0;
  result = (char *)this;
  if ( *(this + 11) >= 0 )
  {
    rf_bitmap_get_resolved_dimensions(*(this + 11), &v6, &v7);
    if ( *(this + 14) > v6 || *(this + 15) > v7 )
    {
      resolved_format_code = rf_bitmap_get_resolved_format_code(*(this + 11));
      rf_bitmap_handle_recycle_slot_or_animation_entry(*(this + 11));
      *(this + 5) = rf_int_max(*(this + 14), v6);
      *(this + 6) = rf_int_max(*(this + 15), v7);
      *(this + 11) = rf_bitmap_create_user_bitmap(resolved_format_code, *(this + 5), *(this + 6));
      rf_bitmap_get_resolved_dimensions(*(this + 11), &v6, &v7);
    }
    rf_bitmap_clear_all_locked_texture_tile_bytes(*(this + 11));
    result = (char *)this;
    if ( *(this + 14) > 0 )
      return rf_font_draw_text_into_bitmap(*(this + 12), *(this + 13), *(this + 11), a2, a3);
  }
  return result;
}

