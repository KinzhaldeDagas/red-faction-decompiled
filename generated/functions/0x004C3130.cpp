// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C3130 rf_explosion_graph_record_construct_vectors_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Thiscall graph record, returns receiver. Calls NOOP vec3 constructors at0 and12, then constructor iterators for eight12B vec3 at36 and eight at132. All eighteen vec3 constructors
// leave components untouched; no scalar/count/room/definition/tracking-pointer/list-link initialization, no memset/allocation. Separate pool initialize4C1F20 zeroes eight308B
// records; do not infer that behavior from this constructor.
char *__thiscall rf_explosion_graph_record_construct_vectors_noop(char *this)
{
  rf_vector3_default_construct_noop(this);
  rf_vector3_default_construct_noop(this + 12);
  rf_vector_construct_no_unwind(this + 36, 0xCu, 8, rf_vector3_default_construct_noop);
  rf_vector_construct_no_unwind(this + 132, 0xCu, 8, rf_vector3_default_construct_noop);
  return this;
}

