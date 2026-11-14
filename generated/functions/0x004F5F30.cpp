// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F5F30 rf_snapshot_unpack_replicator_remaining
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Input dword==-1 resets destination Replicator; all other signed values passed unchanged to rf_replicator_arm_milliseconds as offset from current wrapped clock. Does not clamp overdue negative offsets or restore an absolute saved-clock value.
_DWORD *__cdecl rf_snapshot_unpack_replicator_remaining(int *a1, int *a2)
{
  if ( *a2 == -1 )
    return rf_replicator_reset(a1);
  else
    return (_DWORD *)rf_replicator_arm_milliseconds(a1, *a2);
}

