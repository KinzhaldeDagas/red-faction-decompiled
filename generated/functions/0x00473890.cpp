// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00473890 rf_item_resolve_pickup_sound_index
// UNREALRED VERIFIED [event-item-dispatch-20261028]: Null item returns-1. If definition at item+660 has explicit sound index at+40 other than-1, returns it. Otherwise returns0 if both Ammo For(+60) and Gives Weapon(+64) equal-1; returns12 when either weapon-related field is present. Does not load or play sound.
int __cdecl rf_item_resolve_pickup_sound_index(int a1)
{
  if ( !a1 )
    return -1;
  if ( *(_DWORD *)(*(_DWORD *)(a1 + 660) + 40) != -1 )
    return *(_DWORD *)(*(_DWORD *)(a1 + 660) + 40);
  if ( *(_DWORD *)(*(_DWORD *)(a1 + 660) + 60) == -1 && *(_DWORD *)(*(_DWORD *)(a1 + 660) + 64) == -1 )
    return 0;
  return 12;
}

