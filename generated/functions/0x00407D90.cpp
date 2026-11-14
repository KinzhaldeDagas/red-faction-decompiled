// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00407D90 rf_ai_secondary_weapon_action_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block. Global BYTE661010 any nonzero ->ready predicate any nonzero; owner435A50 predicate EXACT
// AL1 suppresses (helper tests class name Hendrix). Then damage-flinch-override predicate EXACT1 suppresses. Otherwise407E10(block) EXACT AL1 invokes433A90(owner,LOWBYTE0), two
// native stack arguments. Other AL values do not launch that helper. Returns incidental AL from last predicate/action; no independently assembled success result, own weapon-index
// validation, mode or authority admission. Secondary action helper owns deadline/ammo/projectile and fallback behavior.
char __cdecl rf_ai_secondary_weapon_action_dispatch(int *a1)
{
  char result; // al

  result = byte_661010;
  if ( byte_661010 )
  {
    result = rf_ai_is_ready_flag_set((int)a1);
    if ( result )
    {
      result = rf_entity_class_name_is_hendrix(*a1);
      if ( result != 1 )
      {
        result = rf_character_update_damage_flinch_override(*a1);
        if ( result != 1 )
        {
          result = rf_ai_secondary_weapon_target_admitted(a1);
          if ( result == 1 )
            return rf_entity_fire_secondary_or_begin_charge((_DWORD *)*a1, 0);
        }
      }
    }
  }
  return result;
}

