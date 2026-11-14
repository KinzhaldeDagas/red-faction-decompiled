// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004451D0 sub_4451D0
// UNREALRED VERIFIED [combat-panic-movement-20261111]: Process initialization reads movemodes.tbl, requires #movement modes/#end and each $name plus move x/y/z ref and rot x/y/z ref.16 fixed canonical names at661598 index0none,1run,2climb,3fall,4swim,5apc,6apc fall,7sub,8sub fall,9fighter,10turret,11robot fly,12hover,13freelookcam,14deadcam,15johns descent flying mode.32-byte records at6E6B90: loaded byte0,index+4,move refs+8/+C/+10,rotation refs+14/+18/+1C. Initialization clears only loaded bytes. Unknown named entries parse to stack scratch, not a new registry slot. Ref strings: move none/eye/body/parent; rot none/eye-obj/body-obj/body-world; unknown refs become0.
// UNREALRED VERIFIED [combat-panic-movement-20261111-clarified]: Canonical-name precision: native slot15 string at633728 is exactly "john's descent flying mode" including the apostrophe. Earlier same-pass shorthand omitted that punctuation; implementation canonical-name lookup must use these exact bytes. Archive movemodes.tbl3539 bytes at tables.vpp offset819200 contains this exact authored name and matches the extracted source byte-for-byte.
void **sub_4451D0()
{
  char v1; // [esp+4h] [ebp-154h] BYREF
  int i; // [esp+24h] [ebp-134h]
  char *v3; // [esp+28h] [ebp-130h]
  int destination[2]; // [esp+2Ch] [ebp-12Ch] BYREF
  void *self[69]; // [esp+34h] [ebp-124h] BYREF
  int v6; // [esp+154h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v6 = 0;
  rf_string_construct_empty(destination);
  LOBYTE(v6) = 1;
  for ( i = 0; i < 16; ++i )
    unk_6E6B90[32 * i] = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "movemodes.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\gameplay\\movemode.cpp",
      222,
      "Unable to open movemodes.tbl");
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#movement modes");
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#end") )
  {
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$name:");
    rf_text_parser_read_delimited_rfstring(self, destination, 34, 34);
    v3 = &v1;
    for ( i = 0; i < 16; ++i )
    {
      if ( rf_string_equals_case_insensitive((int)destination, (&off_661598)[i]) )
      {
        v3 = &unk_6E6B90[32 * i];
        *v3 = 1;
        unk_6E6B94[8 * i] = i;
        break;
      }
    }
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$move x ref:");
    rf_text_parser_read_delimited_rfstring(self, destination, 34, 34);
    for ( i = 0; i < 4; ++i )
    {
      if ( rf_string_equals_case_insensitive((int)destination, (&off_6615D8)[i]) )
      {
        *((_DWORD *)v3 + 2) = i;
        break;
      }
    }
    if ( i == 4 )
      *((_DWORD *)v3 + 2) = 0;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$move y ref:");
    rf_text_parser_read_delimited_rfstring(self, destination, 34, 34);
    for ( i = 0; i < 4; ++i )
    {
      if ( rf_string_equals_case_insensitive((int)destination, (&off_6615D8)[i]) )
      {
        *((_DWORD *)v3 + 3) = i;
        break;
      }
    }
    if ( i == 4 )
      *((_DWORD *)v3 + 3) = 0;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$move z ref:");
    rf_text_parser_read_delimited_rfstring(self, destination, 34, 34);
    for ( i = 0; i < 4; ++i )
    {
      if ( rf_string_equals_case_insensitive((int)destination, (&off_6615D8)[i]) )
      {
        *((_DWORD *)v3 + 4) = i;
        break;
      }
    }
    if ( i == 4 )
      *((_DWORD *)v3 + 4) = 0;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$rot x ref:");
    rf_text_parser_read_delimited_rfstring(self, destination, 34, 34);
    for ( i = 0; i < 4; ++i )
    {
      if ( rf_string_equals_case_insensitive((int)destination, (&off_6615E8)[i]) )
      {
        *((_DWORD *)v3 + 5) = i;
        break;
      }
    }
    if ( i == 4 )
      *((_DWORD *)v3 + 5) = 0;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$rot y ref:");
    rf_text_parser_read_delimited_rfstring(self, destination, 34, 34);
    for ( i = 0; i < 4; ++i )
    {
      if ( rf_string_equals_case_insensitive((int)destination, (&off_6615E8)[i]) )
      {
        *((_DWORD *)v3 + 6) = i;
        break;
      }
    }
    if ( i == 4 )
      *((_DWORD *)v3 + 6) = 0;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$rot z ref:");
    rf_text_parser_read_delimited_rfstring(self, destination, 34, 34);
    for ( i = 0; i < 4; ++i )
    {
      if ( rf_string_equals_case_insensitive((int)destination, (&off_6615E8)[i]) )
      {
        *((_DWORD *)v3 + 7) = i;
        break;
      }
    }
    if ( i == 4 )
      *((_DWORD *)v3 + 7) = 0;
  }
  LOBYTE(v6) = 0;
  rf_string_destroy_buffer(destination);
  v6 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

