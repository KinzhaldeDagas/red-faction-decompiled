// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00557AC0 rf_geomod_spatial_node_pool_take_peak_and_reset
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): Reads control peakActive at descriptor+200020, overwrites it with currentActive at200024, and returns old peak. Does not modify active/free/heap counts; two successive queries without intervening changes return current active on second.
int __thiscall rf_geomod_spatial_node_pool_take_peak_and_reset(_DWORD *this)
{
  int v2; // [esp+4h] [ebp-4h]

  v2 = *(this + 50005);
  *(this + 50005) = *(this + 50006);
  return v2;
}

