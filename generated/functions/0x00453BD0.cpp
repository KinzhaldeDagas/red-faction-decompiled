// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453BD0 rf_extras_menu_begin_open
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. FILD signed widthDWORD6F1E94, multiply original PE FLOAT661E3C=4.0, round/store
// button X velocityFLOAT6F1DB4. Copy original FLOAT661E60=-2048.0 into titlebar X velocity6F1DBC. Then568050(event49,group0,FLOAT0,FLOAT1), forward its fullEAX residue. Both
// animations are HORIZONTAL X channels:453DC0 writes titlebar control+12 from6F1DB8 and button control+12 from6F1DB0. Does not change position, active/initialized flag, selection,
// clipping or input; no width-sign/finite/endpoint check or sound rollback.
int rf_extras_menu_begin_open()
{
  unk_6F1DB4 = (double)unk_6F1E94 * rf_main_menu_open_x_speed_scale;
  unk_6F1DBC = flt_661E60;
  return rf_gamesound_play_event(49, 0, 0.0, 1.0);
}

