// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C39B0 rf_record40_construct_vecs16_28_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Thiscall record returns receiver. Calls NOOP vec3 constructors at16 and28 only; coordinates and first16B remain untouched. No four-emitter pointer initialization or resource
// acquisition. Do not conflate with ring reset4C3180.
int __thiscall rf_record40_construct_vecs16_28_noop(int this)
{
  rf_vector3_default_construct_noop((void *)(this + 16));
  rf_vector3_default_construct_noop((void *)(this + 28));
  return this;
}

