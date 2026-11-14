// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448150 rf_game_initialization_notice_and_clear_level_cache
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Noarg. If globalBYTE6EDD3D EXACT1 call prepare_multiplayer_menu_without_session delegate. Regardless print exact -- Game Initializing -- newline via
// console text helper, set BYTE6EDD3D=1, call level_state_cache_clear and return delegate EAX. Other nonzero initial byte values skip first cleanup. No own mode/session/error gate,
// actual level-file parse or panel request; initialization marker set before cache clear.
void *rf_game_initialization_notice_and_clear_level_cache()
{
  if ( unk_6EDD3D == 1 )
    rf_prepare_multiplayer_menu_without_session();
  rf_console_output_append_text_lines("-- Game Initializing --\n", nullptr);
  unk_6EDD3D = 1;
  return rf_level_state_cache_clear();
}

