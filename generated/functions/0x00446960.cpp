// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446960 rf_gamesound_parse_table_entry
// UNREALRED VERIFIED [combat-speech-providers-20261111]: Each sounds.tbl row reads filename,minDistance,volume,rolloff and calls567F80. Returned registered resource ID MUST equal this source ordinal; otherwise fatal error loops at4469E7. Registration failure or filename dedup that changes base ordinals is not a completed valid base registry. Host preparation must reject this invalid registry explicitly, not publish shifted/missing global enum entries as success.
int __cdecl rf_gamesound_parse_table_entry(_DWORD *a1, int a2)
{
  int result; // eax
  float distance; // [esp+Ch] [ebp-120h]
  char Destination[268]; // [esp+14h] [ebp-118h] BYREF
  float scale; // [esp+124h] [ebp-8h]
  float volume; // [esp+128h] [ebp-4h]

  rf_text_parser_read_delimited_cstring((int)a1, Destination, 256, 34, 34);
  distance = rf_text_parser_read_number_with_optional_decimal_fraction(a1);
  volume = rf_text_parser_read_number_with_optional_decimal_fraction(a1);
  scale = rf_text_parser_read_number_with_optional_decimal_fraction(a1);
  result = rf_sound_resource_load(Destination, distance, volume, scale);
  if ( result != a2 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\gamewide\\gamesound.cpp",
      301,
      "Error parsing sounds.tbl -- sound handle does not match gamesound enum!");
  return result;
}

