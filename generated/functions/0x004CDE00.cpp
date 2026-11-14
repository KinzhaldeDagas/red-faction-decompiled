// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CDE00 rf_particle_emitter_detach_live_particles
// UNREALRED VERIFIED [vfx-particle-lifecycle] Unlinks every live particle owned by an emitter, clears its emitter owner, and moves it to the global live-particle list so it can finish naturally.
int *__thiscall rf_particle_emitter_detach_live_particles(int *this)
{
  int *result; // eax
  int v2; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  result = this;
  if ( *(this + 44) )
  {
    for ( i = *(this + 44); ; i = v2 )
    {
      v2 = *(_DWORD *)i;
      if ( (int *)i == this + 44 )
        break;
      **(_DWORD **)(i + 4) = *(_DWORD *)i;
      *(_DWORD *)(*(_DWORD *)i + 4) = *(_DWORD *)(i + 4);
      *(_DWORD *)i = 0;
      *(_DWORD *)(i + 4) = 0;
      *(_DWORD *)(i + 104) = 0;
      *(_DWORD *)(i + 4) = unk_867C64;
      *(_DWORD *)i = &dword_867C60;
      *unk_867C64 = i;
      unk_867C64 = i;
    }
    *(this + 44) = (int)(this + 44);
    *(this + 45) = (int)(this + 44);
    return nullptr;
  }
  return result;
}

