// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E75E0 rf_byte_arena_attach_borrowed_storage
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Recovered thiscall(buffer,capacityBytes). Stores data4=buffer,capacity12=input,clears OWN01 and GROW02,then resets cursor todata/alignment/remaining through5E7630. Does not free former owned chunks,clear head0 or lastAllocation20. If bufferNULL,reset helper does nothing,leaving old cursor8/remaining16. Return inherited from helper,mixed receiver/remaining bits rather than uniform status. Borrowed storage is never freed by release helper.
unsigned int __thiscall rf_byte_arena_attach_borrowed_storage(void *this, void *a2, unsigned int a3)
{
  *((_DWORD *)this + 1) = a2;
  *((_DWORD *)this + 3) = a3;
  *((_DWORD *)this + 6) &= ~1u;
  *((_DWORD *)this + 6) &= ~2u;
  return rf_byte_arena_reset_current_chunk_cursor(this);
}

