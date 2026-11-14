// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004266F0 rf_entity_reset_local_impact_state_and_cache_helmet_audio
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): No arguments. First calls43D360 blood-surface-mark pool initializer, ignoring status. Signed i=0..<global local-player count87C638 re-reads
// count each iteration; dereferences player entry87C5B0[i]+20 without entry NULL guard and resolves ENTITY. Missing entity skips that entry only. Resolved entity: store FLOAT+2232=0,
// arm embedded deadline+2236 at clock-relative0ms, THEN FLOAT+2228=0. No health/death/player-role test. After loop, only if cached DWORD681E7C isNULL calls material custom sound-set
// lookup("helmet clatter") and stores result verbatim; NULL remains eligible for a future retry. Existing nonzero cache is retained. EAX is path-dependent initializer result, final
// loop-increment value or new lookup result, not canonical success. No pool/cache destruction, per-entry rollback or deadline disarm.
int rf_entity_reset_local_impact_state_and_cache_helmet_audio()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-Ch]
  int i; // [esp+8h] [ebp-4h]

  result = rf_blood_surface_mark_pool_init();
  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    v1 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_player_entries[i] + 20));
    if ( v1 )
    {
      *(float *)(v1 + 2232) = 0.0;
      rf_replicator_arm_milliseconds((int *)(v1 + 2236), 0);
      *(float *)(v1 + 2228) = 0.0;
    }
    result = i + 1;
  }
  if ( !unk_681E7C )
  {
    result = rf_material_custom_sound_set_find("helmet clatter");
    unk_681E7C = result;
  }
  return result;
}

