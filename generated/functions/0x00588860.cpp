// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00588860 rf_v3c_asset148_clear_selected_mesh
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Writes descriptor DWORD+144=0 and returns this. Does not release mesh arrays or reset base descriptor counters.
_DWORD *__thiscall rf_v3c_asset148_clear_selected_mesh(_DWORD *this)
{
  *(this + 36) = 0;
  return this;
}

