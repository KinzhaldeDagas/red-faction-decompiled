// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004917A0 rf_multiplayer_score_assets_initialize
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl no arguments. Clears BYTE757658,sets full-score logo/red flag/red microflag/blue flag/blue microflag bitmap handles all-1. Loads fonts bigfont.vf,rfpc-large.vf,rfpc-medium.vf
// each spacing override-1,stores handles75765C/757664/757BB0 in order. Returns last font-load result. No existing-font/bitmap release,failure rollback or bitmap file load in this
// body; repeated calls overwrite handles.
int rf_multiplayer_score_assets_initialize()
{
  int result; // eax

  unk_757658 = 0;
  rf_full_score_logo_bitmap = -1;
  rf_full_score_red_flag_bitmap = -1;
  rf_full_score_red_microflag_bitmap = -1;
  rf_full_score_blue_flag_bitmap = -1;
  rf_full_score_blue_microflag_bitmap = -1;
  unk_75765C = rf_font_load_with_spacing_override("bigfont.vf", -1);
  unk_757664 = rf_font_load_with_spacing_override("rfpc-large.vf", -1);
  result = rf_font_load_with_spacing_override("rfpc-medium.vf", -1);
  dword_757BB0 = result;
  return result;
}

