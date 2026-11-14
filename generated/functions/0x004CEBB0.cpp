// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CEBB0 rf_particle_emitter_render_live_particles
// UNREALRED VERIFIED [vfx-particle-render] Walks one emitter's owned live-particle list and renders every particle through the shared billboard path.
_DWORD *__cdecl rf_particle_emitter_render_live_particles(_DWORD *a1)
{
  _DWORD *result; // eax
  _DWORD *i; // [esp+4h] [ebp-4h]

  result = a1;
  for ( i = (_DWORD *)a1[44]; i != a1 + 44; i = (_DWORD *)*i )
  {
    rf_particle_render_billboard((int)i);
    result = i;
  }
  return result;
}

