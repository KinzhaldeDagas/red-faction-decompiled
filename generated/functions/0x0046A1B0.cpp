// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046A1B0 rf_ui_performance_gamma_slider_changed
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Cdecl(x,y). Update continuous slider6F6CA0 from pointer,read x87ST0 and store binary32 rf_graphics_gamma. Reload stored gamma,multiply original
// binary64 constant100.0,and ftol2_sse truncTowardZero into rf_graphics_gamma_percent (no additional binary32 product rounding). Pass storedFLOAT gamma as one native32-bit stack word
// to rf_graphics_gamma_set,cleanup4. No own player,finite,range or input/pane admission,custom-preset update,sound or file save;slider/setter own policies. Existing
// type/name/repeatable note retained;EAX gamma-set delegate residue.
int __cdecl rf_ui_performance_gamma_slider_changed(int a1, int a2)
{
  rf_ui_slider_update_value_from_pointer((int)flt_6F6CA0, a1, a2);
  rf_graphics_gamma = rf_ui_slider_value_get(flt_6F6CA0);
  rf_graphics_gamma_percent = (int)(rf_graphics_gamma * 100.0);
  return rf_graphics_gamma_set(rf_graphics_gamma);
}

