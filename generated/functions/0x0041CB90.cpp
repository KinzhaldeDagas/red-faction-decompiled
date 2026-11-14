// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CB90 rf_face_is_liquid
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Thiscall pointer to face flags DWORD, no stack args; returns SETNZ AL from mask0x04. No null guard or mutation. This helper does not itself control sweep admission: core liquid-face inclusion uses query mask0x1000 and traversal context, whereas glare reflection separately accepts a returned face with mask2 OR4.
bool __thiscall rf_face_is_liquid(_DWORD *this)
{
  return (*this & 4) != 0;
}

