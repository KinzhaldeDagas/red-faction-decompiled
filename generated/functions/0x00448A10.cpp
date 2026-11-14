// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448A10 rf_multiplayer_tick_transfer_and_admitted_level_update
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Native no-argument entry, void/incidental registers; incoming ECX is not semantically consumed (PUSH ECX only reserves local
// storage). First call48F000 session tick regardless current runtime flag. Then reread runtime BYTE704E81: zero exits; ANYnonzero calls597840 service-all-file-transfer-slots. Seed
// local blockedBYTE0, then reread runtime; only EXACT1 with authority BYTE704E82==0 dereferences GLOBAL local-player87C318->DWORD4608->DWORD8 mask0x20 and sets blocked1 if mask set.
// No local-player/nested NULL guard on that branch. Runtime other nonzero values skip the client mask test. After transfers/client test, call446190 CURRENT panel-ID getter;
// panelID==EXACT11 exits, then blockedANYnonzero exits. Otherwise477BD0 level-state-bit0 query must return EXACTAL1 before444D30 level update; other nonzero bytes reject. Delegate
// level update has its own pause/client gates. Runtime, authority and player state are not snapshotted before session/transfer callbacks; blocked result is captured before
// panel/level queries. No own unconditional level tick, pause-depth operation, aggregate success result or rollback.
void __cdecl rf_multiplayer_tick_transfer_and_admitted_level_update()
{
  bool v0; // [esp+1h] [ebp-1h]

  rf_multiplayer_session_tick_if_enabled();
  if ( rf_multiplayer_runtime_mode )
  {
    rf_file_transfer_service_all_slots();
    v0 = 0;
    if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
      v0 = (*(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) & 0x20) != 0;
    if ( rf_ui_panel_stack_current_id() != 11 && !v0 && rf_level_state_bit0_is_set() )
      sub_444D30();
  }
}

