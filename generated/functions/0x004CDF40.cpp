// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CDF40 rf_particle_emitter_process
// UNREALRED VERIFIED [combat-native-followup-20261104]: When global emitter processing enabled, advances/toggles alternate state, conditionally emits, THEN resolves parent handle and copies parent cached room to emitter+76 when flag0x40 is clear. Parent-room refresh still occurs when runtime emission is disabled or deadline not due. No generic pre-spawn point reclassification or retain-prior fallback appears in this function.
int __thiscall rf_particle_emitter_process(int this)
{
  int result; // eax
  void *v3; // [esp+4h] [ebp-4h]

  result = (unsigned __int8)byte_662DF4;
  if ( byte_662DF4 )
  {
    if ( (*(_WORD *)(this + 56) & 0x20) != 0 )
    {
      *(float *)(this + 316) = *(float *)(this + 316) + rf_frame_delta_seconds;
      if ( *(float *)(this + 312) <= (double)*(float *)(this + 316) )
      {
        *(float *)(this + 316) = 0.0;
        *(_BYTE *)(this + 320) = *(_BYTE *)(this + 320) == 0;
        rf_particle_emitter_choose_alternate_duration(this);
      }
    }
    if ( *(_BYTE *)(this + 320) && ((*(_WORD *)(this + 56) & 4) != 0 || rf_replicator_has_elapsed((int *)(this + 340))) )
      rf_particle_emitter_spawn_particle((float *)this);
    result = rf_object_resolve_handle(*(_DWORD *)(this + 4));
    v3 = (void *)result;
    if ( result )
    {
      result = this;
      if ( (*(_WORD *)(this + 56) & 0x40) == 0 )
      {
        result = rf_receiver_get_first_dword(v3);
        *(_DWORD *)(this + 76) = result;
      }
    }
  }
  return result;
}

