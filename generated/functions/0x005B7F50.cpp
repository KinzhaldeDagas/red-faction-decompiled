// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B7F50 rf_ribbon_descriptor_construct_points_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Thiscall descriptor pointer. Invokes vec3 default constructor for16 entries at offset4,stride12,then returns receiver. That vector constructor is verified no-op, so point bytes and all other descriptor fields remain unchanged. Does not zero count,texture196,width200,append points or validate capacity;5B5E10 supplies a212-byte local descriptor and fills selected fields.
char *__thiscall rf_ribbon_descriptor_construct_points_noop(char *this)
{
  rf_vector_construct_no_unwind(this + 4, 0xCu, 16, rf_vector3_default_construct_noop);
  return this;
}

