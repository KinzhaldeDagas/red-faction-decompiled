// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536290 rf_geomod_face_pool_take_peak_and_reset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Thiscall pool plainRET. ReadDWORD at byte2880020(0x2BF214) tolocal, replace it with CURRENT activeDWORD2880024(0x2BF218), return old peakEAX. No free-list walk, memory allocation, counter decrement or current-count-only semantics. Field is active high-water since prior query, including inline and spill records.
int __thiscall rf_geomod_face_pool_take_peak_and_reset(_DWORD *this)
{
  int v2; // [esp+4h] [ebp-4h]

  v2 = *(this + 720005);
  *(this + 720005) = *(this + 720006);
  return v2;
}

