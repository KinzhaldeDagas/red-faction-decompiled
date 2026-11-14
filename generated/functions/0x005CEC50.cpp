// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CEC50 rf_scene_rotation_key20_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Scene loader allocates stride20 records using this callback. Writes firstDWORD0 through setter5CEC80,then packed quaternion fourWORDs at+4=(0,0,0,1). Remaining bytes12..19 untouched. Does not initialize a normalized fixed-point identity or all timing/ease metadata; distinct from16-byte raw RFA rotation-key layout.
_WORD *__thiscall rf_scene_rotation_key20_construct(_WORD *this)
{
  rf_scene_key_set_first_dword(this, 0);
  rf_short_quaternion_construct_0001(this + 2);
  return this;
}

