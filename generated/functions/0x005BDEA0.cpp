// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BDEA0 rf_particle36_construct_free
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Calls no-op vector constructors for position+12 and velocity+24,then writes age float+0=-1.0 to mark free. Lifetime+4,angle+8,position/velocity remain unchanged. Used in36-byte cookie arrays; does not initialize full particle or update live count.
void __thiscall rf_particle36_construct_free(float *this)
{
  rf_vector3_default_construct_noop(this + 3);
  rf_vector3_default_construct_noop(this + 6);
  *this = -1.0;
}

