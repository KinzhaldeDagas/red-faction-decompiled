// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C3180 rf_firing_effect_ring_initialize16
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Cdecl no args. For16 records stride40 starting814CF8 zeros four emitter pointers at offsets0/4/8/12; resets next-slot index814CF0=0. Does NOT release existing emitters or clear
// position16/direction28. Normal EAX16 is loop artifact, not number of active effects.
int rf_firing_effect_ring_initialize16()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 16; ++i )
  {
    unk_814CF8[10 * i] = 0;
    unk_814CFC[10 * i] = 0;
    unk_814D00[10 * i] = 0;
    unk_814D04[10 * i] = 0;
    result = i + 1;
  }
  unk_814CF0 = 0;
  return result;
}

