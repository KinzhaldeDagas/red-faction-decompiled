// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00467360 rf_intro_panel_initialize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser reply and host/options/intro UI call chains, original switch/literal data, native float predicates and
// callback ownership/ABI): Noarg,panel4 initializer from verified compiled UI dispatcher4F0DD4. Original PE body plays intro.bik blocking,then
// game_initialization_notice_and_clear_level_cache. Constructs owned8-byte empty RFString on stack,then owned8-byte copy of configured level RFString6FC308;calls
// level_transition_assign_level_and_save_strings with TWO by-value RFStrings/TOTAL16 native bytes (level first,empty save string second),caller cleans16. Then request UI panel5
// immediately with(5,0). SEH destroys constructed temporary on unwind;native ownership/cleanup retained. No own movie-result/level-path validation or rollback. Previous
// Concurrency::details::SchedulerBase::StaticDestruction name/FUNC_LIB were false SDK recognition:game-specific intro literal,RFString/level delegates and panel4 dispatcher establish
// application code. Corrected name and library flag only;boundaries,prototype and bytes retained.
void __cdecl rf_intro_panel_initialize()
{
  int v0; // eax
  int v1[2]; // [esp-10h] [ebp-34h] BYREF
  int v2[5]; // [esp-8h] [ebp-2Ch] BYREF
  _DWORD *v3; // [esp+Ch] [ebp-18h]
  int *v4; // [esp+10h] [ebp-14h]
  void *v5; // [esp+14h] [ebp-10h]
  int v6; // [esp+20h] [ebp-4h]

  rf_movie_play_bink_blocking("intro.bik");
  rf_game_initialization_notice_and_clear_level_cache();
  v5 = v2;
  v3 = rf_string_construct_from_cstr(v2, (char *)byte_6370CA);
  v2[4] = (int)v3;
  v6 = 0;
  v4 = v1;
  rf_string_copy_construct_from_object(v1, (char **)dword_6FC308);
  v2[3] = v0;
  v6 = -1;
  rf_level_transition_assign_level_and_save_strings(v1[0], (char *)v1[1], v2[0], (char *)v2[1]);
  rf_ui_request_panel_immediate(5, 0);
}

