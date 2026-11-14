// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00418160 rf_monitor_invalidate_rendered_flag
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Find registered monitor by exact identifier via rf_monitor_find_record. If found, clear flags+0x38 bit4 only; absent monitor is no-op. Leaves mode, selected id, target vector, bitmap and deadline intact; subsequent admitted rendering owns refresh.
int *__cdecl rf_monitor_invalidate_rendered_flag(int a1)
{
  int *result; // eax

  result = rf_monitor_find_record(a1);
  if ( result )
    result[14] &= ~4u;
  return result;
}

