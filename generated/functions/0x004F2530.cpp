// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F2530 rf_application_cleanup_before_backend_shutdown
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): No-argument void cleanup wrapper; corrected inherited thiscall receiver and incidental char result. Sole caller4F1D90 supplies no stack/ECX receiver and next call4F1EC0 overwrites EAX without testing it. Native wrapper itself does not read incoming ECX or stack arguments. Ordered calls: multiplayer-runtime teardown48ED40,prepare-menu-without-session,4BCAC0,45A1E0,48DC70,4A63F0,reserved no-op4F2580,world-decal pool abandon,procedural-bitmap system clear; if global local-player pointer nonzero,4E59C0(player). Saved receiver on first delegate is an independent decompiler inference, not a verified public argument of this wrapper. Renderer/audio/window destruction follows
// separately in4F1EC0. No own global-player pointer clearing or return-based failure handling.
void __cdecl rf_application_cleanup_before_backend_shutdown()
{
  rf_multiplayer_runtime_teardown();
  rf_prepare_multiplayer_menu_without_session();
  rf_object_pool_delete_all_when_gate_set();
  rf_ui_clear_owned_string_6F2C78();
  rf_multiplayer_process_shutdown_banlist();
  rf_multiplayer_log_close();
  rf_application_cleanup_reserved_noop();
  rf_world_decal_pool_abandon_lists();
  rf_procedural_bitmap_system_clear();
  if ( rf_local_fpgun_player )
    rf_player_save_configuration_file(rf_local_fpgun_player);
}

