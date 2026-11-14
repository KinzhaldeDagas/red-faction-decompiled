// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00428820 rf_entity_update_motion_scaled_positioned_voice
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required entity). Exact voice DWORD2060==-1 exits with EAX=entity pointer; any other value, including other negative values, proceeds. RatioA
// startsFLOAT0; only ORDERED class FLOAT80>0 computes round32(length(entity vector324)/class80). RatioB startsFLOAT0; only ORDERED class FLOAT96>0, movement predicate437F60 AL0, and
// class flags1828 mask0x40 CLEAR compute round32(length(entity vector336)/class96), in that short-circuit order. Equal/negative/NaN denominators skip their ratio; positive infinity
// is not independently rejected. Choose B only for ORDERED B>A; B<=A OR UNORDERED preserves A, so this is not a symmetric NaN-normalizing maximum.438090(entity,-1) AL0 then forces
// chosen ratio0, any nonzero preserves it. Clamp in place via40D620(lowerFLOAT0,upperFLOAT1): ordered bounds only, NaN chosen ratio survives. Calls5684D0 with FOUR stack
// slots(voice2060,position60,vector324,FLOAT ratio), passes fullEAX return through; no independent success status. Native partial stack cleanup after clamp intentionally
// retains/reuses one FLOAT slot for update argument, not an extra incoming argument. No create/stop, state/voice reset, finite/death/authority gate or rollback.
int __cdecl rf_entity_update_motion_scaled_positioned_voice(int a1)
{
  int result; // eax
  int v2; // [esp+8h] [ebp-8h] BYREF
  int v3; // [esp+Ch] [ebp-4h]

  result = a1;
  if ( *(_DWORD *)(a1 + 2060) != -1 )
  {
    *(float *)&v2 = 0.0;
    if ( *(float *)(*(_DWORD *)(a1 + 660) + 80) > 0.0 )
      *(float *)&v2 = rf_vector3_length((float *)(a1 + 324)) / *(float *)(*(_DWORD *)(a1 + 660) + 80);
    *(float *)&v3 = 0.0;
    if ( *(float *)(*(_DWORD *)(a1 + 660) + 96) > 0.0
      && !rf_entity_descriptor_mode_is_12_15_13_11_or9(a1)
      && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x40) == 0 )
    {
      *(float *)&v3 = rf_vector3_length((float *)(a1 + 336)) / *(float *)(*(_DWORD *)(a1 + 660) + 96);
    }
    if ( *(float *)&v3 > (double)*(float *)&v2 )
      v2 = v3;
    if ( !rf_entity_runtime_enabled_or_resolved_attachment(a1, -1) )
      *(float *)&v2 = 0.0;
    rf_float_clamp_in_place((float *)&v2, 0.0, 1.0);
    return rf_positioned_voice_update(*(_DWORD *)(a1 + 2060), (float *)(a1 + 60), a1 + 324, *(float *)&v2);
  }
  return result;
}

