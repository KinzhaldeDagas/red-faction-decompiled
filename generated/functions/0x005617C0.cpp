// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005617C0 rf_text_log_buffer_destroy_storage
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): If buffer0 nonnull AND external byte4==0, operator-deletes buffer; external storage not freed. Does not clear buffer, capacity, counts or record fields, and does not free record object. Repeated destroy on same owned record can double-free.
void __thiscall rf_text_log_buffer_destroy_storage(int this)
{
  if ( *(_DWORD *)this )
  {
    if ( !*(_BYTE *)(this + 4) )
      operator delete(*(void **)this);
  }
}

