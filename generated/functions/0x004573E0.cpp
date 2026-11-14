// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004573E0 rf_save_list_b_ensure_selected_row_visible
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Signed selectedDWORD6F23EC<offsetDWORD6F23E8 sets offset=selected. Otherwise if signed selected>=wrapped(offset+visibleDWORD6F23C8), sets
// offset=wrapped(selected-visible+1); other case leaves offset. No count/selected/nonnegative validation. ALWAYS compute signed offset / signed wrapped(LIVE array6F26AC
// count-visible) via x87: numerator stored DOUBLE64, denominator FILD, FDIVR, result storedFLOAT32 and passed to4719F0 on slider6F2910. Unlike scroll-button helpers, NO
// count==visible zero-denominator guard; zero/negative range reaches x87 directly and setter policy remains delegated. No own sound, edit update, mode-byte clear or normalized
// result; row position changes precede conversion/division.
void rf_save_list_b_ensure_selected_row_visible()
{
  float v0; // [esp+4h] [ebp-10h]
  double v1; // [esp+Ch] [ebp-8h]

  if ( dword_6F23EC >= dword_6F23E8 )
  {
    if ( dword_6F23EC >= unk_6F23C8 + dword_6F23E8 )
      dword_6F23E8 = dword_6F23EC - unk_6F23C8 + 1;
  }
  else
  {
    dword_6F23E8 = dword_6F23EC;
  }
  v1 = (double)dword_6F23E8;
  v0 = v1 / (double)(rf_receiver_get_first_dword(dword_6F26AC) - unk_6F23C8);
  rf_ui_slider_set_value_clamped(unk_6F2910, v0);
}

