// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F4C10 rf_savegame_restore_level_state
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Literal auto.svl(case-insensitive) selects global cached current-level block by name without opening file; missing cache match returns0. Other filenames read global83544-byte header and count level blocks, reopen/seek selected block via temporary header and malloc100128; selected read/seek failures reset full cache through0x4F5AC0. Copy/replay GeoMod history FIRST, restore world bounds, restore runtime managers, apply deferred id fixups. Outside UI/state10, find saved entity id-999 and call player restore(header+62232,player,snapshot), then apply fixups AGAIN, reconcile player physics, clocks/countdown/music. Finally filter trigger links, free only heap-loaded level block and return1. Does not use auto.svl as a disk filename in special branch, validate every input count locally, or clear applied fixup queue between the two passes.
char __cdecl rf_savegame_restore_level_state(char *FileName, int a2)
{
  const char *v2; // eax
  const char *v4; // eax
  char *v5; // [esp+18h] [ebp-6Ch]
  float v6[3]; // [esp+20h] [ebp-64h] BYREF
  float copy_result[3]; // [esp+2Ch] [ebp-58h] BYREF
  void *v8; // [esp+40h] [ebp-44h]
  char *v9; // [esp+44h] [ebp-40h]
  int v10; // [esp+48h] [ebp-3Ch]
  int v11; // [esp+4Ch] [ebp-38h]
  int v12; // [esp+50h] [ebp-34h]
  int v13; // [esp+54h] [ebp-30h]
  void *v14; // [esp+58h] [ebp-2Ch] BYREF
  int v15; // [esp+5Ch] [ebp-28h]
  void *Block; // [esp+60h] [ebp-24h]
  void *Buffer; // [esp+64h] [ebp-20h]
  int i; // [esp+68h] [ebp-1Ch]
  char v19; // [esp+6Fh] [ebp-15h]
  FILE *Stream; // [esp+70h] [ebp-14h]
  void *first_dword; // [esp+74h] [ebp-10h]
  int v22; // [esp+80h] [ebp-4h]

  Stream = nullptr;
  Block = nullptr;
  Buffer = nullptr;
  v8 = operator new(0x14658u);
  v22 = 0;
  if ( v8 )
    v5 = rf_savegame_header_construct_subobjects((char *)v8);
  else
    v5 = nullptr;
  v9 = v5;
  v22 = -1;
  rf_scene_key_set_first_dword(&v14, (int)v5);
  v22 = 1;
  first_dword = (void *)rf_receiver_get_first_dword(&v14);
  if ( !_stricmp(FileName, "auto.svl") )
  {
    v13 = -1;
    for ( i = 0; i < dword_894D40; ++i )
    {
      v2 = rf_string_object_c_str_or_empty(unk_6FC31C);
      if ( !_stricmp(&unk_894D44[32 * i], v2) )
      {
        v13 = i;
        break;
      }
    }
    if ( v13 == -1 )
      goto LABEL_11;
    Block = (char *)&unk_8A9390 + 100128 * v13;
    Buffer = unk_894D38;
    v19 = 0;
  }
  else
  {
    Stream = fopen(FileName, "rb");
    if ( !Stream )
    {
LABEL_11:
      v22 = -1;
      rf_snapshot_owned_buffer_delete(&v14);
      return 0;
    }
    if ( !fread(unk_894D38, 0x14658u, 1u, Stream) )
    {
      fclose(Stream);
      v22 = -1;
      rf_snapshot_owned_buffer_delete(&v14);
      return 0;
    }
    for ( i = 0; i < dword_894D40; ++i )
    {
      if ( !fread((char *)&unk_8A9390 + 100128 * i, 0x18720u, 1u, Stream) )
        goto LABEL_33;
    }
    fseek(Stream, 0, 0);
  }
  v15 = -1;
  if ( !Block && Stream )
  {
    Buffer = first_dword;
    if ( !fread(first_dword, 0x14658u, 1u, Stream) )
      goto LABEL_33;
    v15 = -1;
    for ( i = 0; i < *((_DWORD *)Buffer + 2); ++i )
    {
      v4 = rf_string_object_c_str_or_empty(unk_6FC31C);
      if ( !_stricmp((const char *)Buffer + 32 * i + 12, v4) )
      {
        v15 = i;
        break;
      }
    }
    if ( v15 == -1 )
    {
      fclose(Stream);
      rf_ui_panel_stack_current_id();
      v22 = -1;
      rf_snapshot_owned_buffer_delete(&v14);
      return 0;
    }
    if ( fseek(Stream, 100128 * v15 + 83544, 0) < 0 )
    {
LABEL_33:
      fclose(Stream);
      rf_level_state_cache_clear();
      v22 = -1;
      rf_snapshot_owned_buffer_delete(&v14);
      return 0;
    }
    Block = malloc(0x18720u);
    if ( !fread(Block, 0x18720u, 1u, Stream) )
    {
      fclose(Stream);
      free(Block);
      rf_level_state_cache_clear();
      v22 = -1;
      rf_snapshot_owned_buffer_delete(&v14);
      return 0;
    }
    fclose(Stream);
    v19 = 1;
  }
  rf_game_clock_pause_depth_increment();
  memcpy(rf_geomod_save_records, (char *)Block + 95112, 32 * *((unsigned __int8 *)Block + 100123));
  rf_geomod_save_record_count = *((unsigned __int8 *)Block + 100123);
  rf_geomod_save_history_replay();
  rf_vector_copy((float *)(rf_world_solid + 72), copy_result, (const float *)Block + 10);
  rf_vector_copy((float *)(rf_world_solid + 84), v6, (const float *)Block + 13);
  rf_level_state_restore_runtime_snapshot((int)Block);
  rf_restore_apply_object_identifier_fixups();
  if ( rf_ui_panel_stack_current_id() != 10 )
  {
    for ( i = 0; i < *((unsigned __int8 *)Block + 100112); ++i )
    {
      if ( *((_DWORD *)Block + 134 * i + 568) == -999 )
      {
        v11 = (int)Block + 536 * i + 2272;
        break;
      }
    }
    if ( !rf_savegame_restore_player_subrecord((int)Buffer + 62232, a2, v11) )
    {
      rf_game_clock_pause_depth_decrement();
      if ( v19 )
        free(Block);
      rf_level_state_cache_clear();
      v22 = -1;
      rf_snapshot_owned_buffer_delete(&v14);
      return 0;
    }
    rf_restore_apply_object_identifier_fixups();
    v12 = rf_object_find_by_saved_identifier(-999);
    if ( v12 && !*(_DWORD *)(v12 + 36) )
    {
      v10 = v12;
      sub_4D9960(v12);
    }
    unk_6FC42C = *((float *)Buffer + 48);
    rf_mission_countdown_remaining_seconds = *((float *)Buffer + 49);
    rf_difficulty_set_valid_choice_copy_configured_and_load_ui(*((unsigned __int8 *)Buffer + 62397));
    if ( (char *)Buffer + strlen((const char *)Buffer + 62184) + 62185 != (char *)Buffer + 62185
      && !rf_ui_get_raw_panel_byte6E6D94() )
    {
      rf_music_play_owned_filename((int)Buffer + 62184, 1.0);
    }
  }
  rf_trigger_filter_flag8_links();
  if ( v19 )
    free(Block);
  rf_game_clock_pause_depth_decrement();
  v22 = -1;
  rf_snapshot_owned_buffer_delete(&v14);
  return 1;
}

