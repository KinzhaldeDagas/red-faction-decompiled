// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E6D70 rf_player_reset_fpgun_and_apply_remote_charge_fallback
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): Assumes player nonNULL. First D9F0 resets fields4228/4236/4240. Resolve own UID+20. If entity exists AND selected primary676 equals registry911C78 remote charge AND player BYTE4164==0, directly write selected primary=911C88 remote charge detonator. No ownership, ammo, placed-charge, transition or model validity checks. Nonzero4164 leaves charge selected. Return EAX is NULL/entity pointer/flag residue, not a stable selected-weapon/status result.
int __cdecl rf_player_reset_fpgun_and_apply_remote_charge_fallback(int a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-4h]

  rf_player_reset_fpgun_fields4228_4236_4240(a1);
  result = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v2 = result;
  if ( result && *(_DWORD *)(result + 676) == dword_911C78 )
  {
    result = *(unsigned __int8 *)(a1 + 4164);
    if ( !*(_BYTE *)(a1 + 4164) )
      *(_DWORD *)(v2 + 676) = unk_911C88;
  }
  return result;
}

