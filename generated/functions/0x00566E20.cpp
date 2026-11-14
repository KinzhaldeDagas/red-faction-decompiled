// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566E20 rf_model_handle88_pool_release_raw
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Unconditionally pushes handle on free list by writing prior head to DWORD0, increments freeCount88012,decrements active88024,returns descriptor. No tag/object destruction, range/double-release/ownership validation or heap delete. High-level563F70 must release owned contents first.
_DWORD *__thiscall rf_model_handle88_pool_release_raw(_DWORD *this, _DWORD *a2)
{
  *a2 = *(this + 22000);
  *(this + 22000) = a2;
  ++*(this + 22003);
  --*(this + 22006);
  return this;
}

