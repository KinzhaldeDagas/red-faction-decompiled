// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BDE60 rf_particle_key52_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Scene loader constructs array with stride52 using this callback and5BDE90 destructor. Calls no-op vector default on position+0 and initializes quaternion at+12 to(0,0,0,1). Remaining key scalars+28..48 untouched. No full zeroing or emitter-frame sample evaluation.
void __thiscall rf_particle_key52_construct(float *this)
{
  rf_vector3_default_construct_noop(this);
  rf_float4_construct_zero_zero_zero_one(this + 3);
}

