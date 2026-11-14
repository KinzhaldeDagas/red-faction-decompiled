// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004422A0 rf_gated_singleplayer_camera1
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No arguments. DWORD1809818 must be ANY nonzero, multiplayer BYTE704E81 EXACT0, local player87C318 nonNULL.
// Pass DWORD[player+196] directly as camera SLOT pointer to4120D0 and forward raw delegate EAX/AL; no own slot/player-entity/camera validation or split restriction. Delegate resolves
// player entity and only on success copies first-person camera pose/state. DWORD-gate failure leaves incoming EAX untouched; MP rejection returns zero-extended raw MP byte; MP0 with
// NULL player returns EAX0. Successful delegate AL0/1 does not turn every wrapper exit into a canonical Boolean.
char rf_gated_singleplayer_camera1()
{
  char result; // al

  if ( dword_1809818 )
  {
    result = rf_multiplayer_runtime_mode;
    if ( !rf_multiplayer_runtime_mode )
    {
      if ( rf_local_fpgun_player )
        return rf_camera_slot_enter_first_person(*(float ***)(rf_local_fpgun_player + 196));
    }
  }
  return result;
}

