// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D190 rf_object_has_respawn_inactive_flag
// UNREALRED VERIFIED [mission-mover-occupancy-20261020] The mover occupancy filter is this exact common object flag predicate. It is not a health<=0, dying, hidden, collision-enabled, NPC activation or spatial-trigger eligibility check. A dying entity still on its list can hold/reverse a door.
// UNREALRED VERIFIED [mission-visibility-20261020] Common+0x7C mask0x4000 is the inactive state shared by initial entity creation and UnHide hide/reactivate. Runtime common identity remains present; hiding is not deferred deletion. This exact predicate also participates in mover occupancy and AI vehicle-route checks.
// UNREALRED VERIFIED [mission-unhide-20261020] Inactive is common+0x7C mask0x4000. Consumer-specific checks matter: entity/clutter radial scans and entity mover occupancy reject it; corpse radial and corpse mover endpoint scans do not. Do not replace these with one blanket damage/occupancy veto.
bool __cdecl rf_object_has_respawn_inactive_flag(int a1)
{
  return a1 && (*(_DWORD *)(a1 + 124) & 0x4000) != 0;
}

