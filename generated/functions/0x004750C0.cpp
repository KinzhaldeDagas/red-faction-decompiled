// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004750C0 rf_inventory_apply_weapon_pickup
// UNREALRED VERIFIED [combat-ammo-roles-pickups-20261111]: Weaponpickup originalcounterchain: rejectnegativeweapon/missingentity/item; authoritativeorSP rejectsowned+RAWreserve>=activeMax andspecial4EF770gate. Alreadyowned scalesSPquantity/capsbyremaining (specialflame/riotminimum100aftercap), calls4365F0. Newlyowned403AB0(quantity), thenonlycaller-specific companions: machinepistol=>specialsamequantity;remotecharge=>detonatorquantity0;railgun=>4365F0(rand%4+1). Constructor/default403AB0 mustnot fabricate thesecompanions. Afterward fills absent selectedprimary onlyforprimarysection, secondaryonlysecondarysection. Localplayer autoswitch/preferences separatefrom forcedAI4014F0 selector. Return0 success, -1reject; do not confuse statuswithtruthygrant.
int __cdecl rf_inventory_apply_weapon_pickup(int a1, int a2, int a3, int a4)
{
  int v5; // eax
  int v6; // [esp+0h] [ebp-3Ch]
  int v7; // [esp+8h] [ebp-34h]
  _DWORD *v8; // [esp+Ch] [ebp-30h]
  int v9; // [esp+18h] [ebp-24h]
  int v10; // [esp+20h] [ebp-1Ch]
  int v11; // [esp+24h] [ebp-18h]
  char v12; // [esp+2Bh] [ebp-11h]
  int v13; // [esp+2Ch] [ebp-10h]
  int *v14; // [esp+30h] [ebp-Ch]
  int *v15; // [esp+34h] [ebp-8h]
  _DWORD *v16; // [esp+38h] [ebp-4h]

  if ( a3 < 0 )
    return -1;
  v14 = (int *)rf_entity_resolve_handle(a1);
  if ( !v14 )
    return -1;
  v13 = rf_item_resolve_handle(a2);
  if ( !v13 )
    return -1;
  v15 = v14 + 168;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    goto LABEL_16;
  if ( sub_403D00((int)v15, a3) && v15[dword_912024[340 * a3] + 3] >= unk_912260[340 * a3] )
    return -1;
  if ( sub_4EF770() == 1 && a3 != dword_911CBC && a3 != unk_911C6C )
    return -1;
LABEL_16:
  v12 = 1;
  if ( sub_403D00((int)v15, a3) )
  {
    if ( !rf_multiplayer_runtime_mode && !rf_splitscreen_runtime_active )
    {
      if ( a3 == rf_weapon_id_flamethrower || a3 == rf_weapon_id_riot_stick )
        a4 = 100 * (int)((double)a4 / 100.0 * flt_661294[dword_6612A4] + 0.5);
      else
        a4 = (int)((double)a4 * flt_661294[dword_6612A4] + 0.5);
    }
    v11 = a4;
    v10 = dword_912024[340 * a3];
    if ( v10 >= 0 )
      v11 = rf_int_min_signed(a4, unk_912260[340 * a3] - v14[v10 + 171]);
    if ( (a3 == rf_weapon_id_flamethrower || a3 == rf_weapon_id_riot_stick) && v11 < 100 )
      v11 = 100;
    rf_entity_add_weapon_ammo((int)v14, a3, v11);
    if ( v11 > 0 )
    {
      v9 = rf_item_definition_find_by_ammo_weapon(a3);
      if ( v9 == -1 )
        v9 = rf_item_definition_find_by_given_weapon(a3);
      if ( v9 == -1 )
        v9 = rf_item_definition_find_by_ammo_weapon(dword_911CBC);
      if ( v9 != -1 )
      {
        if ( a3 == rf_weapon_id_flamethrower || a3 == rf_weapon_id_riot_stick )
        {
          v6 = unk_912088[340 * a3] > 0 ? unk_912088[340 * a3] : 100;
          v11 = (int)((double)v11 / (double)v6 + 0.5);
          if ( v11 < 1 )
            v11 = 1;
        }
        if ( rf_object_has_player_flag((int)v14) )
          rf_item_show_local_pickup_message((int)v14, *(_DWORD *)(v13 + 660), v11, v11 > 0);
      }
    }
  }
  else
  {
    v12 = 0;
    rf_entity_inventory_grant_weapon(v15, a3, a4);
    if ( a3 == dword_911CC4 )
    {
      rf_entity_inventory_grant_weapon(v15, unk_911C98, a4);
    }
    else if ( a3 == dword_911C78 )
    {
      rf_entity_inventory_grant_weapon(v15, unk_911C88, 0);
    }
    else if ( a3 == unk_911CE0 )
    {
      v5 = rand() % 4;
      rf_entity_add_weapon_ammo((int)v14, a3, v5 + 1);
    }
    if ( rf_object_has_player_flag((int)v14) )
      rf_item_show_local_pickup_message((int)v14, *(_DWORD *)(v13 + 660), a4, 0);
  }
  if ( !unk_9120A8[340 * a3] && v14[169] < 0 )
  {
    if ( rf_object_has_player_flag((int)v14) )
    {
      v8 = sub_4DD720(v14[11]);
      rf_player_request_weapon_switch((int)v8, a3, 0, 0);
    }
    else
    {
      v14[169] = a3;
      rf_entity_restore_action_tables_and_apply_weapon_overrides(v14[168], v14[169]);
    }
  }
  if ( unk_9120A8[340 * a3] == 1 && v14[170] < 0 )
    v14[170] = a3;
  v16 = sub_4DD720(v14[11]);
  if ( v16
    && v16 == (_DWORD *)rf_local_fpgun_player
    && v14[169] != -1
    && *((_BYTE *)v16 + 3904) == 1
    && !v12
    && (!rf_weapon_can_damage_self(a3) || !*((_BYTE *)v16 + 3905)) )
  {
    v7 = rf_player_weapon_preference_rank((int)v16, a3);
    if ( v7 < rf_player_weapon_preference_rank((int)v16, v14[169]) )
      rf_player_request_weapon_switch((int)v16, a3, 0, 0);
  }
  return 0;
}

