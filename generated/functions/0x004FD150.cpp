// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD150 rf_event_particle_state_apply_reverse
// UNREALRED VERIFIED [world-uid-ownership]: Particle_State type 39 reverse handler: resolves every authored target in the section-0xA00 registry and disables the matching emitter.
int __cdecl rf_event_particle_state_apply_reverse(int a1)
{
  int result; // eax
  int *v2; // eax
  int i; // [esp+0h] [ebp-8h]
  _BYTE *v4; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v4 = (_BYTE *)rf_particle_emitter_find_by_uid(*v2);
    if ( v4 )
      rf_particle_emitter_disable(v4);
  }
  return result;
}

