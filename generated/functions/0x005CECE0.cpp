// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CECE0 rf_scene_pose_key28_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Loader uses28-byte records: calls no-op position vector at+0,initializes quaternion+12=(0,0,0,1),returns receiver. Position bytes remain unchanged;no frame-time field or allocation inside callback.
float *__thiscall rf_scene_pose_key28_construct(float *this)
{
  rf_vector3_default_construct_noop(this);
  rf_float4_construct_zero_zero_zero_one(this + 3);
  return this;
}

