// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E1FE0 rf_player_autoswitch_exhausted_weapon
// UNREALRED VERIFIED [weapon-autoselect] Detects an unusable current weapon, invokes the preferred usable-weapon scan, and requests that switch. Player+0xF40 gates ordinary exhaustion autoswitch.
// UNREALRED VERIFIED [weapon-autoselect] Detects an unusable current weapon, invokes the preferred usable-weapon scan, and requests that switch. Player+0xF40 gates ordinary exhaustion autoswitch, while an empty Grenade slot always recovers.
void __cdecl rf_player_autoswitch_exhausted_weapon(int a1, char a2)
{
  signed int usable_preferred_weapon; // [esp+0h] [ebp-28h]
  char v3; // [esp+Fh] [ebp-19h]
  int v4; // [esp+10h] [ebp-18h]
  _DWORD *v5; // [esp+18h] [ebp-10h]
  bool v6; // [esp+1Fh] [ebp-9h]
  signed int selected_weapon_and_resolve_mesh; // [esp+20h] [ebp-8h]
  int v8; // [esp+24h] [ebp-4h]

  v8 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( v8 )
  {
    selected_weapon_and_resolve_mesh = rf_player_get_selected_weapon_and_resolve_mesh((_DWORD *)a1);
    if ( selected_weapon_and_resolve_mesh >= 0
      && (*(_BYTE *)(a1 + 3904) || selected_weapon_and_resolve_mesh == rf_weapon_index_grenade)
      && (!rf_entity_is_parent_jeep_relation1(v8) || !a2) )
    {
      v6 = 1;
      if ( selected_weapon_and_resolve_mesh == unk_911C88 )
        v6 = rf_player_has_live_designated_projectile(a1) == 0;
      if ( unk_912260[340 * selected_weapon_and_resolve_mesh] <= 0 || selected_weapon_and_resolve_mesh == dword_911C78 )
        v6 = 0;
      if ( v6 )
      {
        v4 = v8;
        v5 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(v8 + 512));
        if ( v5 && (rf_object_get_use_classification(v5) == 4 || rf_object_get_use_classification(v5) == 1) )
          v4 = (int)v5;
        if ( *(_DWORD *)(v4 + 4 * selected_weapon_and_resolve_mesh + 812)
           + sub_4391D0(v4, selected_weapon_and_resolve_mesh) <= 0
          && !rf_weapon_is_melee(selected_weapon_and_resolve_mesh) )
        {
          v3 = 0;
          if ( selected_weapon_and_resolve_mesh != dword_911CC4 || rf_multiplayer_runtime_mode )
          {
            if ( selected_weapon_and_resolve_mesh != unk_911C98 )
            {
              if ( rf_entity_has_attached_use_turret(v8)
                || rf_entity_has_attached_use_vehicle(v8)
                || rf_entity_is_parent_jeep_relation1(v8) )
              {
                rf_hud_message_enqueue_expand_tokens_and_rearm_head("Out of ammunition", 0, 0, nullptr);
              }
              else
              {
                v3 = 1;
              }
              goto LABEL_32;
            }
            if ( *(_DWORD *)(v4 + 4 * dword_911CC4 + 812) + sub_4391D0(v4, dword_911CC4) > 0 )
              goto LABEL_22;
            v3 = 1;
          }
          else
          {
            if ( *(_DWORD *)(v4 + 4 * unk_911C98 + 812) + sub_4391D0(v4, unk_911C98) > 0 )
            {
LABEL_22:
              rf_player_handle_weapon_fire_input(a1, 1, 1);
              goto LABEL_32;
            }
            v3 = 1;
          }
LABEL_32:
          if ( v3 )
          {
            usable_preferred_weapon = rf_player_find_usable_preferred_weapon(a1);
            if ( usable_preferred_weapon >= 0 )
              rf_player_request_weapon_switch(a1, usable_preferred_weapon, 1, 0);
          }
        }
      }
    }
  }
}

