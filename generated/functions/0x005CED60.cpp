// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CED60 rf_scene_pose_vector_record40_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Loader uses40-byte records;no-op position vector at0,quaternion+12=(0,0,0,1),no-op vector+28;returns receiver. Both vectors and any implicit semantics remain unchanged;does not initialize all40 bytes.
float *__thiscall rf_scene_pose_vector_record40_construct(float *this)
{
  rf_vector3_default_construct_noop(this);
  rf_float4_construct_zero_zero_zero_one(this + 3);
  rf_vector3_default_construct_noop(this + 7);
  return this;
}

