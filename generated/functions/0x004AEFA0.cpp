// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AEFA0 rf_splitscreen_get_selected_player_entity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Noarg. Dereference global selected player7B25D8 then DWORD player+20, call entity_resolve_handle, return entity orNULL from delegate. No NULL-selected-player
// guard, default-first-player fallback or update of selection.
int rf_splitscreen_get_selected_player_entity()
{
  return rf_entity_resolve_handle(*(_DWORD *)(dword_7B25D8 + 20));
}

