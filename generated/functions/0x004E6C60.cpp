// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E6C60 rf_local_players_reset_fpgun_state_and_load_models
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): No args. For each entry in signed global local-player count, no entryNULL check, let state=player+3968. Write pending weapon0=-1; disarm timestamps+4,+16,+184,+252 via55F020; zero bytes+12,+188,+49,+48,+196; DWORD+192=0,F32+64=+0; vector+68=zero, matrix+80=identity. Invoke D9F0(player) to reset three additional fields4228/4236/4240. Other state fields remain untouched; no whole-state memset or action cancellation helper. After loop, if global662FCC==-1 lookup Foley name Riot Spark (stores row index including-1), then call4ECD10 model-cache initializer and return its raw EAX. Cache/model loader runs even when no local entries; no per-player sound variant resolution here.
int rf_local_players_reset_fpgun_state_and_load_models()
{
  int v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    v1 = rf_local_player_entries[i] + 3968;
    *(_DWORD *)v1 = -1;
    rf_replicator_reset((_DWORD *)(v1 + 4));
    *(_BYTE *)(v1 + 12) = 0;
    rf_replicator_reset((_DWORD *)(v1 + 16));
    rf_vector3_zero_return_destination((float *)(v1 + 68));
    rf_identity_orientation_matrix((float *)(v1 + 80));
    rf_replicator_reset((_DWORD *)(v1 + 184));
    *(_BYTE *)(v1 + 188) = 0;
    *(_BYTE *)(v1 + 49) = 0;
    *(_BYTE *)(v1 + 48) = 0;
    *(_DWORD *)(v1 + 192) = 0;
    *(_BYTE *)(v1 + 196) = 0;
    *(float *)(v1 + 64) = 0.0;
    rf_replicator_reset((_DWORD *)(v1 + 252));
    rf_player_reset_fpgun_fields4228_4236_4240(rf_local_player_entries[i]);
  }
  if ( dword_662FCC == -1 )
    dword_662FCC = rf_foley_definition_find_name("Riot Spark");
  return rf_fpgun_initialize_cycle_slot_model_cache();
}

