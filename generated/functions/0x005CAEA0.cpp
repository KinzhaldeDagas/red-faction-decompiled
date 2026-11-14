// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CAEA0 rf_scene_instance_destroy_owned_arrays
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Cookie-deletes nonNULL runtime arrays+20(model states152),+24(point states60),+28(emitter states164),+32(transform states40),all flags3. Does not NULL pointers,reset flags/time,delete containing instance or destroy shared definition+8. EAX branch-dependent incidental pointer,NOT Concurrency::GlobalNode*. No guards against repeated destruction.
void __thiscall rf_scene_instance_destroy_owned_arrays(void *this)
{
  if ( *((_DWORD *)this + 5) )
    rf_scene_model_state152_vector_deleting_destructor(*((char **)this + 5), 3);
  if ( *((_DWORD *)this + 6) )
    rf_scene_point_state60_vector_deleting_destructor(*((char **)this + 6), 3);
  if ( *((_DWORD *)this + 7) )
    rf_particle_instance164_vector_deleting_destructor(*((char **)this + 7), 3);
  if ( *((_DWORD *)this + 8) )
    rf_scene_transform_state40_vector_deleting_destructor(*((void **)this + 8), 3u);
}

