// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502200 rf_goal_reset_shared_record_count
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Write shared table count0x90B050=0 only. Does not clear/free the64 string slots, zero their counts or inspect current registry. Subsequent lookup/pack scans use the new zero count.
void rf_goal_reset_shared_record_count()
{
  dword_90B050 = 0;
}

