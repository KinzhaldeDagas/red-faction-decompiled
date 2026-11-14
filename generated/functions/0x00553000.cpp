// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00553000 rf_solid_clear_selected_face_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Thiscall solid,sets count0 of pointer-array at solid+216 to0 through518120,returns ADDRESS OF MEMBER HEADER. Capacity/backing and pointed face objects remain;no face flags changed or pointer frees.
_DWORD *__thiscall rf_solid_clear_selected_face_count(_DWORD *this)
{
  return rf_pointer_array_clear_count_keep_storage(this + 54);
}

