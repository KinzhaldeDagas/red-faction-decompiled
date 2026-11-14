// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446AF0 rf_foley_parse_sound_set
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Foley rows are44 bytes: name32,materialDWORD+20,count+24,variant SoundID pointer+28. Source order retains duplicate names. Sounds count optional defaults1. Material optional; then require exactly count Sound fields and parse each through446750. A zero/negative count reaches unsafe native allocation/dereference domains; a host must mark unsupported rather than invent a completed empty/no-sound set.
// UNREALRED VERIFIED [combat-speech-stock-parser-20261111]: Each Foley-row entry starts by FIND_SUBSTRING($Name:,no stop), then requires/reads name, optionalcountdefault1/material, and EXACT declaredcount Sound tuples. On next invocation scanner skips intervening extra/unrelated tokens until nextName. Therefore a stock row declaring4 but carrying6 Sound lines registers onlyfirst4; fifth/sixth are not fatal and are not appended/registered. Preserve source-order declared variants and scan row-boundaries; do not require next unconsumed token tobeName. StockDefaultFootstep andotherrows exercise this nativebehavior. NoName finds#End andreturns-1.
// UNREALRED VERIFIED [combat-speech-stock-parser-bounds-20261111]: Fresh578BF0 body proves CASE-SENSITIVE strstr target search; optional-stop branch executes ONLY for nonnull stop.446AF0 passesnullptr, so there is NO implicit#End stop. After initial required#Entity Sounds, row scanning can cross#End and later#Custom Sound Sets; stock consumes508 names (497+11), notonly497. Exactdeclaredvariant reads stillskip21extras at subsequent row searches. Host structured table adapter must preserve subsequentsection sourceorder andexactcase Name scan; it cannot silently treat section markers as native EOF. Native raw substring search also sees comments/quoted substrings after leadingtrivia; that raw-cursor grammar remains an explicit structured-document backend boundary.
// UNREALRED VERIFIED CORRECTION [combat-speech-stock-parser-case-20261111]: Supersedes ONLY the prior parser-bounds note stock508-count claim: installed stock has497 exactcase $Name: rows inEntitySounds, but ALL11 CustomSoundSets use lowercase $name:. CASE-SENSITIVE578BF0 therefore skips those11, so native Foley count497 with1140 declaredslots and21extras skipped. Native scan still has NO implicit#End stop, so a future exactcase $Name: after#End WOULD be found. This conclusion follows inspected rawstocktail (no uppercaseName in its trailingcomments) andfresh578BF0 disassembly. Earlier508 was a case-insensitive corpuscount, NOT native execution, and is retracted; preserve the analysis history.
int __cdecl rf_foley_parse_sound_set(_DWORD *parser)
{
  const char *v2; // eax
  int v3; // eax
  std::exception *v4; // [esp+4h] [ebp-3Ch]
  _DWORD *v5; // [esp+Ch] [ebp-34h]
  _BYTE v6[8]; // [esp+14h] [ebp-2Ch] BYREF
  _BYTE v7[8]; // [esp+1Ch] [ebp-24h] BYREF
  int i; // [esp+24h] [ebp-1Ch]
  int destination[2]; // [esp+28h] [ebp-18h] BYREF
  char *Destination; // [esp+30h] [ebp-10h]
  int v11; // [esp+3Ch] [ebp-4h]

  Destination = (char *)&unk_6E6E30 + 44 * unk_6EDC30;
  if ( rf_text_parser_find_substring_before_optional_stop((char **)parser, "$Name:", nullptr) )
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Name:");
    rf_text_parser_read_delimited_cstring((int)parser, Destination, 32, 34, 34);
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Sounds:") )
      *((_DWORD *)Destination + 9) = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
    else
      *((_DWORD *)Destination + 9) = 1;
    *((_DWORD *)Destination + 10) = malloc(4 * *((_DWORD *)Destination + 9));
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Material:") )
    {
      rf_string_construct_empty(destination);
      v11 = 0;
      rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
      if ( rf_string_equals_case_insensitive((int)destination, "default") )
      {
        *((_DWORD *)Destination + 8) = 0;
      }
      else if ( rf_string_equals_case_insensitive((int)destination, "rock") )
      {
        *((_DWORD *)Destination + 8) = 1;
      }
      else if ( rf_string_equals_case_insensitive((int)destination, "metal") )
      {
        *((_DWORD *)Destination + 8) = 2;
      }
      else if ( rf_string_equals_case_insensitive((int)destination, "flesh") )
      {
        *((_DWORD *)Destination + 8) = 3;
      }
      else if ( rf_string_equals_case_insensitive((int)destination, "water") )
      {
        *((_DWORD *)Destination + 8) = 4;
      }
      else if ( rf_string_equals_case_insensitive((int)destination, "laval") )
      {
        *((_DWORD *)Destination + 8) = 5;
      }
      else if ( rf_string_equals_case_insensitive((int)destination, "solid") )
      {
        *((_DWORD *)Destination + 8) = 6;
      }
      else if ( rf_string_equals_case_insensitive((int)destination, "sand") )
      {
        *((_DWORD *)Destination + 8) = 7;
      }
      else if ( rf_string_equals_case_insensitive((int)destination, (char *)off_633BA4) )
      {
        *((_DWORD *)Destination + 8) = 8;
      }
      else if ( rf_string_equals_case_insensitive((int)destination, "glass") )
      {
        *((_DWORD *)Destination + 8) = 9;
      }
      else if ( rf_string_equals_case_insensitive((int)destination, "ladder") )
      {
        *((_DWORD *)Destination + 8) = 1;
      }
      else
      {
        if ( !rf_string_equals_case_insensitive((int)destination, "chain fence") )
        {
          v5 = rf_string_concat_cstr_object(v7, "\"", (const void **)destination);
          LOBYTE(v11) = 1;
          v4 = (std::exception *)rf_string_concat_object_cstr(v6, v5, "\" is not a recognized material type!");
          LOBYTE(v11) = 2;
          v2 = rf_string_object_c_str_or_empty(v4);
          rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\gamesrc\\gamewide\\gamesound.cpp", 405, v2);
        }
        *((_DWORD *)Destination + 8) = 2;
      }
      v11 = -1;
      rf_string_destroy_buffer(destination);
    }
    for ( i = 0; i < *((_DWORD *)Destination + 9); ++i )
    {
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Sound:");
      v3 = rf_gamesound_parse_direct_sound(parser);
      *(_DWORD *)(*((_DWORD *)Destination + 10) + 4 * i) = v3;
    }
    return 0;
  }
  else
  {
    rf_text_parser_find_substring_before_optional_stop((char **)parser, "#End", nullptr);
    return -1;
  }
}

