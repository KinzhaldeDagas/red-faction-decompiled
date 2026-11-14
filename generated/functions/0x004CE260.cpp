// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CE260 rf_particle_pool_detach_emitters_and_recycle_secondary
// UNREALRED VERIFIED [resource-pools-20261028]: Traverses emitter list0x867A50 to sentinel0x867908 via+328, detaching live particles through rf_particle_emitter_detach_live_particles. Then moves each node from circular active list sentinel0x867C60 to free list sentinel0x866704 using links+0/+4, decrementing0x8667F4 per node. Does not free particle storage or release emitter objects.
int rf_particle_pool_detach_emitters_and_recycle_secondary()
{
  int result; // eax
  int *i; // [esp+0h] [ebp-Ch]
  int v2; // [esp+4h] [ebp-8h]
  int j; // [esp+8h] [ebp-4h]

  for ( i = (int *)dword_867A50; i != dword_867908; i = (int *)i[82] )
    rf_particle_emitter_detach_live_particles(i);
  for ( j = dword_867C60; ; j = v2 )
  {
    result = *(_DWORD *)j;
    v2 = *(_DWORD *)j;
    if ( (int *)j == &dword_867C60 )
      break;
    **(_DWORD **)(j + 4) = *(_DWORD *)j;
    *(_DWORD *)(*(_DWORD *)j + 4) = *(_DWORD *)(j + 4);
    *(_DWORD *)j = 0;
    *(_DWORD *)(j + 4) = 0;
    *(_DWORD *)(j + 4) = unk_866708;
    *(_DWORD *)j = &unk_866704;
    *unk_866708 = j;
    unk_866708 = j;
    --unk_8667F4;
  }
  return result;
}

