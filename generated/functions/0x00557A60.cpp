// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557A60 rf_geomod_spatial_node_pool_release_raw
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Unconditionally writes previous freeHead into released node DWORD0, makes it new freeHead, increments freeCount and decrements currentActive. No pointer/range/double-free/ownership checks, object destructor, or heap deletion. Heap spill nodes are retained for reuse; returns descriptor.
_DWORD *__thiscall rf_geomod_spatial_node_pool_release_raw(_DWORD *this, _DWORD *a2)
{
  *a2 = *(this + 50000);
  *(this + 50000) = a2;
  ++*(this + 50003);
  --*(this + 50006);
  return this;
}

