// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453C10 rf_extras_menu_begin_close
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. FILD signed width6F1E94, multiply PE FLOAT661E40=-4.0, round/store button X
// velocity6F1DB4. Load FLOAT661E60=-2048.0, FCHS and store titlebar X velocity6F1DBC (normally+2048.0). Then568050(event48,group0,FLOAT0,FLOAT1) and forwardEAX. No own
// active/initialized flag clear, position clamp or readiness test;4541D0 clears active AFTER this callback. Mutable signed width and floating environment retain native arithmetic.
int rf_extras_menu_begin_close()
{
  unk_6F1DB4 = (double)unk_6F1E94 * rf_main_menu_close_x_speed_scale;
  unk_6F1DBC = -flt_661E60;
  return rf_gamesound_play_event(48, 0, 0.0, 1.0);
}

