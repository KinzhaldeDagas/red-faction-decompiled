// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043FFD0 rf_particle_emitter_definition_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): Thiscall receiver,no stack arguments,returns receiver EAX; corrected old integer receiver/result to pointer ABI. Calls no-write vector defaults at+4,+16 and no-write RGBA defaults at+108,+112. Performs NO writes to supplied particle-emitter-definition bytes; no zero/identity/color defaults, allocation or field validation. VClip definition224 constructor5079B0 invokes at+56, same embedded base passed by506AF0 to rf_particle_emitter_definition_parse. Uninitialized/static-zero storage behavior comes from caller/storage duration, not these default constructors.
void *__thiscall rf_particle_emitter_definition_construct_noop(void *self)
{
  rf_vector3_default_construct_noop((char *)self + 4);
  rf_vector3_default_construct_noop((char *)self + 16);
  rf_rgba8_default_construct_noop((char *)self + 108);
  rf_rgba8_default_construct_noop((char *)self + 112);
  return self;
}

