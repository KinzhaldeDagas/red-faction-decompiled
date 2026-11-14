// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556320 rf_vertex_component_record_destroy_members
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Destroys only pointer-array backing storage at component record+12. Does not destroy member vertices, alter XYZ, or free record itself.
void __thiscall rf_vertex_component_record_destroy_members(void **this)
{
  rf_pointer_array_destroy_backing_storage(this + 3);
}

