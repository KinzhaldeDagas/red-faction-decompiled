// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F56B0 rf_level_state_restore_runtime_snapshot
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Reset deferred object-id queue count0x88E7C8=0, restore specialized event families at matching snapshot offsets/count bytes, then generic headers, merge shared goals and process deleted saved identifiers. Invoke remaining runtime-manager receivers, finally restore shared seconds-clock bits0x6FC428 from snapshot+0x24. Does NOT apply queued object-id writes; caller separately invokes0x4F5A30 afterward. Does not reset shared-goal table before merge.
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Manager restore routing clarification: input53984/100116=>trigger restore0x506410;69728/100118=>push regions0x478960;76584/100120=>new projectile replay0x510DA0;77800/100121=>blood-mark free-slot replay0x43E540;99208/100124=>glass geometry-removal ledger0x4CA750. Trigger/mover/region matching and blood/projectile creation are distinct restoration policies; this root does not imply every family is reconstructed identically.
int __cdecl rf_level_state_restore_runtime_snapshot(int a1)
{
  unk_88E7C8 = 0;
  rf_event_state_restore_goals(a1 + 64, *(unsigned __int8 *)(a1 + 100104));
  rf_event_state_restore_alarm_sirens(a1 + 256, *(unsigned __int8 *)(a1 + 100105));
  rf_event_state_restore_when_dead(a1 + 448, *(unsigned __int8 *)(a1 + 100106));
  rf_event_state_restore_cyclic_timers(a1 + 928, *(unsigned __int8 *)(a1 + 100107));
  rf_event_state_restore_invulnerability(a1 + 1312, *(unsigned __int8 *)(a1 + 100108));
  rf_event_state_restore_generic_headers(a1 + 1504, *(unsigned __int8 *)(a1 + 100109));
  rf_goal_state_restore_shared_names(a1 + 69984, *(unsigned __int8 *)(a1 + 100119));
  rf_event_state_delete_saved_identifiers(a1 + 99976, *(unsigned __int8 *)(a1 + 100126));
  rf_bolt_emitter_snapshot_restore(a1 + 2144, *(unsigned __int8 *)(a1 + 100110));
  rf_entity_snapshot_restore_registry(
    a1 + 2272,
    *(unsigned __int8 *)(a1 + 100112),
    a1 + 99720,
    *(unsigned __int8 *)(a1 + 100125));
  rf_item_snapshot_restore(a1 + 36576, *(unsigned __int8 *)(a1 + 100113));
  rf_clutter_snapshot_restore(a1 + 41696, *(unsigned __int16 *)(a1 + 100114));
  rf_trigger_snapshot_restore(a1 + 53984, *(unsigned __int8 *)(a1 + 100116));
  rf_mover_snapshot_restore(a1 + 57440, *(unsigned __int8 *)(a1 + 100117));
  rf_push_region_snapshot_restore(a1 + 69728, *(unsigned __int8 *)(a1 + 100118));
  rf_world_decal_snapshot_restore(a1 + 70184, *(unsigned __int8 *)(a1 + 100111));
  rf_projectile_snapshot_restore(a1 + 76584, *(unsigned __int8 *)(a1 + 100120));
  rf_blood_surface_mark_snapshot_restore(a1 + 77800, *(unsigned __int8 *)(a1 + 100121));
  rf_corpse_restore_animation_state(a1 + 78088, *(unsigned __int8 *)(a1 + 100122));
  rf_glass_snapshot_restore_removed_geometry_ids(a1 + 99208, *(unsigned __int8 *)(a1 + 100124));
  dword_6FC428 = *(int *)(a1 + 36);
  return a1;
}

