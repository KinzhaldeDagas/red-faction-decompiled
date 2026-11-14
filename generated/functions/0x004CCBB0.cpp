// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CCBB0 rf_particle_update_all_live_lists
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Cdecl float delta_seconds. Clears moved counter 0x8377E4 and rendered counter 0x8377F0 before updating. Calls rf_particle_pool_update on pool0 unowned sentinel 0x866680, then on
// each active emitter's embedded particle sentinel +176 while walking head 0x867A50 to emitter sentinel base 0x867908 via emitter next +328, then on detached-particle sentinel
// 0x867C60. For each emitter, next is loaded after its pool-update callback, not snapshotted before it. Does not update pool1's unowned sentinel 0x86677C here. Returns final delegate
// EAX incidentally; no independent renderer submission occurs.
int __cdecl rf_particle_update_all_live_lists(float a1)
{
  int *i; // [esp+4h] [ebp-4h]

  unk_8377E4 = 0;
  unk_8377F0 = 0;
  rf_particle_pool_update(&dword_866680, a1);
  for ( i = (int *)dword_867A50; i != dword_867908; i = (int *)i[82] )
    rf_particle_pool_update(i + 44, a1);
  return rf_particle_pool_update(&dword_867C60, a1);
}

