// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00434010 rf_entity_is_nonplayer_sentient_or_runtime_enabled
// UNREALRED VERIFIED [trigger-use-20261021] Auto Use target class predicate is the union of runtime+0x810 flag0x10000 and authored EntityInfo+0x724 bit0x10(sentient), after player-associated exclusion. Humanoid alone is insufficient. UnrealRed currently represents only the authored sentient branch with an explicit parsed metadata flag.
// UNREALRED VERIFIED [ai-arrival-target-20261029] For direct character target admission: player-associated owner is excluded even if runtime-enabled or authored sentient. Mode15 exception is in caller0x40BA80 and must be applied after this predicate. The attached/referenced player-owner branch of0x4BCF40 remains distinct from direct controlled/player-record characters.
bool __cdecl rf_entity_is_nonplayer_sentient_or_runtime_enabled(int a1)
{
  if ( !a1 )
    return 0;
  if ( rf_object_is_player_associated(a1) == 1 )
    return 0;
  if ( rf_entity_runtime_enabled_or_resolved_attachment(a1, -1) )
    return 1;
  return (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x10) != 0;
}

