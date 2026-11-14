// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B7F30 rf_scene_definition_test_retained_flag1
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Returns byte boolean from definition DWORD304&1. No mutation or resource query;scene sweep keeps entries for true and deletes unmarked. No null guard.
bool __thiscall rf_scene_definition_test_retained_flag1(_DWORD *this)
{
  return (*(this + 76) & 1) != 0;
}

