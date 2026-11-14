// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CE5D0 rf_scene_transform_state40_default_construct_members
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Default constructor for40-byte transform states calls no-op vector+12 and initializes quaternion+24=(0,0,0,1). Definition pointer,flags/timing fields+0..11 and vector bytes remain untouched. Explicit transform-state bind constructor follows.
void __thiscall rf_scene_transform_state40_default_construct_members(float *this)
{
  rf_vector3_default_construct_noop(this + 3);
  rf_float4_construct_zero_zero_zero_one(this + 6);
}

