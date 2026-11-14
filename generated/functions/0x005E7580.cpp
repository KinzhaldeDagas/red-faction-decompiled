// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7580 rf_byte_arena_initialize_owned_chunks
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Recovered thiscall(capacityBytes,growByte). Sets GROW02 according to growByte!=0 while preserving other flags,stores capacity12,sets OWN01,then prepends chunk5E7520. Returns0 success,1 if prepend helper nonzero. Does not first release old chain/reset head or clear lastAllocation;existing chunks remain linked on success. Failure leaves requested capacity/OWN/GROW changes committed and previous pointers/cursor unchanged. No capacity/overflow guard or payload zero-fill.
int __thiscall rf_byte_arena_initialize_owned_chunks(void *this, unsigned int a2, unsigned __int8 a3)
{
  *((_DWORD *)this + 6) = (2 * (a3 != 0)) | *((_DWORD *)this + 6) & 0xFFFFFFFD;
  *((_DWORD *)this + 3) = a2;
  *((_DWORD *)this + 6) |= 1u;
  return rf_byte_arena_prepend_chunk(this) != 0;
}

