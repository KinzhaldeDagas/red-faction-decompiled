// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558140 rf_geomod_vertex_pool_take_peak_and_reset
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Returns old peakActive2200020 then replaces it with currentActive2200024. No free-list mutation or active-count change. Wrapper557F50 therefore consumes/reset peaks rather than reading current count.
int __thiscall rf_geomod_vertex_pool_take_peak_and_reset(_DWORD *this)
{
  int v2; // [esp+4h] [ebp-4h]

  v2 = *(this + 550005);
  *(this + 550005) = *(this + 550006);
  return v2;
}

