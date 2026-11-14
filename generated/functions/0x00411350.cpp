// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00411350 rf_camera_cleanup_two_slots_and_sample_arrays
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Atexit cleanup, no stack arguments. Fixed SIGNED i=0,1 traversal tests camera DWORD666AA0+12*i, not owner-player occupancy. For
// each nonnull record calls4124C0 with ECX=record and raw stack flags1: native destructor then operator delete when bit0 set; result ignored, then clears ONLY camera pointer DWORD0.
// Slot owner-player DWORD1 and numeric state DWORD2 are preserved. Clears selected-camera666A9C, releases matrix-array666AB8 storage, then vector-array666AD0 storage. Releases reset
// header count/capacity/base and free backing only; do not destroy elements. Shared sample index666A98 is not reset here. No callback-registration removal or rollback; a destructor
// exception interrupts later clearing/cleanup. Declared void, no meaningful success result.
void __cdecl rf_camera_cleanup_two_slots_and_sample_arrays()
{
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < 2; ++i )
  {
    if ( unk_666AA0[3 * i] )
    {
      rf_entity_scalar_deleting_destructor((void *)unk_666AA0[3 * i], 1);
      unk_666AA0[3 * i] = 0;
    }
  }
  unk_666A9C = 0;
  rf_pointer_array_release_storage((void **)&unk_666AB8);
  rf_pointer_array_release_storage((void **)&unk_666AD0);
}

