// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00485560 rf_geomod_history_sidecar36_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Thiscall36-byte sidecar constructor, returns receiver. Calls three no-op vector constructors at0,12,24; writes no payload. Original static iterator0x62C130 constructs128
// entries,stride36,base0x6FDD50. Fields later hold adjusted operation position and two constraint vectors; no initial zero-vector guarantee from this constructor.
int __thiscall rf_geomod_history_sidecar36_construct_noop(int this)
{
  rf_vector3_default_construct_noop((void *)this);
  rf_vector3_default_construct_noop((void *)(this + 12));
  rf_vector3_default_construct_noop((void *)(this + 24));
  return this;
}

