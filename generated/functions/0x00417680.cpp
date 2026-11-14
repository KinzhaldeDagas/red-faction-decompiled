// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417680 rf_monitor_unlink_and_destroy_record
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Unlink record using next+0/previous+4, then zero both links. If bitmap+0x14!=-1, call0x5781E0 to release it. Invoke deleting destructor0x4181B0(record,1). No identifier lookup, double-unlink guard or material bitmap restoration in this body.
void *__cdecl rf_monitor_unlink_and_destroy_record(void *a1)
{
  void *result; // eax

  **((_DWORD **)a1 + 1) = *(_DWORD *)a1;
  *(_DWORD *)(*(_DWORD *)a1 + 4) = *((_DWORD *)a1 + 1);
  *(_DWORD *)a1 = 0;
  *((_DWORD *)a1 + 1) = 0;
  if ( *((_DWORD *)a1 + 5) != -1 )
    rf_bitmap_handle_recycle_slot_or_animation_entry(*((_DWORD *)a1 + 5));
  result = a1;
  if ( a1 )
    return rf_monitor_record_scalar_deleting_destructor(a1, 1);
  return result;
}

