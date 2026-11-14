// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00403C20 sub_403C20
// UNREALRED VERIFIED [combat-selected-drop-20261111]: Selected inventory removal helper only clears AI+18C[weaponID] when valid; loaded counterAI+8C and shared reserveAI+0C untouched. Conditional associatedlocalplayer notification is separate. Native logical ownership must remain distinct from stored weapon/ammo records; deleting host array record loses residual magazine state.
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Ownership removal only clearsbyteAI+18C[ID] for0..63 and may notifyassociatedlocalplayer forriotshield; preserves weapon-loaded and all ammo-reserve values. Drop439220 separately writes primary-1. No host array deletion, sharedpool reset or secondary clear is implied.
void __cdecl sub_403C20(int a1, unsigned int a2)
{
  int i; // [esp+4h] [ebp-4h]

  if ( a2 < 0x40 )
  {
    *(_BYTE *)(a2 + a1 + 396) = 0;
    for ( i = 0; i < rf_local_player_entry_count; ++i )
    {
      if ( a1 == rf_player_resolve_view_entity_with_monitor_fallback(rf_local_player_entries[i]) + 672
        && a2 == unk_911C80 )
      {
        rf_model_mesh_decal_slots_clear25(rf_local_player_entries[i]);
      }
    }
  }
}

