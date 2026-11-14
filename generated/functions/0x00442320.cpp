// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442320 rf_gated_singleplayer_camera3
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No arguments. Require DWORD1809818 ANY nonzero, multiplayer BYTE704E81 EXACT0 and local player87C318 nonNULL.
// Pass DWORD[player+196] directly as slot pointer to412170 and forward raw delegate EAX/AL. Third-person delegate resolves player entity and has distinct prior-state2
// relative-transform versus default-offset paths; wrapper adds no entity/slot/camera/split check. DWORD-gate failure leaves incoming EAX untouched; MP rejection returns zero-extended
// raw MP byte; MP0 with NULL player returns EAX0. Only delegate actual calls have its canonical AL0/1 contract.
char rf_gated_singleplayer_camera3()
{
  char result; // al

  if ( dword_1809818 )
  {
    result = rf_multiplayer_runtime_mode;
    if ( !rf_multiplayer_runtime_mode )
    {
      if ( rf_local_fpgun_player )
        return rf_camera_slot_enter_third_person(*(int **)(rf_local_fpgun_player + 196));
    }
  }
  return result;
}

