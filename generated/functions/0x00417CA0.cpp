// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417CA0 rf_monitor_configure_record
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Lookup registered monitor by identifier through0x417D10; absent record is a no-op. Write raw mode dword+8 and interval float+0x28. Set flags+0x38 bit8 only when input byte equals1; false does not clear existing bit8. Finite interval<=0 is replaced by8.0seconds. Does not arm/reset interval timer, clear rendered bit4, change selected entity, or clear attachment vector.
void __cdecl rf_monitor_configure_record(int a1, int a2, char a3, float a4)
{
  int *record; // [esp+0h] [ebp-4h]

  record = rf_monitor_find_record(a1);
  if ( record )
  {
    record[2] = a2;
    *((float *)record + 10) = a4;
    if ( a3 == 1 )
      record[14] |= 8u;
    if ( *((float *)record + 10) <= 0.0 )
      *((float *)record + 10) = 8.0;
  }
}

