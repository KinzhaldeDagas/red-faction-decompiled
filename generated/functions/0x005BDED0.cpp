// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BDED0 rf_particle36_destroy_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): No-op particle36 destructor callback; no member/global writes or meaningful return. Used for construction unwind and particle array deleting destructor5BFDD0. Particle has no separately owned allocations.
void __thiscall rf_particle36_destroy_noop(void *this)
{
  ;
}

