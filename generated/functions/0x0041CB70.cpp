// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CB70 rf_face_flags_has_mask2
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Thiscall pointer to face flags DWORD (caller passes face+40), no stack args. Returns canonical AL bool for mask0x02 only. No other fields, validation or mutation. Reflection renderer accepts this predicate OR liquid-mask4 predicate; broader material semantics are not inferred here.
bool __thiscall rf_face_flags_has_mask2(_DWORD *this)
{
  return (*this & 2) != 0;
}

