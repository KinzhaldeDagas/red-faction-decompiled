// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F85D0 rf_named_source_cache_enable_and_clear_head
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Writes DWORD enabled0x1F67110=1 and head0x1F67114=NULL,returns0. Does not iterate/unlink/free prior circular-list entries;calling again loses head reference. Cache records use next136,prev140,name0,source string144 as shown by lookup and insertion0x5F88E0.
int rf_named_source_cache_enable_and_clear_head()
{
  unk_1F67110 = 1;
  unk_1F67114 = 0;
  return 0;
}

