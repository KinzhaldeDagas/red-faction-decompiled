// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00533FC0 rf_geomod_plane_classes_differ_excluding_coplanar
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Cdecl two signed DWORD class values, no stack pop. Returns normalized AL1 iff a!=2 AND b!=2 AND a!=b; otherwise AL0. No validation restricts inputs to1/2/3: arbitrary differing values except2 also return true. No pointers or memory writes. Caller5339B0 uses this to select plane-side changes while separately admitting current class2 vertices.
bool __cdecl rf_geomod_plane_classes_differ_excluding_coplanar(int a1, int a2)
{
  return a1 != 2 && a2 != 2 && a1 != a2;
}

