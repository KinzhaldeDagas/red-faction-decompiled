// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00408D20 rf_ai_refresh_active_weapon_body_action
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block. Only422270(owner full handle+44,primary index block+4)==EXACT AL1 proceeds. Select body
// fire SLOT via stance helper(owner,0); directly inspect DWORD owner+2644+16*slot!=-1, with no own slot-range bound. Existing body-action-active(owner,slot) any-nonzero suppresses.
// Otherwise request body action(owner,slot,FLOAT1.0,LOWBYTE0,LOWBYTE1), five four-byte stack slots and20byte cleanup; ignores request result. No timer/target/mode updates or explicit
// dead/inactive/ownership admission. Stored char return is incidental rather than independently constructed boolean.
void __cdecl rf_ai_refresh_active_weapon_body_action(unsigned int *a1)
{
  unsigned int v1; // [esp+Ch] [ebp-4h]

  if ( rf_entity_weapon_firing_byte_is_set(*(_DWORD *)(*a1 + 44), a1[1]) )
  {
    v1 = rf_entity_select_body_fire_slot_for_stance(*a1, 0);
    if ( *(_DWORD *)(*a1 + 16 * v1 + 2644) != -1 && !rf_entity_body_action_is_active(*a1, v1) )
      rf_entity_request_body_action(*a1, v1, 1.0, 0, 1);
  }
}

