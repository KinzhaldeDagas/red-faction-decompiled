// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004117A0 rf_camera_find_free_player_slot
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): No arguments, no writes. Fixed SIGNED loop i=0,1 returns first index whose owner-player DWORD666AA4+12*i equals0; returns full
// EAX-1 if neither free. Does not test camera pointer or state and does not reclaim a slot whose owner remains nonnull after camera cleanup.
int rf_camera_find_free_player_slot()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 2; ++i )
  {
    if ( !unk_666AA4[3 * i] )
      return i;
  }
  return -1;
}

