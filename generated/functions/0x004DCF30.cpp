// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DCF30 rf_player_resolve_entity_inventory
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl player pointer. NULL player or failed entity-handle20 resolution returns0; otherwise returns entity+672 inventory/AI member address. Does not validate selected weapon, alive/player classification or ownership and performs no writes.
int __cdecl rf_player_resolve_entity_inventory(int a1)
{
  int v2; // [esp+0h] [ebp-4h]

  if ( !a1 )
    return 0;
  v2 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( v2 )
    return v2 + 672;
  else
    return 0;
}

