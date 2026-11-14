// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005805C0 rf_volume_system_atexit_cleanup
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Loops owned count18CCFF4,operator-delete each stored volume pointer,then releases owned array and borrowed active array18CD030. No virtual/member destructor (volume members trivial/no-op). Releases active list without deleting borrowed entries again. Returns void.
void __cdecl rf_volume_system_atexit_cleanup()
{
  void **v0; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_18CCFF4); ++i )
  {
    v0 = (void **)sub_552200(unk_18CCFF4, i);
    operator delete(*v0);
  }
  rf_pointer_array_release_storage((void **)unk_18CCFF4);
  rf_pointer_array_release_storage((void **)unk_18CD030);
}

