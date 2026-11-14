// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040DB70 rf_entity_auto_trigger_use_candidate
// UNREALRED VERIFIED [trigger-use-20261021] The formerly opaque common+0x1F8 state is the authored/runtime friendliness code: RFL entity loader481B40 copies it and4BBF50 (Set_Friendliness writer) writes the supplied code unchanged. Exact values1 or2 are accepted, after nonplayer sentient/runtime-enabled and alive predicates. Do not reinterpret as a broader faction/team relation.
bool __cdecl rf_entity_auto_trigger_use_candidate(int a1)
{
  if ( !a1 )
    return 0;
  if ( !rf_entity_is_nonplayer_sentient_or_runtime_enabled(a1) )
    return 0;
  if ( rf_entity_is_dead(a1) )
    return 0;
  return *(_DWORD *)(a1 + 504) == 1 || *(_DWORD *)(a1 + 504) == 2;
}

