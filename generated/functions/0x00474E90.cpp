// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474E90 rf_item_apply_ammo_pickup
// UNREALRED VERIFIED [item-pickups-20261028]: MP mode==1 without server authority returns0 before resolutions. Missing entity/item returns-1; rejects reserve>=weapon max and rejects0x4EF770()==1 except weapon globals0x911CBC/0x911C6C. Non-MP/nonsplitscreen scales quantity by table0x661294[index0x6612A4], adding0.5 then truncating; flamethrower/riot stick use hundred-unit rounding. Caps against remaining reserve when ammo-type>=0, then for those two weapons enforces minimum100 AFTER cap. Calls rf_entity_add_weapon_ammo. Message quantity converts those units back with /100,+0.5,trunc,min1. No lower clamp for other weapons and no local weapon-index validation. Returns0 after grant.
// UNREALRED VERIFIED [combat-ammo-roles-pickups-20261111]: Ammo-only pickup: MPmode1clientreturns0 early; resolvesentity/item else-1; rejectRAWreserve[AmmoID]>=receivingweaponactiveMax, then4EF770specialgate excepttwohandgunIDs. SPnonsplit scalesrawsignedquantity via661294[difficulty],+0.5/trunc; flame/riotstick hundred-unitrounding. IfAmmoID>=0 capsquantityagainstremainingreserve; specialtwo enforceMIN100 AFTERcap.4365F0 receivesactualquantity; its pending correction is receivingWEAPONid-gated. Messages areseparate. No universalpositivequantity clamp or pool-name matching.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Ammo scale661294 exactF32(1.5,0.8999999761581421,0.800000011920929,0.6000000238418579). MP/split bothzero scales before remaining-cap then flame/riot minimum100 AFTER cap. Receiving weapon active maximum and dispatcher473940 MPserver precheck SPmax+25C are different operands.
int __cdecl rf_item_apply_ammo_pickup(int a1, int a2, int a3, int a4)
{
  int v5; // [esp+4h] [ebp-14h]
  int v6; // [esp+8h] [ebp-10h]
  int v7; // [esp+Ch] [ebp-Ch]
  int v8; // [esp+10h] [ebp-8h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    return 0;
  v7 = rf_entity_resolve_handle(a1);
  if ( !v7 )
    return -1;
  v6 = rf_item_resolve_handle(a2);
  if ( !v6 )
    return -1;
  if ( *(_DWORD *)(v7 + 672 + 4 * dword_912024[340 * a3] + 12) >= unk_912260[340 * a3] )
    return -1;
  if ( sub_4EF770() == 1 && a3 != dword_911CBC && a3 != unk_911C6C )
    return -1;
  if ( !rf_multiplayer_runtime_mode && !rf_splitscreen_runtime_active )
  {
    if ( a3 == rf_weapon_id_flamethrower || a3 == rf_weapon_id_riot_stick )
      a4 = 100 * (int)((double)a4 / 100.0 * flt_661294[dword_6612A4] + 0.5);
    else
      a4 = (int)((double)a4 * flt_661294[dword_6612A4] + 0.5);
  }
  v8 = a4;
  v5 = dword_912024[340 * a3];
  if ( v5 >= 0 )
    v8 = rf_int_min_signed(a4, unk_912260[340 * a3] - *(_DWORD *)(v7 + 4 * v5 + 684));
  if ( (a3 == rf_weapon_id_flamethrower || a3 == rf_weapon_id_riot_stick) && v8 < 100 )
    v8 = 100;
  rf_entity_add_weapon_ammo(v7, a3, v8);
  if ( a3 == rf_weapon_id_flamethrower || a3 == rf_weapon_id_riot_stick )
  {
    v8 = (int)((double)v8 / 100.0 + 0.5);
    if ( v8 < 1 )
      v8 = 1;
  }
  if ( rf_object_has_player_flag(v7) )
    rf_item_show_local_pickup_message(v7, *(_DWORD *)(v6 + 660), v8, 0);
  return 0;
}

