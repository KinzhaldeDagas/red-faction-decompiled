// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A7580 rf_multiplayer_apply_received_weapon_fire
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): cdecl(entity,weapon,position,matrix,mode LOW BYTE). Runtime==1 AND authority0 requires unguarded localPlayer.net4608 stateDWORD12==1 or2; all other
// states bypass this gate. Stops current entity weapon firing first. If (flameFlag(weapon) AND mode==EXACT1) OR Grenade predicate5119F0 OR remote-charge flag, creates
// projectile(weapon,entityHandle44,position,matrix,mode,0), calls43B1B0(entity,currentWeapon676,mode), and if created projectile AND Grenade AND mode1 sets projectile DWORD680
// bit0x10. Else detonator flag marks owned flag40 projectiles; otherwise calls431FD0(entity,0,mode,NULL,position,matrix). Finally always calls fire-publication
// wrapper4A8390(entity,position,matrix,weapon,mode) on admitted paths. No own weapon-bound, health, position/orientation finite or source checks; helper delegates own validation.
// Return register incidental.
int __cdecl rf_multiplayer_apply_received_weapon_fire(int a1, int a2, float *a3, float *a4, char a5)
{
  int result; // eax
  int runtime; // [esp+0h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode != 1
    || rf_multiplayer_server_authority
    || (result = *(_DWORD *)(rf_local_fpgun_player + 4608), *(_DWORD *)(result + 12) == 2)
    || *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 12) == 1 )
  {
    rf_entity_stop_weapon_firing(*(_DWORD *)(a1 + 44), *(_DWORD *)(a1 + 676));
    if ( rf_weapon_has_flame_flag(a2) && a5 == 1 || sub_5119F0(a2) || rf_weapon_has_remote_charge_flag(a2) )
    {
      runtime = rf_projectile_create_runtime(a2, *(_DWORD *)(a1 + 44), (int)a3, (int)a4, a5, 0);
      rf_entity_consume_player_weapon_ammo_after_fire(a1, *(_DWORD *)(a1 + 676), a5);
      if ( runtime && sub_5119F0(a2) && a5 == 1 )
        *(_DWORD *)(runtime + 680) |= 0x10u;
    }
    else if ( rf_weapon_has_detonator_flag(a2) )
    {
      rf_entity_mark_owned_flag40_projectiles(a1);
    }
    else
    {
      sub_431FD0(*(float *)&a1, 0, a5, nullptr, a3, a4);
    }
    return rf_multiplayer_publish_weapon_fire(a1, a3, a4, a2, a5);
  }
  return result;
}

