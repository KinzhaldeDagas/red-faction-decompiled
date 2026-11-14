// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004541D0 rf_extras_menu_close_and_clear_active
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Call453C10 to set closing X velocities/playevent48, THEN overwrite
// activeBYTE6F1DA8=0; forward delegateEAX unchanged. No own initialized-latch reset, forced position/clamp, close-ready wait, stack commit or callback rollback. Active replacement
// made during sound delegate is overwritten after it returns.
int rf_extras_menu_close_and_clear_active()
{
  int result; // eax

  result = rf_extras_menu_begin_close();
  unk_6F1DA8 = 0;
  return result;
}

