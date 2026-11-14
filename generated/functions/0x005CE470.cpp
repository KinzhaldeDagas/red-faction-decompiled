// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CE470 rf_scene_point_state60_default_construct_members
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Default constructor for60-byte point states calls no-op vector constructors at+12,+24;no bytes initialized here. Does not allocate/bind point pool slot,clear definition pointer or initialize other flags/times.
void __thiscall rf_scene_point_state60_default_construct_members(char *this)
{
  rf_vector3_default_construct_noop(this + 12);
  rf_vector3_default_construct_noop(this + 24);
}

