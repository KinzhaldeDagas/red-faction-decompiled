// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C35A0 rf_firing_effect_slot_release_paired_emitters
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Cdecl slotIndex, stride40 at814CF8. If BOTH emitter pointers0 AND4 nonnull: disables both then destroys both. Independently repeats for BOTH8 AND12. ALWAYS clears all four pointers
// afterward. A lone surviving pointer in a pair is orphaned without disable/destroy; not independent per-pointer cleanup. No bounds check, pose clear or ring-index update.
// EAX=40*slotIndex incidental address offset, not release count/status.
int __cdecl rf_firing_effect_slot_release_paired_emitters(int a1)
{
  if ( unk_814CF8[10 * a1] && unk_814CFC[10 * a1] )
  {
    rf_particle_emitter_disable((_BYTE *)unk_814CF8[10 * a1]);
    rf_particle_emitter_disable((_BYTE *)unk_814CFC[10 * a1]);
    rf_particle_emitter_destroy(unk_814CF8[10 * a1]);
    rf_particle_emitter_destroy(unk_814CFC[10 * a1]);
  }
  if ( unk_814D00[10 * a1] && unk_814D04[10 * a1] )
  {
    rf_particle_emitter_disable((_BYTE *)unk_814D00[10 * a1]);
    rf_particle_emitter_disable((_BYTE *)unk_814D04[10 * a1]);
    rf_particle_emitter_destroy(unk_814D00[10 * a1]);
    rf_particle_emitter_destroy(unk_814D04[10 * a1]);
  }
  unk_814CF8[10 * a1] = 0;
  unk_814CFC[10 * a1] = 0;
  unk_814D00[10 * a1] = 0;
  unk_814D04[10 * a1] = 0;
  return 40 * a1;
}

