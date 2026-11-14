// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417D50 rf_monitor_get_selected_entity_identifier
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Return registered monitor selected entity identifier+0x10, or-1 when no registered record. Does not resolve or validate selected entity.
int __cdecl rf_monitor_get_selected_entity_identifier(int a1)
{
  int *record; // [esp+0h] [ebp-4h]

  record = rf_monitor_find_record(a1);
  if ( record )
    return record[4];
  else
    return -1;
}

