// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CB140 rf_particle_pool_recycle_all_active
// UNREALRED VERIFIED [resource-pools-20261028]: First invokes0x4CE260 to detach emitter particles/recycle secondary list. Then moves every node in active list sentinel0x866680 to free list sentinel0x866608 via doubly-linked+0/+4, decrementing0x8666F8. Does not zero full records, release bitmap references or free heap storage in this body.
// UNREALRED VERIFIED [combat-particle-vbm-lifetime-20261104]: Nativeleveldestroy477770 calls thiscleanup at477AB3.4CE260 detaches/recycles emitter/livepool1 particles, then thisroutine drainsglobalpool0 active list tofree list anddecrementscount. DirectVBM particlesusepool0; theirN/FPS life isnotpermission tosurvivelevel destruction. Unreal actor/container cleanup is its resource-backend mapping, not a claim that Unreal has RFroom/portal visibility ownership.
int rf_particle_pool_recycle_all_active()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  rf_particle_pool_detach_emitters_and_recycle_secondary();
  for ( i = dword_866680; ; i = v1 )
  {
    result = *(_DWORD *)i;
    v1 = *(_DWORD *)i;
    if ( (_DWORD *)i == &dword_866680 )
      break;
    **(_DWORD **)(i + 4) = *(_DWORD *)i;
    *(_DWORD *)(*(_DWORD *)i + 4) = *(_DWORD *)(i + 4);
    *(_DWORD *)i = 0;
    *(_DWORD *)(i + 4) = 0;
    *(_DWORD *)(i + 4) = dword_86660C[0];
    *(_DWORD *)i = &unk_866608;
    *(_DWORD *)dword_86660C[0] = i;
    dword_86660C[0] = i;
    --unk_8666F8;
  }
  return result;
}

