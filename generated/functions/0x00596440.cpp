// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00596440 rf_scene_point_record140_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): Thiscall calls float4(0,0,0,1) constructor at+4,no-op vector constructor at+20,then defaults helper595390 on whole receiver;returns receiver. First float4 initialization is repeated by helper. Initializes only listed prefix fields throughBYTE72,not tail73..139 or padding. Global array constructor62E670 uses this callback for50 records,stride8Ch=140,base1BC2160. No vtable,allocation or full zero fill.
float *__thiscall rf_scene_point_record140_construct(float *this)
{
  rf_float4_construct_zero_zero_zero_one(this + 1);
  rf_vector3_default_construct_noop(this + 5);
  rf_scene_point_record140_initialize_defaults(this);
  return this;
}

