// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00418200 rf_monitor_construct_record
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Construct vector at record+0x18 with argument0, then Replicator deadline+0x24. No explicit initialization of list links, mode, identifiers, bitmap, interval, dimensions or flags here; creation0x417A60 supplies those fields separately.
int *__thiscall rf_monitor_construct_record(int *this)
{
  rf_dword_array_construct_capacity(this + 6, 0);
  rf_timestamp4_construct_invalid(this + 9);
  return this;
}

