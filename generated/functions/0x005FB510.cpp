// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FB510 rf_scene_transform_track_state_update_compat
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall args float frame,two unusedDWORDs;callee pops12. Forwards onlyframe to0x5FB2C0,returns result. Extra arguments have no effects;no separate loop or interpolation logic.
float *__thiscall rf_scene_transform_track_state_update_compat(float *this, float a2, int a3, int a4)
{
  return rf_scene_transform_track_state_update(this, a2);
}

