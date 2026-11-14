// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BF0B0 rf_particle_instance_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Stores definition pointer0,clears emission-disable flags+16 and high four control bits28..31 of flags+20 (preserves low28). Zeros world origin+32,sets orientation+56 identity and elapsedSeconds+28=0; previous origin+44 left for first update. For each of3 nonNULL channel definitions allocates72-byte channel state; absent channel storesNULL. Allocates cookie array of definition.maxParticles36-byte records,constructor sets only free age-1. Compiler multiplication/addition overflow guards request size-1 on overflow. Stores particle pointer+144,liveCount+148=0,lastFrame+152=0 for nonnegative emissionStart else emissionStart asfloat,emissionFraction+156=0,backlogSeconds+160=0. Many attachment/local sampled fields
// untouched until update. No allocation rollback/NULL-use guard beyond constructor patterns.
char *__thiscall rf_particle_instance_construct(char *this, int a2)
{
  int v2; // ecx
  char *v4; // [esp+4h] [ebp-30h]
  float *v5; // [esp+8h] [ebp-2Ch]
  char *v7; // [esp+10h] [ebp-24h]
  int v8; // [esp+18h] [ebp-1Ch]
  float *v9; // [esp+1Ch] [ebp-18h]
  int i; // [esp+24h] [ebp-10h]

  *(_DWORD *)this = a2;
  *((_DWORD *)this + 4) = 0;
  *((_DWORD *)this + 5) &= ~0x10000000u;
  *((_DWORD *)this + 5) &= ~0x20000000u;
  *((_DWORD *)this + 5) &= ~0x40000000u;
  *((_DWORD *)this + 5) &= ~0x80000000;
  rf_vector3_zero_return_destination((float *)this + 8);
  rf_identity_orientation_matrix((float *)this + 14);
  *((float *)this + 7) = 0.0;
  for ( i = 0; i < 3; ++i )
  {
    if ( *(_DWORD *)(*(_DWORD *)this + 4 * i + 136) )
    {
      v9 = (float *)operator new(0x48u);
      if ( v9 )
        v5 = rf_scene_frame_channel_state_construct(v9, *(_DWORD *)(*(_DWORD *)this + 4 * i + 136));
      else
        v5 = nullptr;
      *((_DWORD *)this + i + 1) = v5;
    }
    else
    {
      *((_DWORD *)this + i + 1) = 0;
    }
  }
  v8 = *(_DWORD *)(a2 + 152);
  v2 = (36 * (unsigned __int64)(unsigned int)v8) >> 32 != 0 ? -1 : 36 * v8;
  v7 = (char *)operator new(__CFADD__(v2, 4) ? -1 : v2 + 4);
  if ( v7 )
  {
    *(_DWORD *)v7 = v8;
    `eh vector constructor iterator'(
      v7 + 4,
      0x24u,
      v8,
      (void (__thiscall *)(void *))rf_particle36_construct_free,
      rf_particle36_destroy_noop);
    v4 = v7 + 4;
  }
  else
  {
    v4 = nullptr;
  }
  *((_DWORD *)this + 36) = v4;
  *((_DWORD *)this + 37) = 0;
  if ( *(int *)(a2 + 156) >= 0 )
    *((float *)this + 38) = 0.0;
  else
    *((float *)this + 38) = (float)*(int *)(a2 + 156);
  *((float *)this + 39) = 0.0;
  *((float *)this + 40) = 0.0;
  return this;
}

