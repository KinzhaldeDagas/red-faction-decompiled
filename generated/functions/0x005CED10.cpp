// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CED10 rf_scene_record144_construct_vectors_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Loader constructs144-byte records with this callback;calls no-op vector defaults at+96,+108 then returns receiver. No bytes initialized,including names/counts/pointers. Original record class name remains unproven;size/offsets verified from allocation caller.
char *__thiscall rf_scene_record144_construct_vectors_noop(char *this)
{
  rf_vector3_default_construct_noop(this + 96);
  rf_vector3_default_construct_noop(this + 108);
  return this;
}

