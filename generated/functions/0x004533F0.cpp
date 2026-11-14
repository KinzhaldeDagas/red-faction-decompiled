// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004533F0 rf_credits_mouse_press_request_fade_out
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Query58ACF0(button0) press-count predicate once, ZERO-EXTEND returned AL intoEAX.
// ANYnonzero byte stores exitDWORD6F1504=1 then fade-outBYTE6EFEB0=1; AL0 leaves both unchanged. Return that zero-extended byte, not either stored flag. Predicate does not
// consume/reset press count. No fade-in gate, so mouse can set fade-out while fade-in remains1; unlike453280 there is no intro suppression. No timer/pause/panel request or rollback.
BOOL rf_credits_mouse_press_request_fade_out()
{
  BOOL result; // eax

  result = rf_mouse_button_has_press_count(0);
  if ( result )
  {
    unk_6F1504 = 1;
    unk_6EFEB0 = 1;
  }
  return result;
}

