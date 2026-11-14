// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004377E0 rf_object_player_flag_without_player_context
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(record), canonical AL0/1.4BB430 player-flag predicate ANY nonzero required, otherwise0 and second helper
// skipped. Then438AC0 ANY nonzero returns0; zero returns1. Preserves two helper calls/short circuit; stable ordinary entity case is player-flag set with no Player pointer5168, not a
// local/remote/authority classification. NULL yields0 through first helper. No independent object-type/pointer/attachment validation or state mutation.
bool __cdecl rf_object_player_flag_without_player_context(int a1)
{
  return rf_object_has_player_flag(a1) && !sub_438AC0(a1);
}

