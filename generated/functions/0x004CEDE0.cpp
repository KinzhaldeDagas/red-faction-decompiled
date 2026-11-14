// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CEDE0 rf_particle_emitter_destroy
// UNREALRED VERIFIED [vfx-particle-lifecycle] Detaches live particles before unlinking the emitter, returning the emitter record to its free list, and decrementing the active count.
int __cdecl rf_particle_emitter_destroy(int *a1)
{
  rf_particle_emitter_detach_live_particles(a1);
  *(_DWORD *)(a1[83] + 328) = a1[82];
  *(_DWORD *)(a1[82] + 332) = a1[83];
  a1[82] = 0;
  a1[83] = 0;
  a1[83] = unk_867E24;
  a1[82] = (int)dword_867CD8;
  *(_DWORD *)(unk_867E24 + 328) = a1;
  unk_867E24 = a1;
  return --unk_867900;
}

