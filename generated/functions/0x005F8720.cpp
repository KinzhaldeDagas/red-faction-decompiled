// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F8720 rf_scene_frame48_construct_quaternion_only
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): 48-byte frame constructor used by scene loader array iterator. Calls no-op vector default at0,then sets float4 at12 to(0,0,0,1). Does NOT initialize position0..11 or five scalar floats28..47. No allocation or meaningful return.
void __thiscall rf_scene_frame48_construct_quaternion_only(float *this)
{
  rf_vector3_default_construct_noop(this);
  rf_float4_construct_zero_zero_zero_one(this + 3);
}

