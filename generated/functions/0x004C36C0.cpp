// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C36C0 rf_firing_effect_slot_set_enabled_for_mode
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Cdecl slotIndex,enabledDWORD. Current multiplayer BYTE0 chooses pointer pair0/4; ANY nonzero chooses8/12. Operates only when BOTH selected pointers nonnull, then nonzero enabled
// enables both, zero disables both. Inactive mode pair untouched; no allocation/destruction/pose refresh/index validation. Return EAX incidental mode or last delegate, not normalized
// success.
int __cdecl rf_firing_effect_slot_set_enabled_for_mode(int a1, int a2)
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode )
  {
    if ( unk_814D00[10 * a1] && unk_814D04[10 * a1] )
    {
      if ( a2 )
      {
        rf_particle_emitter_enable(unk_814D00[10 * a1]);
        return rf_particle_emitter_enable(unk_814D04[10 * a1]);
      }
      else
      {
        rf_particle_emitter_disable((_BYTE *)unk_814D00[10 * a1]);
        return (int)rf_particle_emitter_disable((_BYTE *)unk_814D04[10 * a1]);
      }
    }
  }
  else if ( unk_814CF8[10 * a1] && unk_814CFC[10 * a1] )
  {
    if ( a2 )
    {
      rf_particle_emitter_enable(unk_814CF8[10 * a1]);
      return rf_particle_emitter_enable(unk_814CFC[10 * a1]);
    }
    else
    {
      rf_particle_emitter_disable((_BYTE *)unk_814CF8[10 * a1]);
      return (int)rf_particle_emitter_disable((_BYTE *)unk_814CFC[10 * a1]);
    }
  }
  return result;
}

