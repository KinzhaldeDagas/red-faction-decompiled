// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C31F0 rf_firing_effect_ring_destroy_all
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Cdecl no args. Calls4C35A0(slot) for each0..15; inherits paired-pointer release semantics (a lone nonnull emitter in a pair is not released before pointer clear). Does not reset
// next-slot index or stored pose. Normal EAX16 incidental loop result.
int rf_firing_effect_ring_destroy_all()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 16; ++i )
  {
    rf_firing_effect_slot_release_paired_emitters(i);
    result = i + 1;
  }
  return result;
}

