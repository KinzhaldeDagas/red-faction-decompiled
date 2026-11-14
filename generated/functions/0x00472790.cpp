// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00472790 rf_item_contact_try_pickup
// UNREALRED VERIFIED [item-pickups-20261028]: If float+468==0 or object handle+484 cannot resolve, returns2. In non-MP/non-splitscreen, non-player object returns0 without pickup. Otherwise if resolved object dword+36 is zero, calls rf_item_pickup_dispatch(item,object,1,0); returns0 regardless pickup result. Called by object-list update and contact dispatcher. Does not assume unresolved object is always entity.
// UNREALRED VERIFIED [combat-ammo-roles-pickups-20261111]: Physical item contact: contactindicatorF32+468==0 orunresolvedcommonhandle+484=>return2; otherwise SP(noMP/split) NONPLAYER returns0beforepickup. MP/split permitsnonplayer subjectcommonTYPE exactly0, then473940(item,entity,LOSflag1,networkoverride0). Thus OriginalSPNPC contactrejection is native, but MP/splitNPC mustnot be sent to an AltAI-only pickup adapter.
int __thiscall rf_item_contact_try_pickup(int this)
{
  int v3; // [esp+8h] [ebp-4h]

  if ( *(float *)(this + 468) == 0.0 )
    return 2;
  v3 = rf_object_resolve_handle(*(_DWORD *)(this + 484));
  if ( !v3 )
    return 2;
  if ( !(rf_splitscreen_runtime_active | rf_multiplayer_runtime_mode) && !rf_object_has_player_flag(v3) )
    return 0;
  if ( !*(_DWORD *)(v3 + 36) )
    rf_item_pickup_dispatch((_DWORD *)this, v3, 1, 0);
  return 0;
}

