// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1AA0 rf_explosion_definition_parse_next
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Cdecl parser pointer. Destination=813C20+152*globalCount814348; no count increment here. Searches forward for $Name: with NULL stop-token; failure also searches #End, ignores that
// result, returns-1. Success requires $Name:, quoted bounded reader32 into name0; $Flags: one-name mask table662DCC(no_trails); $Explosion_play_time: ->F32at136. Sets
// centralCount124=0 and consumes repeated +Central_Emitter: entries. Each quoted reader64 name resolves4CE330 to index array44+4*j; missing central index-1 formats error and fatal
// source explosion.cpp:250 (native retry loop if fatal returned).
// Per central j: required +process_per_frame: stores BOOL BYTE68+j; optional +min_size_before_use: F32at76+4*j default0; optional +play_time_factor: F32at100+4*j defaultFLT_MAX
// (0x7F7FFFFF). Optional +rand_pos_factor: writes SHARED F32at144, default0 EACH central iteration, so LAST central wins; zero-central entry leaves144 untouched. Increments
// centralCount after these stores. No bound against six nominal central slots; excess entries overwrite adjacent fields.
// Sets sparksCount132=0,sparksIndex128=-1; optional $Sparks_Emitter: resolves name WITHOUT fatal validity check and requires +number: signed integer132. Sets headIndex36=-1; optional
// $Trail_Head_Emitter: resolves unchecked name, requires +time_to_emit_head_parts: ->140 and optional +rand_pos_factor: ->148/default0. If head clause absent,140/148 untouched. Sets
// tailIndex40=-1; optional $Trail_Tail_Emitter: resolves unchecked name. Returns0, does NOT memset row, validate numeric ranges, clamp central count/global table capacity, validate
// optional emitter indices or impose a stop token on initial name search. Sequential optional-clause order is significant.
int __cdecl rf_explosion_definition_parse_next(_BYTE **parser)
{
  int name; // eax
  char boolean_word_prefix; // al
  double number_with_optional_decimal_fraction; // st7
  double v5; // st7
  double v6; // st7
  int v7; // eax
  int signed_decimal_or_hex_integer; // eax
  int v9; // eax
  double v10; // st7
  double v11; // st7
  int v12; // eax
  char v13[64]; // [esp+0h] [ebp-508h] BYREF
  char v14[64]; // [esp+40h] [ebp-4C8h] BYREF
  char v15[64]; // [esp+80h] [ebp-488h] BYREF
  char Buffer[1024]; // [esp+C0h] [ebp-448h] BYREF
  char String2[64]; // [esp+4C0h] [ebp-48h] BYREF
  char *Destination; // [esp+504h] [ebp-4h]

  Destination = &unk_813C20[152 * unk_814348];
  if ( rf_text_parser_find_substring_before_optional_stop(parser, "$Name:", nullptr) )
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Name:");
    rf_text_parser_read_delimited_cstring((int)parser, Destination, 32, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Flags:");
    *((_DWORD *)Destination + 8) = rf_text_parser_read_parenthesized_named_flag_mask(parser, (int)&off_662DCC, 1);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Explosion_play_time:");
    *((float *)Destination + 34) = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
    *((_DWORD *)Destination + 31) = 0;
    while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+Central_Emitter:") )
    {
      rf_text_parser_read_delimited_cstring((int)parser, String2, 64, 34, 34);
      name = rf_particle_emitter_definition_find_name(String2);
      *(_DWORD *)&Destination[4 * *((_DWORD *)Destination + 31) + 44] = name;
      if ( *(_DWORD *)&Destination[4 * *((_DWORD *)Destination + 31) + 44] == -1 )
      {
        sprintf(
          Buffer,
          "Entry \"%s\" in explosion.tbl references non-existent entry \"%s\" in emitter.tbl!",
          Destination,
          String2);
        rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\gamesrc\\particle\\explosion.cpp", 250, Buffer);
      }
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+process_per_frame:");
      boolean_word_prefix = rf_text_parser_read_boolean_word_prefix((const char **)parser);
      Destination[*((_DWORD *)Destination + 31) + 68] = boolean_word_prefix;
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+min_size_before_use:") )
      {
        number_with_optional_decimal_fraction = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        *(float *)&Destination[4 * *((_DWORD *)Destination + 31) + 76] = number_with_optional_decimal_fraction;
      }
      else
      {
        *(float *)&Destination[4 * *((_DWORD *)Destination + 31) + 76] = 0.0;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+play_time_factor:") )
      {
        v5 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        *(float *)&Destination[4 * *((_DWORD *)Destination + 31) + 100] = v5;
      }
      else
      {
        *(float *)&Destination[4 * *((_DWORD *)Destination + 31) + 100] = 3.4028235e38;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+rand_pos_factor:") )
      {
        v6 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        *((float *)Destination + 36) = v6;
      }
      else
      {
        *((float *)Destination + 36) = 0.0;
      }
      ++*((_DWORD *)Destination + 31);
    }
    *((_DWORD *)Destination + 33) = 0;
    *((_DWORD *)Destination + 32) = -1;
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Sparks_Emitter:") )
    {
      rf_text_parser_read_delimited_cstring((int)parser, v15, 64, 34, 34);
      v7 = rf_particle_emitter_definition_find_name(v15);
      *((_DWORD *)Destination + 32) = v7;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+number:");
      signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(parser);
      *((_DWORD *)Destination + 33) = signed_decimal_or_hex_integer;
    }
    *((_DWORD *)Destination + 9) = -1;
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Trail_Head_Emitter:") )
    {
      rf_text_parser_read_delimited_cstring((int)parser, v14, 64, 34, 34);
      v9 = rf_particle_emitter_definition_find_name(v14);
      *((_DWORD *)Destination + 9) = v9;
      rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+time_to_emit_head_parts:");
      v10 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
      *((float *)Destination + 35) = v10;
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "+rand_pos_factor:") )
      {
        v11 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
        *((float *)Destination + 37) = v11;
      }
      else
      {
        *((float *)Destination + 37) = 0.0;
      }
    }
    *((_DWORD *)Destination + 10) = -1;
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)parser, "$Trail_Tail_Emitter:") )
    {
      rf_text_parser_read_delimited_cstring((int)parser, v13, 64, 34, 34);
      v12 = rf_particle_emitter_definition_find_name(v13);
      *((_DWORD *)Destination + 10) = v12;
    }
    return 0;
  }
  else
  {
    rf_text_parser_find_substring_before_optional_stop(parser, "#End", nullptr);
    return -1;
  }
}

