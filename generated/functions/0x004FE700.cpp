// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FE700 rf_event_message_dispatch
// UNREALRED VERIFIED [serialized-event-bool-20260923]: Message dispatch first handles persona index +0x2C8 == -1 through ordinary game-sound/HUD calls, independent of byte +0x2CC and entity identifier. Otherwise byte +0x2CC == 1 enters the persona path and requires nonempty text before 0x44CEE0. Since RFL boolean ingestion normalizes any nonzero source byte, raw file values 2/255 select persona too when the index is not -1. Ordinary/entity speech branches remain separate; this annotation does not establish complete audio/HUD parity.
// UNREALRED VERIFIED [message-correction-audit-20260923]: Reaudit: index -1 calls gamesound directly and discards the returned handle; it does not read or update event +0x2D4. The ordinary nonpersona/nonentity branch alone checks +0x2D4 and writes it at 0x4FE89A. Successful independent voices remain in the gamesound pool. Entity identifier >0 takes a separate speech branch ending at 0x4FE858, with no ordinary HUD call; a generic four-second HUD expectation for that branch is not supported. Ordinary nonentity subtitles are conditional and request 10000 ms, not an unconditional 4000 ms.
void __thiscall rf_event_message_dispatch(int this)
{
  const char *v1; // eax
  char *v2; // eax
  const char *v3; // eax
  int v4; // [esp+0h] [ebp-10h]
  int v5; // [esp+4h] [ebp-Ch]
  int v7; // [esp+Ch] [ebp-4h]

  if ( *(_DWORD *)(this + 712) == -1 )
  {
    rf_gamesound_play_event(*(_DWORD *)(this + 696), 0, 0.0, 1.0);
    v1 = rf_string_object_c_str_or_empty((const void *)(this + 704));
    rf_hud_message_enqueue_expand_tokens_and_rearm_head(v1, 0, 0, nullptr);
  }
  else if ( *(_BYTE *)(this + 716) == 1 )
  {
    if ( (int)rf_string_length_from_cstr((const char **)(this + 704)) > 0 )
    {
      v5 = *(_DWORD *)(this + 696);
      v4 = *(_DWORD *)(this + 712);
      v2 = (char *)rf_string_object_c_str_or_empty((const void *)(this + 704));
      rf_hud_persona_admit_message(v2, v4, v5);
    }
  }
  else if ( *(int *)(this + 720) <= 0 )
  {
    if ( !rf_gamesound_voice_is_playing(*(_DWORD *)(this + 724)) )
    {
      *(_DWORD *)(this + 724) = rf_gamesound_play_event(*(_DWORD *)(this + 696), 0, 0.0, 1.0);
      if ( (*(int *)(this + 724) < 0 || *(int *)(this + 696) < 0 || *(_BYTE *)(rf_local_fpgun_player + 3893))
        && (rf_string_equals_case_insensitive((int)unk_6FC31C, "train01.rfl")
         || rf_string_equals_case_insensitive((int)unk_6FC31C, "train02.rfl")
         || *(_DWORD *)(this + 36) == 21068
         || *(_DWORD *)(this + 36) == 10091) )
      {
        v3 = rf_string_object_c_str_or_empty((const void *)(this + 704));
        rf_hud_message_enqueue_expand_tokens_and_rearm_head(v3, 0, 10000, nullptr);
      }
    }
  }
  else
  {
    v7 = sub_4316E0(*(_DWORD *)(this + 720));
    if ( v7
      && !rf_entity_is_dead(v7)
      && (*(_DWORD *)(v7 + 1312) == 13
       || *(_DWORD *)(v7 + 1312) == 2
       || *(_DWORD *)(v7 + 1312) == 4
       || *(_DWORD *)(v7 + 1312) == 8
       || *(_DWORD *)(v7 + 1312) == 14
       || *(_DWORD *)(v7 + 1312) == 1)
      && *(_DWORD *)(this + 696) != -1 )
    {
      rf_entity_replace_speech_voice(v7, *(_DWORD *)(this + 696), 0);
    }
  }
}

