// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CA800 rf_face_next_spatial_node_link
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): stdcall(face), RET4. Returns DWORD Face88, the intrusive next link used by spatial node face lists. Does not inspect owner72 or room next92; no null guard.
int __stdcall rf_face_next_spatial_node_link(int a1)
{
  return *(_DWORD *)(a1 + 88);
}

