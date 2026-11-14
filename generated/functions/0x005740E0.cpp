// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005740E0 rf_bitmap_manager_release_active_storage
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Repeatedly takes active-list head0x1897434 until sentinel0x18973E0, force-releases CPU pixels via0x5741B0(handle,1), then recycles handle0x5781E0. Clears byte0x189744F. Deletes and nulls global bitmap-record array0x1897344, hash pointer table0x189734C, and allocation pointer0x1897450. Does not itself walk renderer GPU caches or animated-entry storage; other lifecycle owners must handle those. Assumes list and stored handles consistent; repeated head relies on recycle removing current record.
void __cdecl rf_bitmap_manager_release_active_storage()
{
  int i; // [esp+Ch] [ebp-4h]

  for ( i = dword_1897434; (_UNKNOWN *)i != &unk_18973E0; i = dword_1897434 )
  {
    rf_bitmap_release_cpu_pixels_force_or_reference(*(_DWORD *)(i + 36), 1);
    rf_bitmap_handle_recycle_slot_or_animation_entry(*(_DWORD *)(i + 36));
  }
  unk_189744F = 0;
  if ( dword_1897344 )
  {
    operator delete((void *)dword_1897344);
    dword_1897344 = 0;
  }
  if ( dword_189734C )
  {
    operator delete(dword_189734C);
    dword_189734C = nullptr;
  }
  if ( MEMORY[0x1897450] )
  {
    operator delete(MEMORY[0x1897450]);
    MEMORY[0x1897450] = nullptr;
  }
}

