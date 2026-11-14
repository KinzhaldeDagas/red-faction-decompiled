// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004534F0 rf_endgame_load_all_matching_localized_wrapped_text
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Construct stack parser, open 'endgame.tbl' via578EA0(this,path,raw0x0098967F
// decimal9999999,unused0). SIGNED negative open result fatal5708E0(endgame.cpp,line181,'Could not open endgame.tbl!'); hypothetical return repeats fatal. After successful open reset
// budgetDWORD6F1590=0 and textBYTE6F1598[0]=0,local foundBYTE0. Outer loop578BF0(parser,'$Name:',NULL) must return EXACTAL1; every other byte ends. Require/consume '$Name:' at found
// cursor through5797A0, then57A050(parser,stackName,capacity127,opening34,closing34), so accepted payload length<127 (at most126), not127. Compare FULL name case-insensitively
// against CURRENT global Cstring6F1508. Nonmatching entry resumes raw outer search without parsing its body. Searches are case-sensitive substrings and do not imply
// record/comment/quote boundaries.  For EACH matching name query CURRENT localization4EFC60: EXACT0 requires search/consume 'En:' before optional stop '$Name:';1 'Gr:';2 'Fr:'. A
// zero locatorAL explicitly fatal-exits with respective endgame.cpp lines200/204/208 and missing-language diagnostic. Any other language performs NO section search, starting line
// reads at current cursor. Then579460(line,256) ANYnonzeroAL admits line; false ends INNER loop normally. CRT _strnicmp('#end',line,6)==0 ends inner; despite count6, NUL-terminated
// '#end' makes this a case-insensitive full-string stop, not '#end...' prefix acceptance. No required terminal marker onEOF.  For every nonterminal line set local foundBYTE1 BEFORE
// wrapping/admission. Wrap58DC50(lengths,offsets,line,CURRENT viewportWidth,32,ignoredMarker0,fontID-1); no width-64 margin here. If countn==0 budget+=1; ANYnonzero n adds
// strlen(ORIGINAL line)+n, native32-bit wrap. SIGNED updated budget>2048 breaks INNER loop before appending that line; overbudget counter and found1 remain. Otherwise n0 appends
// WORD0x000A at globaltextNUL; n!=0 signed i0..<n strncat(text,line+offset[i],length[i]) then LF/NUL word for each. No independent source/count/offset/capacity validation. Counter
// measures original-line length plus emitted counts, not recomputed actual output length.  After any inner termination, CONTINUE outer search for further '$Name:' entries. ALL later
// matching duplicate names may append; there is no first-match return, budget reset per match, or global break on size. A later wrapped-counter change retains native behavior. If
// found remains0 after whole search, unbounded sprintf(text6F1598,'Missing endgame text for %s\n',CURRENT globalname6F1508), without updating budget counter. A matching
// empty/end-only section still falls back; a nonterminal line rejected for size already suppressed fallback. On normal end close parser579190 then destructor578830 closes again;
// return stack parser RECEIVER pointer inEAX, preserved by normal cookie check, not success/text length. SEH cleanup delegates destructor; no rollback of resets/appended/overbudget
// state, panel request, font/bitmap initialization or pause gate.
void **rf_endgame_load_all_matching_localized_wrapped_text()
{
  int viewport_width; // eax
  int language; // [esp+28h] [ebp-3BCh]
  size_t Count[32]; // [esp+30h] [ebp-3B4h] BYREF
  int v4; // [esp+B0h] [ebp-334h]
  char v5; // [esp+B7h] [ebp-32Dh]
  int line_offsets[33]; // [esp+B8h] [ebp-32Ch] BYREF
  int i; // [esp+13Ch] [ebp-2A8h]
  void *self[68]; // [esp+140h] [ebp-2A4h] BYREF
  char String2[128]; // [esp+250h] [ebp-194h] BYREF
  char Destination; // [esp+2D0h] [ebp-114h] BYREF
  _BYTE v11[3]; // [esp+2D1h] [ebp-113h] BYREF
  int v12; // [esp+3E0h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v12 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "endgame.tbl", byte_98967F, 0) < 0 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\interface\\endgame.cpp",
      181,
      "Could not open endgame.tbl!");
  dword_6F1590 = 0;
  byte_6F1598[0] = 0;
  v5 = 0;
  while ( rf_text_parser_find_substring_before_optional_stop((char **)self, "$Name:", nullptr) == 1 )
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Name:");
    rf_text_parser_read_delimited_cstring((int)self, String2, 127, 34, 34);
    if ( !_stricmp(unk_6F1508, String2) )
    {
      language = rf_localization_get_language();
      if ( language )
      {
        if ( language == 1 )
        {
          if ( !rf_text_parser_find_before_stop_and_consume_required((char **)self, "Gr:", "$Name:") )
            rf_fatal_error_show_message_and_exit(
              "D:\\projects\\rf_pc\\gamesrc\\interface\\endgame.cpp",
              204,
              "Missing German (Gr:) entry in endgame.tbl!");
        }
        else if ( language == 2 && !rf_text_parser_find_before_stop_and_consume_required((char **)self, "Fr:", "$Name:") )
        {
          rf_fatal_error_show_message_and_exit(
            "D:\\projects\\rf_pc\\gamesrc\\interface\\endgame.cpp",
            208,
            "Missing French (Fr:) entry in endgame.tbl!");
        }
      }
      else if ( !rf_text_parser_find_before_stop_and_consume_required((char **)self, "En:", "$Name:") )
      {
        rf_fatal_error_show_message_and_exit(
          "D:\\projects\\rf_pc\\gamesrc\\interface\\endgame.cpp",
          200,
          "Missing English (En:) entry in endgame.tbl!");
      }
      while ( rf_text_parser_read_cr_line_cstring_if_fits((int)self, &Destination, 256)
           && _strnicmp("#end", &Destination, 6u) )
      {
        v5 = 1;
        viewport_width = rf_renderer_get_viewport_width();
        v4 = rf_text_wrap_into_offset_length_arrays((int *)Count, line_offsets, &Destination, viewport_width, 32, 0, -1);
        if ( v4 )
          dword_6F1590 += v4 + &v11[strlen(&Destination)] - v11;
        else
          ++dword_6F1590;
        if ( dword_6F1590 > 2048 )
          break;
        if ( v4 )
        {
          for ( i = 0; i < v4; ++i )
          {
            strncat(byte_6F1598, &v11[line_offsets[i] - 1], Count[i]);
            *(_WORD *)&byte_6F1598[strlen(byte_6F1598)] = 10;
          }
        }
        else
        {
          *(_WORD *)&byte_6F1598[strlen(byte_6F1598)] = 10;
        }
      }
    }
  }
  if ( !v5 )
    sprintf(byte_6F1598, "Missing endgame text for %s\n", unk_6F1508);
  rf_memory_text_parser_close_buffer(self);
  v12 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

