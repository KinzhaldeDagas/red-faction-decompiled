// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B28C0 rf_scene_model_definition292_destroy_arrays
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Operator deletes nonNULL pointers+208 and+216,then invokes verified no-op base destructor4580D0. Does not NULL pointers,delete292-byte containing definition or release shared scene pools. Cookie-array deletion adapter5CE600 handles containing storage.
void __thiscall rf_scene_model_definition292_destroy_arrays(void **this)
{
  if ( *(this + 52) )
    operator delete(*(this + 52));
  if ( *(this + 54) )
    operator delete(*(this + 54));
  rf_shared_noop_destructor_4580d0();
}

