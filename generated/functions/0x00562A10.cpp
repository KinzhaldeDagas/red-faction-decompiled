// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562A10 rf_model_handle_advance_animation_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Tag2 calls character_instance_advance_animations(instance4,dt,byteFlag,extraDWORD), ignoring supplied transform pointers. Tag3 calls scene_instance_update_15fps(instance4,dt,position,orientation), ignoring byteFlag/extraDWORD. Other tags no work. Saved byte return is not a consistent success contract; no dt/instance validation.
char __thiscall rf_model_handle_advance_animation_dispatch(int *this, float a2, char a3, float *a4, float *a5, int a6)
{
  char result; // al

  result = (char)this;
  if ( *this == 2 )
    return rf_character_instance_advance_animations(*(this + 1), a2, (unsigned __int8)a3, a6);
  if ( *this == 3 )
    return rf_scene_instance_update_15fps((void *)*(this + 1), a2, a4, a5);
  return result;
}

