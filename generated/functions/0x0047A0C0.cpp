// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A0C0 rf_bolt_emitter_definition_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Thiscall constructor used by RFL bolt-emitter loader and zap console path. Calls no-op vector constructors at4,16,28,40 and no-op RGBA constructor92; returns receiver. No own
// payload stores, so id0, scalar/flag fields52..91 and vector/color components retain prior storage. Does not allocate or initialize runtime bolt chains.
int __thiscall rf_bolt_emitter_definition_construct_noop(int this)
{
  rf_vector3_default_construct_noop((void *)(this + 4));
  rf_vector3_default_construct_noop((void *)(this + 16));
  rf_vector3_default_construct_noop((void *)(this + 28));
  rf_vector3_default_construct_noop((void *)(this + 40));
  rf_rgba8_default_construct_noop((void *)(this + 92));
  return this;
}

