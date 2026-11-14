// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CF9B0 rf_underwater_particle32_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, emitter extent ownership, underwater motion/pause state, projectile geometry continuation and native output writes): 
// Thiscall constructor for 32-byte underwater particle; returns receiver. Calls no-op vectors at +0 and +12 and no-op RGBA at +28; radius+24 is untouched. Consequently writes no
// record fields. Original static constructor iterator at 0x62CD90 invokes it for1024 records of stride32 at 0x872A88. Explicit runtime initialization belongs to 0x4CF040.
int __thiscall rf_underwater_particle32_construct_noop(int this)
{
  rf_vector3_default_construct_noop((void *)this);
  rf_vector3_default_construct_noop((void *)(this + 12));
  rf_rgba8_default_construct_noop((void *)(this + 28));
  return this;
}

