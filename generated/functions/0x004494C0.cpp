// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004494C0 rf_client_level_entry_initialize_and_request_panel5
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Noarg. Call448150 initialization notice/cache helper, then request UI panel5 force0; preserve panel delegate EAX. No runtime/authority, pending-panel
// or level-name validation here; initialization occurs before possible panel refusal and is not rolled back.
int rf_client_level_entry_initialize_and_request_panel5()
{
  rf_game_initialization_notice_and_clear_level_cache();
  return rf_ui_request_panel_immediate(5, 0);
}

