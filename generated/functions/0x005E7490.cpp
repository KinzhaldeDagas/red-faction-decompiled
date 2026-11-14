// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E7490 rf_byte_arena_destroy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Recovered thiscall destructor wrapper,forwards receiver inECX to5E74B0. Frees chunk chain only when OWN flag01 set;borrowed header untouched. Returns release-helper incidental DWORD,not a guaranteed receiver/status. No current-cursor/remaining/lastAllocation reset.
unsigned int __thiscall rf_byte_arena_destroy(void *this)
{
  return rf_byte_arena_release_owned_chunks(this);
}

