// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561830 rf_text_log_buffer_get_data
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): False generic runtime label:returns record DWORD0 buffer pointer bits. Does not copy, allocate, validate ownership, terminate or use count/capacity.
int __thiscall rf_text_log_buffer_get_data(void *this)
{
  return *(_DWORD *)this;
}

