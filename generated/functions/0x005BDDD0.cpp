// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BDDD0 rf_scene_pool_counters_construct_zero
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Clears ten consecutive DWORDs at receiver offsets0..36,returns receiver. Called on scene loader pool-context block. No allocation,destruction or initialization beyond40 bytes; precise original C++ type name unproven.
_DWORD *__thiscall rf_scene_pool_counters_construct_zero(_DWORD *this)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  return this;
}

