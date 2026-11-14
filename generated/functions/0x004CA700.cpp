// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CA700 rf_glass_snapshot_collect_removed_geometry_ids
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Copy global glass geometry-removal ledger0x822310,count0x8222F4 into4-byte saved-id entries and export BYTE count. No shard transform/velocity state, particle emitter snapshot or geometry removal occurs here. Ledger is reset by rf_glass_shard_system_init and appended by0x4C74D0.
char __cdecl rf_glass_snapshot_collect_removed_geometry_ids(int a1, _BYTE *a2)
{
  char result; // al
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_8222F4; ++i )
    *(_DWORD *)(a1 + 4 * i) = unk_822310[i];
  result = dword_8222F4;
  *a2 = dword_8222F4;
  return result;
}

