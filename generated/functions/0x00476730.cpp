// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476730 rf_cutscene_play_level_audio_mix
// UNREALRED VERIFIED [cutscene-playback-20261028]: Case-insensitive exact logical level-name dispatch: l6s3->RFCS_02_FinalMix.wav,l7s4->03,l8s4->04,l11s3->05,l13s3->06,l14s3->07,l15s4->08,l17s4->09,l20s3->10 (all .rfl and filenames RFCS_NN_FinalMix.wav). Match returns rf_music_play_unowned_filename(filename,1.0). No match returns final stricmp result, not a meaningful music handle. No fallback audio or path stripping.
int rf_cutscene_play_level_audio_mix()
{
  const char *v0; // eax
  const char *v1; // eax
  const char *v2; // eax
  const char *v3; // eax
  const char *v4; // eax
  const char *v5; // eax
  const char *v6; // eax
  const char *v7; // eax
  const char *v8; // eax
  int result; // eax
  const char *v10; // [esp+4h] [ebp-4h]

  v0 = rf_string_object_c_str_or_empty(unk_6FC31C);
  if ( !_stricmp(v0, "l6s3.rfl") )
  {
    v10 = "RFCS_02_FinalMix.wav";
    return rf_music_play_unowned_filename((int)v10, 1.0);
  }
  v1 = rf_string_object_c_str_or_empty(unk_6FC31C);
  if ( !_stricmp(v1, "l7s4.rfl") )
  {
    v10 = "RFCS_03_FinalMix.wav";
    return rf_music_play_unowned_filename((int)v10, 1.0);
  }
  v2 = rf_string_object_c_str_or_empty(unk_6FC31C);
  if ( !_stricmp(v2, "l8s4.rfl") )
  {
    v10 = "RFCS_04_FinalMix.wav";
    return rf_music_play_unowned_filename((int)v10, 1.0);
  }
  v3 = rf_string_object_c_str_or_empty(unk_6FC31C);
  if ( !_stricmp(v3, "l11s3.rfl") )
  {
    v10 = "RFCS_05_FinalMix.wav";
    return rf_music_play_unowned_filename((int)v10, 1.0);
  }
  v4 = rf_string_object_c_str_or_empty(unk_6FC31C);
  if ( !_stricmp(v4, "l13s3.rfl") )
  {
    v10 = "RFCS_06_FinalMix.wav";
    return rf_music_play_unowned_filename((int)v10, 1.0);
  }
  v5 = rf_string_object_c_str_or_empty(unk_6FC31C);
  if ( !_stricmp(v5, "l14s3.rfl") )
  {
    v10 = "RFCS_07_FinalMix.wav";
    return rf_music_play_unowned_filename((int)v10, 1.0);
  }
  v6 = rf_string_object_c_str_or_empty(unk_6FC31C);
  if ( !_stricmp(v6, "l15s4.rfl") )
  {
    v10 = "RFCS_08_FinalMix.wav";
    return rf_music_play_unowned_filename((int)v10, 1.0);
  }
  v7 = rf_string_object_c_str_or_empty(unk_6FC31C);
  if ( !_stricmp(v7, "l17s4.rfl") )
  {
    v10 = "RFCS_09_FinalMix.wav";
    return rf_music_play_unowned_filename((int)v10, 1.0);
  }
  v8 = rf_string_object_c_str_or_empty(unk_6FC31C);
  result = _stricmp(v8, "l20s3.rfl");
  if ( !result )
  {
    v10 = "RFCS_10_FinalMix.wav";
    return rf_music_play_unowned_filename((int)v10, 1.0);
  }
  return result;
}

