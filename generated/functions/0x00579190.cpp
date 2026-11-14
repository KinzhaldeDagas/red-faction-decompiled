// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00579190 rf_memory_text_parser_close_buffer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): ECX receiver. If buffer DWORD0 nonNULL AND global mapped-cache pointer189745C==0,calls free(buffer). If global nonzero skips free for EVERY buffer,without checking whether pointer belongs to cache. Always clears buffer0 and returns receiver. Leaves current cursor4,filename,field264,size268 unchanged;cursor can become stale. Open578EA0 currently forces own malloc path even with global cache present,so closing that path while cache-global nonzero leaks allocation. No object deletion,buffer-range/ownership/refcount validation or state reinitialization.
void **__thiscall rf_memory_text_parser_close_buffer(void **this)
{
  if ( *this && !unk_189745C )
    free(*this);
  *this = nullptr;
  return this;
}

