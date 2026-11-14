// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CECA0 rf_scene_vector_key40_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Writes firstDWORD0 via5CEC80,then calls no-op vectors at+4,+16,+28. Returns receiver;the three vectors remain uninitialized. Loader uses40-byte records;no bounds/ownership allocation or full zeroing.
char *__thiscall rf_scene_vector_key40_construct(char *this)
{
  rf_scene_key_set_first_dword(this, 0);
  rf_vector3_default_construct_noop(this + 4);
  rf_vector3_default_construct_noop(this + 16);
  rf_vector3_default_construct_noop(this + 28);
  return this;
}

