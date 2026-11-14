// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004422E0 rf_gated_singleplayer_camera2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No arguments. Require DWORD1809818 ANY nonzero, multiplayer BYTE704E81 EXACT0, local player87C318 nonNULL.
// Pass DWORD[player+196] directly as slot pointer to411FA0 and forward delegate EAX/AL. Delegate enters state2 and only attempts detach for SIGNED nonnegative camera handle512;
// negative handles are preserved by that verified helper. No wrapper slot/camera/player-entity/split validation. DWORD-gate failure leaves incoming EAX untouched; MP rejection
// returns zero-extended raw MP byte; MP0 with NULL player returns EAX0. Helper AL1 on every normal call does not make wrapper rejection returns a coherent success flag.
char rf_gated_singleplayer_camera2()
{
  char result; // al

  if ( dword_1809818 )
  {
    result = rf_multiplayer_runtime_mode;
    if ( !rf_multiplayer_runtime_mode )
    {
      if ( rf_local_fpgun_player )
        return rf_camera_slot_enter_state2_and_detach_nonnegative_handle(*(int **)(rf_local_fpgun_player + 196));
    }
  }
  return result;
}

