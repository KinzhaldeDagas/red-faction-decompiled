// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566C30 rf_scene_instance_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Calls scene_instance_destroy_owned_arrays(receiver), then operator-deletes receiver if flags&1 set, returns original pointer bits even when freed. Other flags ignored; does not itself delete shared scene definition/cache.
void *__thiscall rf_scene_instance_scalar_deleting_destructor(void *this, char a2)
{
  rf_scene_instance_destroy_owned_arrays(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

