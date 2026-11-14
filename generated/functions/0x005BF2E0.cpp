// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BF2E0 rf_particle_instance_destroy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): If particle-array pointer+144 nonNULL invokes36-byte vector deleting destructor5BFDD0(flags3) to destroy/free cookie allocation. For each3 nonNULL72-byte channel-state pointers+4..12 invokes5BFE40(flags1). Does not NULL freed pointers,delete containing runtime or free shared definition. Prior Concurrency::GlobalCore** receiver type was false SDK match; receiver is particle instance.
void __thiscall rf_particle_instance_destroy(void *this)
{
  int i; // [esp+1Ch] [ebp-4h]

  if ( *((_DWORD *)this + 36) )
    rf_particle36_vector_deleting_destructor(*((void **)this + 36), 3u);
  for ( i = 0; i < 3; ++i )
  {
    if ( *((_DWORD *)this + i + 1) )
      rf_scene_frame_channel_state_scalar_deleting_destructor(*((void **)this + i + 1), 1);
  }
}

