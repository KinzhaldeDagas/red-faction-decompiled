// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CE510 rf_particle_instance_default_construct_members
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Default member constructor for164-byte emitter states calls no-op vectors+32,+44,+92 and no-op matrix+56,then writes quaternion+104=(0,0,0,1). Leaves pointers,flags,age/time/live count and other fields untouched. Explicit bind5BF0B0 follows in scene instance constructor.
void __thiscall rf_particle_instance_default_construct_members(char *this)
{
  rf_vector3_default_construct_noop(this + 32);
  rf_vector3_default_construct_noop(this + 44);
  rf_matrix3_construct(this + 56);
  rf_vector3_default_construct_noop(this + 92);
  rf_float4_construct_zero_zero_zero_one((float *)this + 26);
}

