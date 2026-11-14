// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005580E0 rf_geomod_vertex_pool_release_raw
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Unconditionally pushes released44-byte record onto pool free list using DWORD0, increments control freeCount2200012 and decrements currentActive2200024. No incidence-array cleanup, range/ownership/double-free checks or heap deletion; higher-level557FC0 must release incidence storage first. Returns descriptor.
_DWORD *__thiscall rf_geomod_vertex_pool_release_raw(_DWORD *this, _DWORD *a2)
{
  *a2 = *(this + 550000);
  *(this + 550000) = a2;
  ++*(this + 550003);
  --*(this + 550006);
  return this;
}

