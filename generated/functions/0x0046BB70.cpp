// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046BB70 rf_gameplay_priority_move_selected_down
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Noarg. Only signed selected6F7B88<count6F7B7C-1:swap actual playerDWORD4436+4*selected with nextDWORD4440+4*selected;increment selected AFTER
// stores. NO selected>=0/physical32/playerNULL/weapon eligibility guard. ALWAYS ensure-visible46BAF0,even if no swap. No own sound/save;keyboard can pass ignored sentinel words.
void rf_gameplay_priority_move_selected_down()
{
  int v0; // [esp+4h] [ebp-4h]

  if ( unk_6F7B88 < unk_6F7B7C - 1 )
  {
    v0 = *(_DWORD *)(rf_local_fpgun_player + 4 * unk_6F7B88 + 4436);
    *(_DWORD *)(rf_local_fpgun_player + 4 * unk_6F7B88 + 4436) = *(_DWORD *)(rf_local_fpgun_player
                                                                           + 4 * unk_6F7B88
                                                                           + 4440);
    *(_DWORD *)(rf_local_fpgun_player + 4 * unk_6F7B88++ + 4440) = v0;
  }
  rf_gameplay_priority_ensure_selected_visible();
}

