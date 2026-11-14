// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442260 rf_gated_singleplayer_dispatch_player_movement_action
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No arguments. Require DWORD1809818 ANY nonzero, multiplayer BYTE704E81 EXACT0 and local-player pointer87C318
// nonNULL; then call4E04F0(player) and forward its raw EAX/AL. Native wrapper adds no movement-state, ENTITY-resolution, action-availability or split-mode gate. Rejected
// DWORD1809818==0 path never writes EAX and preserves incoming incidental EAX; after admitted DWORD gate, MP rejection returns zero-extended raw MP byte, and NULL-player with MP0
// returns EAX0. Delegate result is not normalized, and neither full EAX nor AL is a uniform success indication.
char rf_gated_singleplayer_dispatch_player_movement_action()
{
  char result; // al

  if ( dword_1809818 )
  {
    result = rf_multiplayer_runtime_mode;
    if ( !rf_multiplayer_runtime_mode )
    {
      if ( rf_local_fpgun_player )
        return rf_player_dispatch_movement_state_action(rf_local_fpgun_player);
    }
  }
  return result;
}

