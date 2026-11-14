// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7440 rf_byte_arena_construct_partial_empty
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Recovered thiscall header constructor. Writes data4=0,head0=0,lastAllocation20=0;clears OWN flagbit01 and GROW bit02 at24 preserving other bits. Does NOT initialize cursor8,capacity12 or remaining16,and does not zero whole28-byte header. Returns receiver;no allocation/free. Must configure owned or attached storage before normal use.
void *__thiscall rf_byte_arena_construct_partial_empty(void *this)
{
  *((_DWORD *)this + 1) = 0;
  *((_DWORD *)this + 6) &= ~1u;
  *((_DWORD *)this + 6) &= ~2u;
  *(_DWORD *)this = 0;
  *((_DWORD *)this + 5) = 0;
  return this;
}

