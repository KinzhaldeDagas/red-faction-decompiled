// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E0960 rf_player_update_entity_body_animation_for_movement
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Assumes player nonNULL, resolves own entity+20; missing returns AL0. Priority: attached turret AL==1->body state15; linked jeep seat0 AL==1->20, seat1 AL==1->21; player byte177 nonzero->9 when both entity motion X+1812/Z+1820 are within inclusive double +/-0.1 OR unordered at each native bound, otherwise10; 437F00 AL==1->14; movement-class4/7 predicate437FD0 AL==1->18 for exact zero motion vector,19 for unequal vector (NaN compares unequal). Zero vector already resident18 causes no new19 request. Otherwise fast vector length ordered<0.25 selects idle: carrying AL==1->16, else holstered nonzero or selected weapon==-1->0, else1. Length>=0.25 OR unordered selects moving: carrying AL==1->17, else holstered/nonweapon->4, else5. Request chosen
// state with F320.25 ONLY if current-or-pending resident predicate returns0. Numeric movement IDs and body-animation IDs are distinct domains. Native return AL is helper/x87-status/pointer residue, not selected state or success.
char __cdecl rf_player_update_entity_body_animation_for_movement(int a1)
{
  int v1; // eax
  float *v2; // eax
  float *v3; // eax
  float v5[3]; // [esp+Ch] [ebp-1Ch] BYREF
  float v6[3]; // [esp+18h] [ebp-10h] BYREF
  int v7; // [esp+24h] [ebp-4h]

  v1 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v7 = v1;
  if ( v1 )
  {
    if ( rf_entity_has_attached_use_turret(v7) )
    {
      LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 15);
      if ( !(_BYTE)v1 )
        LOBYTE(v1) = rf_entity_request_body_state(v7, 0xFu, 0.25);
    }
    else if ( rf_entity_is_parent_jeep_relation0(v7) )
    {
      LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 20);
      if ( !(_BYTE)v1 )
        LOBYTE(v1) = rf_entity_request_body_state(v7, 0x14u, 0.25);
    }
    else if ( rf_entity_is_parent_jeep_relation1(v7) )
    {
      LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 21);
      if ( !(_BYTE)v1 )
        LOBYTE(v1) = rf_entity_request_body_state(v7, 0x15u, 0.25);
    }
    else if ( *(_BYTE *)(a1 + 177) )
    {
      if ( *(float *)(v7 + 1812) <= 0.1000000014901161
        && *(float *)(v7 + 1812) >= -0.1000000014901161
        && *(float *)(v7 + 1820) <= 0.1000000014901161
        && *(float *)(v7 + 1820) >= -0.1000000014901161 )
      {
        LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 9);
        if ( !(_BYTE)v1 )
          LOBYTE(v1) = rf_entity_request_body_state(v7, 9u, 0.25);
      }
      else
      {
        LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 10);
        if ( !(_BYTE)v1 )
          LOBYTE(v1) = rf_entity_request_body_state(v7, 0xAu, 0.25);
      }
    }
    else if ( rf_entity_uses_fall_or_airborne_vehicle_motion((_DWORD *)v7) )
    {
      LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 14);
      if ( !(_BYTE)v1 )
        LOBYTE(v1) = rf_entity_request_body_state(v7, 0xEu, 0.25);
    }
    else if ( rf_entity_movement_is_index4_or7(v7) )
    {
      v2 = rf_vector3_set_components_return_destination(v6, 0.0, 0.0, 0.0);
      if ( !rf_vector3_components_equal((float *)(v7 + 1812), v2) || rf_entity_body_state_is_resident(v7, 18) )
      {
        v3 = rf_vector3_set_components_return_destination(v5, 0.0, 0.0, 0.0);
        LOBYTE(v1) = rf_vector3_components_not_equal((float *)(v7 + 1812), v3);
        if ( (_BYTE)v1 )
        {
          LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 19);
          if ( !(_BYTE)v1 )
            LOBYTE(v1) = rf_entity_request_body_state(v7, 0x13u, 0.25);
        }
      }
      else
      {
        LOBYTE(v1) = rf_entity_request_body_state(v7, 0x12u, 0.25);
      }
    }
    else if ( rf_vector_fast_length((float *)(v7 + 1812)) >= 0.25 )
    {
      if ( rf_entity_is_carrying_body(v7) )
      {
        LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 17);
        if ( !(_BYTE)v1 )
          LOBYTE(v1) = rf_entity_request_body_state(v7, 0x11u, 0.25);
      }
      else if ( rf_entity_weapon_is_holstered_for_actions(v7) || *(_DWORD *)(v7 + 676) == -1 )
      {
        LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 4);
        if ( !(_BYTE)v1 )
          LOBYTE(v1) = rf_entity_request_body_state(v7, 4u, 0.25);
      }
      else
      {
        LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 5);
        if ( !(_BYTE)v1 )
          LOBYTE(v1) = rf_entity_request_body_state(v7, 5u, 0.25);
      }
    }
    else if ( rf_entity_is_carrying_body(v7) )
    {
      LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 16);
      if ( !(_BYTE)v1 )
        LOBYTE(v1) = rf_entity_request_body_state(v7, 0x10u, 0.25);
    }
    else if ( rf_entity_weapon_is_holstered_for_actions(v7) || *(_DWORD *)(v7 + 676) == -1 )
    {
      LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 0);
      if ( !(_BYTE)v1 )
        LOBYTE(v1) = rf_entity_request_body_state(v7, 0, 0.25);
    }
    else
    {
      LOBYTE(v1) = rf_entity_body_state_is_resident(v7, 1);
      if ( !(_BYTE)v1 )
        LOBYTE(v1) = rf_entity_request_body_state(v7, 1u, 0.25);
    }
  }
  return v1;
}

