// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00496170 rf_face_next_room_link
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, spatial partitioning, strict/inclusive box tests, pool counters, portal registration and ABI verification): stdcall(face), RET4. Returns DWORD Face92, intrusive next link used for authored room face lists. Distinct from solid next84 and spatial-node next88; no null guard.
int __stdcall rf_face_next_room_link(int a1)
{
  return *(_DWORD *)(a1 + 92);
}

