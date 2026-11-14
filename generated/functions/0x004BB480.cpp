// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BB480 rf_text_parse_optional_use_classification
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Cdecl(parser,outClassificationDWORD*,outRadiusF32*). Absent exact $Use: prefix returns WITHOUT writing eitheroutput. Present quoted name matched case-insensitively:vehicle1,switch2,command3,turret4,monitor5,medic6,ai response9,play_sound10. Unknown present name writes classification0 thenreturns WITHOUT consuming/assigning +radius:. Recognized name writesclassification THEN requires +radius: and stores parsednumber to radius;no finite/positive clamp. Thus missing/malformed radius can leave classification committed before fatal. No outputpointer validation;temporary RFString cleanup/SEH only,not semantic rollback.
void __cdecl rf_text_parse_optional_use_classification(const char **parser, _DWORD *a2, float *a3)
{
  int destination[2]; // [esp+4h] [ebp-14h] BYREF
  int v4; // [esp+14h] [ebp-4h]

  rf_string_construct_empty(destination);
  v4 = 0;
  if ( !rf_text_parser_try_consume_case_insensitive_prefix(parser, "$Use:") )
  {
    v4 = -1;
    rf_string_destroy_buffer(destination);
    return;
  }
  rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
  if ( rf_string_equals_case_insensitive((int)destination, "vehicle") )
  {
    *a2 = 1;
  }
  else if ( rf_string_equals_case_insensitive((int)destination, "switch") )
  {
    *a2 = 2;
  }
  else if ( rf_string_equals_case_insensitive((int)destination, "command") )
  {
    *a2 = 3;
  }
  else if ( rf_string_equals_case_insensitive((int)destination, "turret") )
  {
    *a2 = 4;
  }
  else if ( rf_string_equals_case_insensitive((int)destination, "monitor") )
  {
    *a2 = 5;
  }
  else if ( rf_string_equals_case_insensitive((int)destination, "medic") )
  {
    *a2 = 6;
  }
  else if ( rf_string_equals_case_insensitive((int)destination, "ai response") )
  {
    *a2 = 9;
  }
  else
  {
    if ( !rf_string_equals_case_insensitive((int)destination, "play_sound") )
    {
      *a2 = 0;
      v4 = -1;
      rf_string_destroy_buffer(destination);
      return;
    }
    *a2 = 10;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "+radius:");
  *a3 = rf_text_parser_read_number_with_optional_decimal_fraction(parser);
  v4 = -1;
  rf_string_destroy_buffer(destination);
}

