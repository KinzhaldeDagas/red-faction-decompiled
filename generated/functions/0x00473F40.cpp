// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00473F40 rf_object_respawn_update_authority
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): No arguments. Skips ONLY when runtimeBYTE==EXACT1 AND authorityBYTE==0; any nonzero authority passes. Calls
// performance_clock_elapsed_scaled(1000), subtracts DWORD6F9120 and requires SIGNED difference>=100. Does NOT update6F9120 itself, so this body is not a self-rearming100ms throttle.
// Walks item list6FB1C4 to sentinel6FAF38 via nextDWORD+652 read after work. Requires inactive predicate AL EXACT1 AND elapsed game-clock deadline at object+688 AL EXACT1,
// then473EF0(object). No object creation, separate disarm/reset, network broadcast or overflow/invalid-pointer recovery here. Existing saved char return type is incidental register
// residue.
void rf_object_respawn_update_authority()
{
  int i; // [esp+0h] [ebp-8h]

  if ( (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority)
    && rf_performance_clock_elapsed_scaled(1000) - unk_6F9120 >= 100 )
  {
    for ( i = unk_6FB1C4; (_UNKNOWN *)i != &unk_6FAF38; i = *(_DWORD *)(i + 652) )
    {
      if ( rf_object_has_respawn_inactive_flag(i) && rf_replicator_has_elapsed((int *)(i + 688)) )
        rf_object_respawn_apply(i);
    }
  }
}

