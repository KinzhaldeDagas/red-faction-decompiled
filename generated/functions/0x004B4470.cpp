// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4470 rf_player_runtime_list_count
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): Noargs,returns signed32 count of nodes reachable from head87C324. NULLhead ->0. Counts currentnode,reads nextDWORD0;setsnextNULL if next==ORIGINAL globalhead,otherwise continuesnext. Supports NULL-terminated or head-circular lists,not sentinel-first convention. No list-integrity/cycle/overflow guard;cycles not returning to globalhead can loop indefinitely. Does not use local player-entry array/count or mutate list.
int rf_player_runtime_list_count()
{
  _DWORD *v1; // [esp+0h] [ebp-Ch]
  _DWORD *i; // [esp+4h] [ebp-8h]
  int v3; // [esp+8h] [ebp-4h]

  v3 = 0;
  for ( i = (_DWORD *)dword_87C324; i; i = v1 )
  {
    ++v3;
    if ( *i == dword_87C324 )
      v1 = nullptr;
    else
      v1 = (_DWORD *)*i;
  }
  return v3;
}

