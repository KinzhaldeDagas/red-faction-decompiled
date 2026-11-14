// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F4300 rf_savegame_update_current_level_in_stream
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Caller-owned r+b stream: seek0/read83544-byte header, case-insensitive lookup current level in32-byte name slots at+12; append name/increment count if absent, set current index+188. Copy title to header+140(47chars+null), shared clock header+192 and countdown+196, music filename+62184. Write ONLY62232-byte header prefix from offset0, preserving previously written player/persona suffix. Seek83544+100128*index; allocate level block, copy level name, shared seconds to block+36, size100128 to+32, collect runtime payload and fwrite100128 bytes. Return0 on checked seek/read/write failures,1 on final write success. No stream close, local slot-capacity guard or rollback of earlier prefix write.
char __cdecl rf_savegame_update_current_level_in_stream(FILE *Stream)
{
  const char *v2; // eax
  const char *v3; // eax
  const char *v4; // [esp-4h] [ebp-70h]
  char v5; // [esp+7h] [ebp-65h]
  _BYTE *v6; // [esp+Ch] [ebp-60h]
  const char *v7; // [esp+10h] [ebp-5Ch]
  char *v8; // [esp+14h] [ebp-58h]
  char v9; // [esp+1Bh] [ebp-51h]
  char *v10; // [esp+20h] [ebp-4Ch]
  const char *v11; // [esp+24h] [ebp-48h]
  char *v12; // [esp+28h] [ebp-44h]
  char *v13; // [esp+30h] [ebp-3Ch]
  char *v14; // [esp+3Ch] [ebp-30h]
  char *Source; // [esp+44h] [ebp-28h]
  void *v16; // [esp+48h] [ebp-24h] BYREF
  void *Buffer; // [esp+4Ch] [ebp-20h]
  int v18; // [esp+50h] [ebp-1Ch]
  int i; // [esp+54h] [ebp-18h]
  void *v20; // [esp+58h] [ebp-14h] BYREF
  void *first_dword; // [esp+5Ch] [ebp-10h]
  int v22; // [esp+68h] [ebp-4h]

  if ( fseek(Stream, 0, 0) < 0 )
    return 0;
  v14 = (char *)operator new(0x14658u);
  v22 = 0;
  if ( v14 )
    v12 = rf_savegame_header_construct_subobjects(v14);
  else
    v12 = nullptr;
  v22 = -1;
  rf_scene_key_set_first_dword(&v16, (int)v12);
  v22 = 1;
  Buffer = (void *)rf_receiver_get_first_dword(&v16);
  if ( !fread(Buffer, 0x14658u, 1u, Stream) )
    goto LABEL_27;
  v18 = -1;
  for ( i = 0; i < *((_DWORD *)Buffer + 2); ++i )
  {
    v4 = (char *)Buffer + 32 * i + 12;
    v2 = rf_string_object_c_str_or_empty(unk_6FC31C);
    if ( !_stricmp(v2, v4) )
    {
      v18 = i;
      break;
    }
  }
  if ( v18 == -1 )
  {
    v11 = rf_string_object_c_str_or_empty(unk_6FC31C);
    v10 = (char *)Buffer + 32 * *((_DWORD *)Buffer + 2) + 12;
    do
    {
      v9 = *v11;
      *v10++ = *v11++;
    }
    while ( v9 );
    *((_DWORD *)Buffer + 47) = (*((_DWORD *)Buffer + 2))++;
  }
  else
  {
    *((_DWORD *)Buffer + 47) = v18;
  }
  v3 = rf_string_object_c_str_or_empty(unk_6FC314);
  strncpy((char *)Buffer + 140, v3, 0x30u);
  *((_BYTE *)Buffer + 187) = 0;
  *((float *)Buffer + 48) = unk_6FC42C;
  *((float *)Buffer + 49) = rf_mission_countdown_remaining_seconds;
  memset((char *)Buffer + 62184, 0, 0x30u);
  Source = rf_ui_panel_stack_current_id() == 11 ? (char *)rf_music_owned_get_resource_record() : (char *)unk_6E6AC0;
  if ( Source )
  {
    strncpy((char *)Buffer + 62184, Source, 0x2Fu);
    *((_BYTE *)Buffer + 62231) = 0;
  }
  else
  {
    *((_BYTE *)Buffer + 62184) = 0;
  }
  if ( fseek(Stream, 0, 0) >= 0
    && fwrite(Buffer, 0xF318u, 1u, Stream)
    && fseek(Stream, 100128 * *((_DWORD *)Buffer + 47) + 83544, 0) >= 0 )
  {
    v13 = (char *)operator new(0x18720u);
    LOBYTE(v22) = 2;
    if ( v13 )
      v8 = rf_level_snapshot_construct_subobjects(v13);
    else
      v8 = nullptr;
    LOBYTE(v22) = 1;
    rf_scene_key_set_first_dword(&v20, (int)v8);
    LOBYTE(v22) = 3;
    first_dword = (void *)rf_receiver_get_first_dword(&v20);
    v7 = rf_string_object_c_str_or_empty(unk_6FC31C);
    v6 = first_dword;
    do
    {
      v5 = *v7;
      *v6++ = *v7++;
    }
    while ( v5 );
    *((float *)first_dword + 9) = *(float *)&dword_6FC428;
    *((_DWORD *)first_dword + 8) = 100128;
    rf_level_state_collect_runtime_snapshot(first_dword);
    if ( fwrite(first_dword, 0x18720u, 1u, Stream) )
    {
      LOBYTE(v22) = 1;
      rf_snapshot_owned_buffer_delete(&v20);
      v22 = -1;
      rf_snapshot_owned_buffer_delete(&v16);
      return 1;
    }
    else
    {
      LOBYTE(v22) = 1;
      rf_snapshot_owned_buffer_delete(&v20);
      v22 = -1;
      rf_snapshot_owned_buffer_delete(&v16);
      return 0;
    }
  }
  else
  {
LABEL_27:
    v22 = -1;
    rf_snapshot_owned_buffer_delete(&v16);
    return 0;
  }
}

