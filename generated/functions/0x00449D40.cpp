// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449D40 rf_geomod_operation_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Thiscall100-byte runtime operation constructor; returns receiver. Calls no-op vector constructors at+8,+64,+76,+88 and no-op matrix row constructor at+20. Therefore performs NO
// operation payload initialization: cutter id0,room id4,position8,matrix20,flags56,scale60,impact normal64,constraint vectors76/88 retain existing bytes. Actual admission/replay must
// assign each consumed field. Earlier short 'initializes vectors' label refers to constructor calls, not zeroing or identity defaults.
char *__thiscall rf_geomod_operation_init(char *this)
{
  rf_vector3_default_construct_noop(this + 8);
  rf_matrix3_construct(this + 20);
  rf_vector3_default_construct_noop(this + 64);
  rf_vector3_default_construct_noop(this + 76);
  rf_vector3_default_construct_noop(this + 88);
  return this;
}

