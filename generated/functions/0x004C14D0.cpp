// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C14D0 rf_bolt_emitter_slot_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, four-slot emitter lifecycle, allocation and constructor layouts, native ordered lifetime gates, attachment transforms and paused rendering): 
// Thiscall68B slot subobject, no stack args. Constructs DWORD/pointer array header at8 with capacity0 -> count/capacity/backing0. Calls NOOP vec3 constructors at20/32/44/56; leaves
// their components, life0 and curve pointer4 uninitialized here. Normal tail EAX receiver is incidental under current void prototype. Emitter allocation helper later supplies
// life/curve. Exception cleanup destroys backing header at8 only; no per-point ownership traversal in this constructor.
void __thiscall rf_bolt_emitter_slot_construct(char *this)
{
  rf_dword_array_construct_capacity(this + 8, 0);
  rf_vector3_default_construct_noop(this + 20);
  rf_vector3_default_construct_noop(this + 32);
  rf_vector3_default_construct_noop(this + 44);
  rf_vector3_default_construct_noop(this + 56);
}

