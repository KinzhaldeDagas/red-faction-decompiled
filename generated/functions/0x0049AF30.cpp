// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049AF30 rf_replication_encode_or_apply_entity_action_bits
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl(entity,bytePointer,BYTE encodeMode). Always first find current player by entity handle44 and sample current bits:1 holstered-for-actions predicate,2
// selected-weapon bit in Entity5160 via4387E0(entity,weapon676),4 crouched Entity2064mask400,8 player BYTE3988 nonzero. Resolve body-fire slots435390(entity,0/1). Include active
// primary/alternate bits10/20 only when (flame weapon AND alternate slot active) OR exact Grenade ID predicate5119F0 OR remote-charge flag; no other weapon classes sampled. Nonzero
// encodeMode writes computed byte and exits; zero means apply incoming byte without overwriting it. Compare lowbits1/2/4 against sampled prior; on change invoke holster
// setter/clearer, selected-weapon5160 setters438940/438820, crouch/uncrouch436100/4361B0. Callees may refuse transition; no retry/success check. Fire requests independent of sampler
// weapon gate: if incoming10, primary slot>=0 and inactive, request primary0; ONLY if that branch not taken consider20/alternate slot/request1. At most one request, primary priority.
// Missing bits do not stop active firing actions. Finally if player found assign BYTE3988 exact0/1 from incoming8 on every apply. No runtime/authority/packet-length/entity/pointer
// guard; bits40/80 ignored. Nominal char return incidental AL, no coherent success status.
void __cdecl rf_replication_encode_or_apply_entity_action_bits(_DWORD *a1, unsigned __int8 *a2, char a3)
{
  unsigned __int8 is_holstered_for_actions; // [esp+3h] [ebp-Dh]
  signed int v4; // [esp+4h] [ebp-Ch]
  _DWORD *v5; // [esp+8h] [ebp-8h]
  signed int v6; // [esp+Ch] [ebp-4h]

  v5 = sub_4DD720(a1[11]);
  is_holstered_for_actions = rf_entity_weapon_is_holstered_for_actions((int)a1);
  if ( rf_entity_selected_weapon_state_bit_is_set((int)a1, a1[169]) )
    is_holstered_for_actions |= 2u;
  if ( rf_entity_is_crouched_state810((int)a1) )
    is_holstered_for_actions |= 4u;
  if ( v5 && *((_BYTE *)v5 + 3988) )
    is_holstered_for_actions |= 8u;
  v6 = rf_entity_select_body_fire_slot_for_stance((int)a1, 0);
  v4 = rf_entity_select_body_fire_slot_for_stance((int)a1, 1);
  if ( rf_weapon_has_flame_flag(a1[169]) && rf_entity_body_action_is_active((int)a1, v4)
    || sub_5119F0(a1[169])
    || rf_weapon_has_remote_charge_flag(a1[169]) )
  {
    if ( rf_entity_body_action_is_active((int)a1, v6) )
      is_holstered_for_actions |= 0x10u;
    if ( rf_entity_body_action_is_active((int)a1, v4) )
      is_holstered_for_actions |= 0x20u;
  }
  if ( a3 )
  {
    *a2 = is_holstered_for_actions;
  }
  else
  {
    if ( ((*a2 ^ is_holstered_for_actions) & 1) != 0 )
    {
      if ( (*a2 & 1) != 0 )
        rf_entity_try_set_holster_and_stop_primary(a1);
      else
        rf_entity_clear_holster_if_mapped_weapon_owned(a1);
    }
    if ( ((*a2 ^ is_holstered_for_actions) & 2) != 0 )
    {
      if ( (*a2 & 2) != 0 )
        rf_entity_set_custom_weapon_masks_and_begin_actions(a1, a1[169]);
      else
        rf_entity_clear_custom_weapon_masks_and_leave_actions(a1, a1[169]);
    }
    if ( ((*a2 ^ is_holstered_for_actions) & 4) != 0 )
    {
      if ( (*a2 & 4) != 0 )
        rf_entity_apply_crouch_shape_centers((int)a1);
      else
        rf_entity_try_apply_standing_shape_centers((int)a1);
    }
    if ( (*a2 & 0x10) == 0 || v6 < 0 || rf_entity_body_action_is_active((int)a1, v6) )
    {
      if ( (*a2 & 0x20) != 0 && v4 >= 0 && !rf_entity_body_action_is_active((int)a1, v4) )
        rf_entity_request_body_fire_action((int)a1, 1);
    }
    else
    {
      rf_entity_request_body_fire_action((int)a1, 0);
    }
    if ( v5 )
      *((_BYTE *)v5 + 3988) = (*a2 & 8) != 0;
  }
}

