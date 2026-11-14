// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E0760 rf_player_resolve_view_entity_with_monitor_fallback
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): NULL player returnsNULL. First try clutter lookup(player+180); if found, pass clutter UID+44 to monitor-selected-entity helper then resolve that identifier as entity; successful result returned without own use-class test. Missing selected entity: if monitor predicate AL==1 call monitor exit2740, then unconditionally set player+180=-1. Next try direct entity lookup(current+180), return if found; otherwise clear+180=-1 and resolve own UID+20. Mutates view state on failure; no alive/inactive checks.
int __cdecl rf_player_resolve_view_entity_with_monitor_fallback(int a1)
{
  int selected_entity_identifier; // [esp+0h] [ebp-Ch]
  int v3; // [esp+4h] [ebp-8h]
  int v4; // [esp+4h] [ebp-8h]
  int v5; // [esp+8h] [ebp-4h]

  if ( !a1 )
    return 0;
  v5 = rf_clutter_find_by_uid(*(_DWORD *)(a1 + 180));
  if ( v5 )
  {
    selected_entity_identifier = rf_monitor_get_selected_entity_identifier(*(_DWORD *)(v5 + 44));
    v3 = rf_entity_resolve_handle(selected_entity_identifier);
    if ( v3 )
      return v3;
    if ( rf_player_view_target_is_monitor(a1) )
      rf_player_exit_monitor_view(a1);
    *(_DWORD *)(a1 + 180) = -1;
  }
  v4 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 180));
  if ( v4 )
    return v4;
  *(_DWORD *)(a1 + 180) = -1;
  return rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
}

