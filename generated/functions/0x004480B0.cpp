// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004480B0 rf_prepare_multiplayer_menu_without_session
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. BYTE6EDD3D==0 returns immediately with zero-extended EAX0. Any nonzero value destroys level runtime resources;
// then re-reads split-screen byte and, if ANY nonzero, clears it BEFORE calling4E1B00(raw local-player entry0,viewportMode0), with no player-count/null guard. Re-reads multiplayer
// mode and tears it down if ANY nonzero. Finally clears6EDD3D and stops all gamesound voice slots through568650, forwarding its incidental EAX. No unconditional teardown on zero gate
// and no own panel request, menu construction or status normalization.
void rf_prepare_multiplayer_menu_without_session()
{
  if ( unk_6EDD3D )
  {
    rf_level_destroy_runtime_resources();
    if ( rf_splitscreen_runtime_active )
    {
      rf_splitscreen_runtime_active = 0;
      rf_player_viewport_mode_set(rf_local_player_entries[0], 0);
    }
    if ( rf_multiplayer_runtime_mode )
      rf_multiplayer_runtime_teardown();
    unk_6EDD3D = 0;
    rf_gamesound_stop_all_voice_slots();
  }
}

