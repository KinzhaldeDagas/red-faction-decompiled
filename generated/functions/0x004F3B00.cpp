// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F3B00 rf_savegame_write_file_for_player
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Ordinary save entry. Allocate83544-byte header owner, set shared-goal omission flag0x88E7CC=0 BEFORE checking player entity. On valid player, DeleteFileA(destination), create/truncate via wb (retry directory creation on open failure), close then reopen r+b. Seed file with full484056-byte global cache image(83544+4*100128), with unchecked initial fwrite result. Cache count==4 and current level absent can compact first slot not in current level adjacency rule, using candidate initialized-1 without found-index guard. Write player subrecord/persona-history suffix from temporary header at offset62232,length21312, then call0x4F4300 to update header prefix/current level block. Store filename global0x890400 even when final writer returns0. The destination file is replaced through direct writes without rollback in this body.
char __cdecl rf_savegame_write_file_for_player(LPCSTR lpFileName, int a2)
{
  const char *v3; // eax
  const char *v4; // eax
  CHAR v5; // [esp+7h] [ebp-75h]
  char *v6; // [esp+Ch] [ebp-70h]
  LPCSTR v7; // [esp+10h] [ebp-6Ch]
  char v8; // [esp+17h] [ebp-65h]
  char *v9; // [esp+1Ch] [ebp-60h]
  char *v10; // [esp+20h] [ebp-5Ch]
  char *v11; // [esp+2Ch] [ebp-50h]
  char v12; // [esp+30h] [ebp-4Ch]
  char *v13; // [esp+34h] [ebp-48h]
  int m; // [esp+3Ch] [ebp-40h]
  char v15; // [esp+43h] [ebp-39h]
  int k; // [esp+44h] [ebp-38h]
  int v17; // [esp+48h] [ebp-34h]
  int j; // [esp+4Ch] [ebp-30h]
  int n; // [esp+4Ch] [ebp-30h]
  char v20; // [esp+53h] [ebp-29h]
  int i; // [esp+58h] [ebp-24h]
  void *v22; // [esp+5Ch] [ebp-20h] BYREF
  char updated; // [esp+63h] [ebp-19h]
  int first_dword; // [esp+64h] [ebp-18h]
  FILE *Stream; // [esp+68h] [ebp-14h]
  int v27; // [esp+78h] [ebp-4h]

  v13 = (char *)operator new(0x14658u);
  v27 = 0;
  if ( v13 )
    v11 = rf_savegame_header_construct_subobjects(v13);
  else
    v11 = nullptr;
  v27 = -1;
  rf_scene_key_set_first_dword(&v22, (int)v11);
  v27 = 1;
  first_dword = rf_receiver_get_first_dword(&v22);
  unk_88E7CC = 0;
  if ( !rf_entity_resolve_handle(*(_DWORD *)(a2 + 20)) )
    goto LABEL_5;
  DeleteFileA(lpFileName);
  do
  {
    Stream = fopen(lpFileName, "wb");
    if ( Stream )
    {
      fclose(Stream);
    }
    else if ( !CreateDirectoryA(MEMORY[0x88E7D0], nullptr) )
    {
      rf_ui_show_ok_modal(unk_88D450, unk_88DF44, (int (*)(void))rf_savegame_callback_call_46F8B0, 0);
      v27 = -1;
      rf_snapshot_owned_buffer_delete(&v22);
      return 0;
    }
  }
  while ( !Stream );
  Stream = fopen(lpFileName, off_63D924);
  if ( Stream )
  {
    if ( dword_894D40 )
    {
      if ( dword_894D40 == 4 )
      {
        v20 = 0;
        for ( i = 0; i < dword_894D40; ++i )
        {
          v3 = rf_string_object_c_str_or_empty(unk_6FC31C);
          if ( !_stricmp((const char *)&unk_894D38[8 * i + 3], v3) )
          {
            v20 = 1;
            break;
          }
        }
        if ( !v20 )
        {
          v17 = -1;
          for ( j = 0; j < unk_890500; ++j )
          {
            v4 = rf_string_object_c_str_or_empty(unk_6FC31C);
            if ( !_stricmp((const char *)&unk_890508 + 164 * j, v4) )
            {
              for ( k = 0; k < dword_894D40; ++k )
              {
                v15 = 0;
                for ( m = 0; m < unk_890528[41 * j]; ++m )
                {
                  if ( !_stricmp((const char *)&unk_894D38[8 * k + 3], &unk_89052C[164 * j + 32 * m]) )
                  {
                    v15 = 1;
                    break;
                  }
                }
                if ( !v15 )
                {
                  v17 = k;
                  goto LABEL_38;
                }
              }
              break;
            }
          }
LABEL_38:
          for ( n = v17; n < dword_894D40 - 1; ++n )
          {
            memcpy((char *)&unk_8A9390 + 100128 * n, (char *)&unk_8A9390 + 100128 * n + 100128, 0x18720u);
            v10 = &unk_894D44[32 * n + 32];
            v9 = &unk_894D44[32 * n];
            do
            {
              v8 = *v10;
              *v9++ = *v10++;
            }
            while ( v8 );
          }
          --dword_894D40;
        }
      }
    }
    else
    {
      unk_894D38[0] = 83544;
      unk_894D3C = 65545;
      unk_894DF4 = -1;
    }
    fwrite(unk_894D38, 0x762D8u, 1u, Stream);
    fseek(Stream, 62232, 0);
    rf_savegame_pack_player_subrecord(first_dword + 62232, a2);
    *(_DWORD *)(first_dword + 83528) = rf_persona_history_count;
    *(_DWORD *)(first_dword + 83532) = rf_persona_history_newest_index;
    *(_DWORD *)(first_dword + 83536) = rf_persona_history_total_height;
    memcpy((void *)(first_dword + 62406), &rf_persona_history_entries, 0x5280u);
    *(_BYTE *)(first_dword + 62397) = rf_ai_difficulty_get_with_zero_fallback();
    fwrite((const void *)(first_dword + 62232), 0x5340u, 1u, Stream);
    updated = rf_savegame_update_current_level_in_stream(Stream);
    fclose(Stream);
    v7 = lpFileName;
    v6 = &unk_890400;
    do
    {
      v5 = *v7;
      *v6++ = *v7++;
    }
    while ( v5 );
    v12 = updated;
    v27 = -1;
    rf_snapshot_owned_buffer_delete(&v22);
    return v12;
  }
  else
  {
LABEL_5:
    v27 = -1;
    rf_snapshot_owned_buffer_delete(&v22);
    return 0;
  }
}

