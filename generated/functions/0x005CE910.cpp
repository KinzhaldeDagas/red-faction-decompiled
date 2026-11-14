// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CE910 rf_scene_material_binding_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Invokes rf_scene_material_binding_destruct_noop;flag byte mask1 additionally operator deletes receiver,returns original pointer bits even after free. No vector/cookie handling for mask2,no member reset. Used at scene definition+128.
void *__thiscall rf_scene_material_binding_scalar_deleting_destructor(void *this, char a2)
{
  rf_scene_material_binding_destruct_noop();
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

