// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FAD40 rf_scene_transform_frame28_construct_quaternion_only
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): 28-byte frame constructor:vector default at0 is no-op,quaternion float4 at12=(0,0,0,1). Position remains uninitialized. Does not allocate or write beyond28bytes;used by scene loader array constructor iterator.
void __thiscall rf_scene_transform_frame28_construct_quaternion_only(float *this)
{
  rf_vector3_default_construct_noop(this);
  rf_float4_construct_zero_zero_zero_one(this + 3);
}

