// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2530 rf_player_find_owned_riotshield_clutter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Assumes player nonNULL; resolve own entity+20, missing returnsNULL. Only if selected weapon DWORD+676 equals global911C80 (weapon registry lookup of riot shield) scan clutter ring/sentinel666D18 via+652. Return first clutter whose definition index+664 equals666B64 (registry riot_shield) and whose owner UID+48 resolves to same entity. ElseNULL. No creation, transfer or fallback to other shield owners.
int __cdecl rf_player_find_owned_riotshield_clutter(int a1)
{
  int i; // [esp+0h] [ebp-8h]
  int v3; // [esp+4h] [ebp-4h]

  v3 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !v3 )
    return 0;
  if ( *(_DWORD *)(v3 + 676) != unk_911C80 )
    return 0;
  for ( i = rf_clutter_list_head; (_UNKNOWN *)i != &unk_666D18; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 664) == unk_666B64 && rf_entity_resolve_handle(*(_DWORD *)(i + 48)) == v3 )
      return i;
  }
  return 0;
}

