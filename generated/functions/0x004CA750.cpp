// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CA750 rf_glass_snapshot_restore_removed_geometry_ids
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Reset removal-ledger count0x8222F4=0, then for each saved id find current world geometry record via0x51E8A0(rf_world_solid,id). Only non-null record whose first byte accessor0x4CA7F0 is nonzero reaches0x4C74D0 to remove geometry and reappend id. Missing/zero-byte records are skipped. Does not restore dynamic glass-cell poses, reconstruct particle emitters.
void __cdecl rf_glass_snapshot_restore_removed_geometry_ids(int a1, int a2)
{
  _DWORD *geometry_record_by_saved_id; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  dword_8222F4 = 0;
  for ( i = 0; i < a2; ++i )
  {
    geometry_record_by_saved_id = (_DWORD *)rf_solid_find_geometry_record_by_saved_id(
                                              (_DWORD *)rf_world_solid,
                                              *(_DWORD *)(a1 + 4 * i));
    if ( geometry_record_by_saved_id )
    {
      if ( unknown_libname_11(geometry_record_by_saved_id) )
        rf_glass_remove_geometry_and_record_id(geometry_record_by_saved_id);
    }
  }
}

