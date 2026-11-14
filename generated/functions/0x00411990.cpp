// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00411990 rf_camera_update_occupied_slots
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): No arguments, void. Fixed SIGNED i=0,1 loop calls4124A0(i); any nonzero AL (owner-player DWORD1 nonnull)
// invokes4119E0(address666AA0+12*i). Does not test camera pointer separately. Ignores each delegate EAX and always continues to next slot after ordinary return. No sample-index
// advance, slot-state writes or failure rollback in this wrapper.
void rf_camera_update_occupied_slots()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 2; ++i )
  {
    if ( rf_camera_slot_has_player_unchecked(i) )
      rf_camera_update_slot_by_numeric_state(&unk_666AA0[3 * i]);
  }
}

