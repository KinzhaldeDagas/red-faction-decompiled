// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00455160 rf_save_list_a_ensure_selected_row_visible
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Signed selectedDWORD6F1FA0<offsetDWORD6F1F9C sets offset=selected. Otherwise if signed selected>=wrapped(offset+visibleDWORD6F1F80), sets
// offset=wrapped(selected-visible+1); other case leaves offset. No count/selected/nonnegative validation. ALWAYS compute signed offset / signed wrapped(LIVE array6F21AC
// count-visible) via x87: numerator stored DOUBLE64, denominator FILD, FDIVR, result storedFLOAT32 and passed to4719F0 on slider6F2200. Unlike scroll-button helpers, NO
// count==visible zero-denominator guard; zero/negative range reaches x87 directly and setter policy remains delegated. No own sound, edit update, mode-byte clear or normalized
// result; row position changes precede conversion/division.
void rf_save_list_a_ensure_selected_row_visible()
{
  float v0; // [esp+4h] [ebp-10h]
  double v1; // [esp+Ch] [ebp-8h]

  if ( dword_6F1FA0 >= dword_6F1F9C )
  {
    if ( dword_6F1FA0 >= unk_6F1F80 + dword_6F1F9C )
      dword_6F1F9C = dword_6F1FA0 - unk_6F1F80 + 1;
  }
  else
  {
    dword_6F1F9C = dword_6F1FA0;
  }
  v1 = (double)dword_6F1F9C;
  v0 = v1 / (double)(rf_receiver_get_first_dword(dword_6F21AC) - unk_6F1F80);
  rf_ui_slider_set_value_clamped(unk_6F2200, v0);
}

