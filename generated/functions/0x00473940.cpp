// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00473940 rf_item_pickup_dispatch
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Mover container gate: common item flags +0x2BC bit1 causes immediate pickup rejection before inventory callbacks, respawn or grant logic. Mover bind0x48AC40 sets this bit and arrival0x488B30 clears/sets it by direction. This is pickup eligibility, not removal or an instruction to hide the item.
// UNREALRED VERIFIED [mission-mover-effects-20261013] The mover-owned item-disable bit is checked before pickup grant. Keep this predicate independent of active/respawn and world pause in the port; visual hiding or pausing respawn timers is not equivalent.
// UNREALRED VERIFIED [combat-ammo-roles-pickups-20261111]: Beforecounterpickup: MPmode1clientwithoutoverride rejects; mover itemflag+2BCbit1 rejects; attached-use-vehicle/turret ordeadreceiverreject. ServerMP applies weaponsstay/playerseen/team/specialmetadata gates and AmmoFor receivingweaponMPmax rawreserve gate. RequestedLOS uses472790 flag1 beforeanygrant. Customhandler atdefinition+72 or474D10 nonzero status=>reject. Successfulnonplayerwithoutplayerentry invokes473800. Counter mutation,status and itemhide/delete/respawn followoriginalprefixes; nogenericnearby/distance pickup or immediatehide substitutes for thesegates.
void __cdecl rf_item_pickup_dispatch(_DWORD *a1, int a2, char a3, char a4)
{
  int v4; // [esp+4h] [ebp-20h]
  int v5; // [esp+8h] [ebp-1Ch]
  int v6; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h] BYREF
  int v8; // [esp+14h] [ebp-10h]
  int v9; // [esp+18h] [ebp-Ch] BYREF
  int v10; // [esp+1Ch] [ebp-8h]
  int v11; // [esp+20h] [ebp-4h] BYREF

  v8 = a1[165];
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority && !a4
    || (a1[175] & 1) != 0
    || rf_entity_has_attached_use_vehicle(a2)
    || rf_entity_has_attached_use_turret(a2)
    || rf_entity_is_dead(a2) )
  {
    return;
  }
  v10 = (int)sub_4DD720(*(_DWORD *)(a2 + 44));
  if ( rf_multiplayer_runtime_mode != 1 || !v10 )
  {
LABEL_27:
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
    {
      if ( a2
        && v10
        && (rf_multiplayer_game_flags & 0x10) != 0
        && (a1[175] & 8) == 0
        && *(_DWORD *)(a1[165] + 64) != -1
        && *(_DWORD *)(a1[165] + 64) != rf_weapon_id_shoulder_cannon
        && *(_BYTE *)(v10 + a1[166] + 80) == 1 )
      {
        return;
      }
      if ( *(_DWORD *)(a1[165] + 60) != -1 )
      {
        v5 = dword_912024[340 * *(_DWORD *)(a1[165] + 60)];
        if ( a2 )
        {
          if ( v5 >= 0 && *(_DWORD *)(a2 + 4 * v5 + 684) >= unk_91225C[340 * *(_DWORD *)(a1[165] + 60)] )
            return;
        }
      }
      v6 = sub_4ACFF0((int)(a1 + 167));
      if ( v6 == 2 && a2 && *(float *)(a2 + 56) >= 200.0 )
        return;
      if ( v6 == 3 && a2 && *(float *)(a2 + 52) >= 200.0 )
        return;
    }
    if ( a3 == 1 && rf_geometry_segment_is_obstructed((int)(a1 + 15), a2 + 2004, 1, 0) == 1 )
      return;
    v7 = -1;
    v9 = -1;
    v11 = -1;
    if ( *(_DWORD *)(v8 + 72) )
    {
      if ( (*(int (__cdecl **)(_DWORD, _DWORD, _DWORD))(v8 + 72))(*(_DWORD *)(a2 + 44), a1[11], a1[169]) )
        return;
    }
    else if ( rf_item_apply_default_weapon_or_ammo_pickup(*(_DWORD *)(a2 + 44), a1[11], a1[169], &v7, &v9, &v11) )
    {
      return;
    }
    if ( v10 )
      *(_BYTE *)(v10 + a1[166] + 80) = 1;
    else
      rf_item_pickup_maybe_resume_ai_combat(a2);
    if ( (int)a1[171] < 0 )
      goto LABEL_66;
    if ( (int)a1[171] <= 0 )
      goto LABEL_68;
    if ( rf_multiplayer_runtime_mode )
    {
      if ( *(_DWORD *)(a1[165] + 64) != -1 && *(_DWORD *)(a1[165] + 64) != rf_weapon_id_shoulder_cannon )
      {
        if ( (a1[175] & 8) == 0 )
        {
          if ( (rf_multiplayer_game_flags & 0x10) == 0 )
          {
            rf_object_mark_hidden_inactive((int)a1);
            rf_replicator_arm_milliseconds(a1 + 172, a1[171]);
          }
          goto LABEL_68;
        }
        goto LABEL_66;
      }
      if ( (a1[175] & 8) != 0 )
      {
LABEL_66:
        rf_object_mark_for_deferred_delete((int)a1);
        goto LABEL_68;
      }
    }
    rf_object_mark_hidden_inactive((int)a1);
    rf_replicator_arm_milliseconds(a1 + 172, a1[171]);
LABEL_68:
    if ( rf_multiplayer_runtime_mode == 1
      && rf_multiplayer_server_authority == 1
      && (rf_multiplayer_game_flags & 0x10) != 0
      && (a1[175] & 8) == 0 )
    {
      v4 = rf_item_resolve_pickup_sound_index((int)a1);
      if ( v4 >= 0 )
        rf_server_send_proximity_packet52(v10, v4, (float *)a1 + 15, 10.0);
    }
    rf_item_play_pickup_sound((int)a1);
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
    {
      if ( (a1[175] & 8) != 0 )
      {
        rf_multiplayer_send_item_apply_packet40(0, a1[11], *(_DWORD *)(a2 + 44), v7, v9, v11);
      }
      else if ( v10 != rf_local_fpgun_player )
      {
        rf_multiplayer_send_item_apply_packet40(v10, a1[11], *(_DWORD *)(a2 + 44), v7, v9, v11);
      }
    }
    return;
  }
  if ( (a1[175] & 0x80) != 0 || (a1[175] & 0x100) != 0 )
  {
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      rf_ctf_capture_at_base(v10, (int)a1);
    return;
  }
  if ( ((a1[175] & 0x20) == 0 || rf_ctf_red_carrier_get() != v10)
    && ((a1[175] & 0x40) == 0 || rf_ctf_blue_carrier_get() != v10) )
  {
    if ( (a1[175] & 0x20) != 0 || (a1[175] & 0x40) != 0 )
    {
      if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
        rf_ctf_flag_touch(v10, (int)a1);
      return;
    }
    goto LABEL_27;
  }
}

