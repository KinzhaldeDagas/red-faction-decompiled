// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530710 rf_geomod_corner_allocate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): No args, forward global corner-pool descriptor ECX to5362C0, return raw28-byte corner orNULL. No payload/ring/vertex initialization or failure conversion; caller530E20 immediately dereferences result. Pool handles free/spill and active/high-water counters.
_DWORD *rf_geomod_corner_allocate()
{
  return rf_geomod_corner_pool_allocate_raw(rf_geomod_corner_pool_descriptor);
}

