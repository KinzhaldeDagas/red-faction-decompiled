// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005530B0 rf_solid_clear_selection204_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Sets count of solid pointer-array+204 to0,returns member header pointer. Retains capacity/backing/elements. Collection role not conclusively identified by this body;do not infer face/vertex ownership or deletion.
_DWORD *__thiscall rf_solid_clear_selection204_count(_DWORD *this)
{
  return rf_pointer_array_clear_count_keep_storage(this + 51);
}

