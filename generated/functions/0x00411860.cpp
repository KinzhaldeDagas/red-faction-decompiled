// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00411860 rf_camera_initialize_occupied_slots
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): No arguments, void. Fixed SIGNED i=0,1 loop calls4124A0(i) and accepts any nonzero AL. Occupancy means owner-player slotDWORD1
// nonzero, NOT camera pointer validity. For occupied slots passes address666AA0+12*i to4120D0, ignores its separate AL result and continues second slot even after ordinary false
// return. Delegate resolves player+20 as ENTITY; successful initialization writes camera+512 full handle and shown transforms/state0, false resolution leaves that delegate state
// unwritten. Wrapper has no additional camera/player/null validation, transaction or shared sample mutation.
void rf_camera_initialize_occupied_slots()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 2; ++i )
  {
    if ( rf_camera_slot_has_player_unchecked(i) )
      rf_camera_slot_enter_first_person(&unk_666AA0[3 * i]);
  }
}

