// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438AC0 sub_438AC0
// UNREALRED VERIFIED [ai-set-mode-event-20260826]: Set_AI_Mode's attached-target path suppresses propagation when this predicate returns true. The shown predicate requires a non-null record, acceptance by sub_4BB430, and record +0x1430 != 0; no broader semantic label is inferred.
bool __cdecl sub_438AC0(int a1)
{
  if ( !a1 )
    return 0;
  if ( rf_object_has_player_flag(a1) )
    return *(_DWORD *)(a1 + 5168) != 0;
  return 0;
}

