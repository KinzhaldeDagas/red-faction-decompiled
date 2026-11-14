// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580620 rf_volume_system_clear
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Deletes every owned volume pointer,then releases owned and borrowed active pointer-array backing exactly as atexit cleanup. No per-volume destructor or active-entry double delete. Nominal EAX from final release is incidental,not a success predicate;existing return type retained.
void **rf_volume_system_clear()
{
  void **v0; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_18CCFF4); ++i )
  {
    v0 = (void **)sub_552200(unk_18CCFF4, i);
    operator delete(*v0);
  }
  rf_pointer_array_release_storage((void **)unk_18CCFF4);
  return rf_pointer_array_release_storage((void **)unk_18CD030);
}

