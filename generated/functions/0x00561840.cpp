// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561840 rf_text_log_buffer_get_used_length
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): False generic runtime label:returns DWORD record12, the stored used-length count. Does not call strlen or validate against actual buffer contents.
int __thiscall rf_text_log_buffer_get_used_length(_DWORD *this)
{
  return *(this + 3);
}

