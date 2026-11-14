// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005562F0 rf_vertex_component_record_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Destroys member pointer-array backing storage through556320, then operator-deletes record when flags bit0 set. Other flags ignored; returns original receiver pointer even after freeing it.
void **__thiscall rf_vertex_component_record_scalar_deleting_destructor(void **this, char a2)
{
  rf_vertex_component_record_destroy_members(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

