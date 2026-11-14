// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC940 rf_event_drop_weapon_apply
// UNREALRED VERIFIED [weapon-events-20260826]: Event-table case 81 (Drop_Weapon). Iterates event +0x29C and admits only entity-resolver results. A selected owner first calls sub_422A40 and rf_character_drop_selected_weapon_item(owner, 0). For every resolved owner, the two type-4 identifiers at +0x145C/+0x1460 are resolved, marked for deferred deletion when present, and reset to -1; all 64 ownership bytes at +0x42C are cleared; selected indices +0x2A4/+0x2A8 are reset to -1.
int __cdecl rf_event_drop_weapon_apply(int a1)
{
  int result; // eax
  int *v2; // eax
  int k; // [esp+0h] [ebp-14h]
  unsigned int *v4; // [esp+4h] [ebp-10h]
  int j; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]
  int v7; // [esp+10h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v4 = (unsigned int *)rf_entity_resolve_handle(*v2);
    if ( v4 )
    {
      if ( v4[169] != -1 )
      {
        rf_entity_stop_weapon_firing(v4[11], v4[169]);
        rf_character_drop_selected_weapon_item(v4, 0);
      }
      for ( j = 0; j < 2; ++j )
      {
        v7 = rf_clutter_find_by_uid(v4[j + 1303]);
        if ( v7 )
        {
          rf_object_mark_for_deferred_delete(v7);
          v4[j + 1303] = -1;
        }
      }
      for ( k = 0; k < 64; ++k )
        *((_BYTE *)v4 + k + 1068) = 0;
      v4[169] = -1;
      v4[170] = -1;
    }
  }
  return result;
}

