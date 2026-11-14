// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050FC20 rf_entity_grant_all_player_weapons_and_refill_ammo
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): NULL argument selects current splitscreen entity via4AEFA0, otherwise primary entity681E38. Returns if entity or computed entity+672 inventory base is NULL. First loops FIXED64 records, granting every flags+612 player_wep(80h) with quantity-1. Then loops signed global weapon count911C68: player_wep with nonnegative ammo index+36 writes record DWORD+608 to inventory+12+4*ammo_index. Resolves linked entity UID+512; when use-vehicle predicate equals1, loops global count again and refills its +684+4*ammo_index for ALL records with nonnegative ammo index, without player_wep filter. No ammo-index upper bound/deduplication; later shared-index records overwrite earlier values.
// Grant results ignored.
void __cdecl rf_entity_grant_all_player_weapons_and_refill_ammo(int selected_player_entity)
{
  int *v1; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  int j; // [esp+4h] [ebp-8h]
  int k; // [esp+4h] [ebp-8h]
  _DWORD *v5; // [esp+8h] [ebp-4h]

  if ( !selected_player_entity )
  {
    if ( rf_splitscreen_runtime_active )
      selected_player_entity = rf_splitscreen_get_selected_player_entity();
    else
      selected_player_entity = dword_681E38;
  }
  if ( selected_player_entity )
  {
    v1 = (int *)(selected_player_entity + 672);
    if ( selected_player_entity != -672 )
    {
      for ( i = 0; i < 64; ++i )
      {
        if ( (unk_912264[340 * i] & 0x80) != 0 )
          rf_entity_inventory_grant_weapon(v1, i, -1);
      }
      for ( j = 0; j < dword_911C68; ++j )
      {
        if ( (unk_912264[340 * j] & 0x80) != 0 && dword_912024[340 * j] >= 0 )
          v1[dword_912024[340 * j] + 3] = unk_912260[340 * j];
      }
      v5 = (_DWORD *)rf_entity_resolve_handle(*(_DWORD *)(selected_player_entity + 512));
      if ( v5 )
      {
        if ( rf_object_is_use_vehicle(v5) )
        {
          for ( k = 0; k < dword_911C68; ++k )
          {
            if ( dword_912024[340 * k] >= 0 )
              v5[dword_912024[340 * k] + 171] = unk_912260[340 * k];
          }
        }
      }
    }
  }
}

