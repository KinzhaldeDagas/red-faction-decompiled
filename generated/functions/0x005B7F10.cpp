// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B7F10 rf_scene_definition_set_retained_flag1
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Thiscall scene definition:ORs DWORD304 with1,returns receiver. Scene cache sweep5B21C0 tests this bit to KEEP record. No loading, reference count or membership validation.
_DWORD *__thiscall rf_scene_definition_set_retained_flag1(_DWORD *this)
{
  *(this + 76) |= 1u;
  return this;
}

