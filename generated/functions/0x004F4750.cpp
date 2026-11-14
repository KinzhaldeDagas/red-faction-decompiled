// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F4750 rf_level_state_collect_runtime_snapshot
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Pack runtime memory snapshot managers in fixed order. Event families: goals/sirens/When_Dead/cyclic/invulnerability/generic at buffer offsets64/256/448/928/1312/1504, byte counts100104..100109. Shared goals at69984 count100119 are skipped by setting count0 when global0x88E7CC nonzero. Deleted saved identifiers at99976 count100126. Other managers include entities/items/clutter/projectiles/bolts/movers/lights/decals/corpses and GeoMod records; copies32*GeoMod count bytes to95112 and exports byte count100123. This is in-memory collection, no file write or successful reload claim.
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Manager routing clarification to earlier broad summary: snapshot53984/count100116 is TRIGGER records0x5062F0;69728/count100118 is PUSH REGION state0x4788E0;76584/count100120 is PROJECTILES0x510BC0;77800/count100121 is BLOOD SURFACE MARKS0x43E480;99208/count100124 is GLASS REMOVED-GEOMETRY IDS0x4CA700. These are distinct payload families, not interchangeable projectile/light/particle labels. Other prior offsets remain as observed; no file-write guarantee implied.
char __cdecl rf_level_state_collect_runtime_snapshot(_BYTE *a1)
{
  float v2[3]; // [esp+0h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-Ch] BYREF

  rf_event_state_collect_goals((int)(a1 + 64), a1 + 100104);
  rf_event_state_collect_alarm_sirens((int)(a1 + 256), a1 + 100105);
  rf_event_state_collect_when_dead((int)(a1 + 448), a1 + 100106);
  rf_event_state_collect_cyclic_timers((int)(a1 + 928), a1 + 100107);
  rf_event_state_collect_invulnerability((int)(a1 + 1312), a1 + 100108);
  rf_event_state_collect_armed_generic((int)(a1 + 1504), a1 + 100109);
  if ( unk_88E7CC )
    a1[100119] = 0;
  else
    rf_goal_state_pack_shared_names((int)(a1 + 69984), a1 + 100119);
  rf_event_state_pack_deleted_identifiers(a1 + 99976, a1 + 100126);
  rf_bolt_emitter_snapshot_collect((int)(a1 + 2144), a1 + 100110);
  rf_entity_snapshot_collect((int)(a1 + 2272), a1 + 100112, (int)(a1 + 99720), a1 + 100125);
  rf_item_snapshot_collect((int)(a1 + 36576), a1 + 100113);
  rf_clutter_snapshot_collect((int)(a1 + 41696), (_WORD *)a1 + 50057);
  rf_trigger_snapshot_collect((int)(a1 + 53984), a1 + 100116);
  rf_mover_snapshot_collect((int)(a1 + 57440), a1 + 100117);
  rf_push_region_snapshot_collect((int)(a1 + 69728), a1 + 100118);
  rf_world_decal_snapshot_collect((int)(a1 + 70184), a1 + 100111);
  rf_projectile_snapshot_collect((int)(a1 + 76584), a1 + 100120);
  rf_blood_surface_mark_snapshot_collect((int)(a1 + 77800), a1 + 100121);
  rf_corpse_serialize_animation_state((int)(a1 + 78088), a1 + 100122);
  memcpy(a1 + 95112, rf_geomod_save_records, 32 * rf_geomod_save_record_count);
  a1[100123] = rf_geomod_save_record_count;
  rf_vector_copy((float *)a1 + 10, copy_result, (const float *)(rf_world_solid + 72));
  rf_vector_copy((float *)a1 + 13, v2, (const float *)(rf_world_solid + 84));
  return rf_glass_snapshot_collect_removed_geometry_ids((int)(a1 + 99208), a1 + 100124);
}

