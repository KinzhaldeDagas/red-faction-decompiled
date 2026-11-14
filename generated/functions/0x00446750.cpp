// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446750 rf_gamesound_parse_direct_sound
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Direct sound parser reads quoted filename; EMPTY filename returns-1 WITHOUT consuming distance/volume numbers or registering a resource. Nonempty reads minimumDistance then volume and calls567F80 with fixed rolloff1.0. These records must remain distinct from normalized Foley-set aliases.
// UNREALRED VERIFIED [combat-native-weapon-registry-20261111]: Direct sound cursor: read one quoted RFString. Only if byte length>0 read2numbers (minimum distance,volume), then register resource. Empty string returns-1 and consumes NO numeric operands. No positivity/range clamp in this reader; Foley-description parser is a different grammar.
int __cdecl rf_gamesound_parse_direct_sound(_DWORD *parser)
{
  const char *v2; // eax
  float distance; // [esp+0h] [ebp-34h]
  float volume; // [esp+4h] [ebp-30h]
  int v5; // [esp+10h] [ebp-24h]
  const char *destination[2]; // [esp+18h] [ebp-1Ch] BYREF
  float v7; // [esp+20h] [ebp-14h]
  float number_with_optional_decimal_fraction; // [esp+24h] [ebp-10h]
  int v9; // [esp+30h] [ebp-4h]

  rf_string_construct_empty(destination);
  v9 = 0;
  rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
  if ( (int)rf_string_length_from_cstr(destination) > 0 )
  {
    number_with_optional_decimal_fraction = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    v7 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    volume = v7;
    distance = number_with_optional_decimal_fraction;
    v2 = rf_string_object_c_str_or_empty(destination);
    v5 = rf_sound_resource_load(v2, distance, volume, 1.0);
    v9 = -1;
    rf_string_destroy_buffer(destination);
    return v5;
  }
  else
  {
    v9 = -1;
    rf_string_destroy_buffer(destination);
    return -1;
  }
}

