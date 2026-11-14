// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046BA70 rf_gameplay_priority_move_selected_up
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Noarg. Only signed selected6F7B88>0:swap playerDWORD4436+4*selected with previousDWORD4432+4*selected;decrement selected AFTER both stores. No
// selected<32/count or playerNULL check. ALWAYS ensure selected visible46BAF0 even no swap atlimit. Mutates actual player priority array,not a UI copy;no weapon
// eligibility/type/swap-result check,sound or save. Keyboard caller may pass ignored(-1,-1).
void rf_gameplay_priority_move_selected_up()
{
  int v0; // [esp+4h] [ebp-4h]

  if ( unk_6F7B88 > 0 )
  {
    v0 = *(_DWORD *)(rf_local_fpgun_player + 4 * unk_6F7B88 + 4436);
    *(_DWORD *)(rf_local_fpgun_player + 4 * unk_6F7B88 + 4436) = *(_DWORD *)(rf_local_fpgun_player
                                                                           + 4 * unk_6F7B88
                                                                           + 4432);
    *(_DWORD *)(rf_local_fpgun_player + 4 * unk_6F7B88-- + 4432) = v0;
  }
  rf_gameplay_priority_ensure_selected_visible();
}

