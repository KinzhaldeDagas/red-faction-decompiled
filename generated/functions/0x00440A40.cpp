// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00440A40 sub_440A40
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Entity personas.tbl registry, separate from HUD personas.16 preinitialized slots of56 bytes at6E6730: NameRFString8;12 Foley indices at+8..+34, all initialized-1. Required order Alert,Under Alert,Cower,Flee,Use Key, optionalHealing Gone/Heal Ignore,Timeout,Humming,Fight Single,Fight Mult,Panic. Count increments BEFORE >=16 test, so only15 authored records parse; encountering a16th leaves count16 with final slot still initialized. Do not claim16 parsed authored rows. Resolve each Foley name through446EE0 while loading.
void **sub_440A40()
{
  char *v0; // eax
  int name; // eax
  char *v2; // eax
  int v3; // eax
  char *v4; // eax
  int v5; // eax
  char *v6; // eax
  int v7; // eax
  char *v8; // eax
  int v9; // eax
  char *v10; // eax
  int v11; // eax
  char *v12; // eax
  int v13; // eax
  char *v14; // eax
  int v15; // eax
  char *v16; // eax
  int v17; // eax
  char *v18; // eax
  int v19; // eax
  char *v20; // eax
  int v21; // eax
  char *v22; // eax
  int v23; // eax
  void *v25[2]; // [esp+4h] [ebp-134h] BYREF
  void *destination; // [esp+Ch] [ebp-12Ch]
  int i; // [esp+10h] [ebp-128h]
  void *self[69]; // [esp+14h] [ebp-124h] BYREF
  int v29; // [esp+134h] [ebp-4h]

  atexit(rf_record56_table_clear_names_and_indices);
  for ( i = 0; i < 16; ++i )
  {
    rf_string_assign_from_cstr(&byte_6E6730[56 * i], (char *)&byte_633331);
    unk_6E6738[14 * i] = -1;
    unk_6E673C[14 * i] = -1;
    unk_6E6740[14 * i] = -1;
    unk_6E6744[14 * i] = -1;
    unk_6E6748[14 * i] = -1;
    unk_6E674C[14 * i] = -1;
    unk_6E6750[14 * i] = -1;
    unk_6E6754[14 * i] = -1;
    unk_6E6758[14 * i] = -1;
    unk_6E675C[14 * i] = -1;
    unk_6E6760[14 * i] = -1;
    dword_6E6764[14 * i] = -1;
  }
  rf_memory_text_parser_construct_empty(self);
  v29 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "personas.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\entity\\entity_personas.cpp",
      166,
      "Unable to open personas.tbl");
  unk_6E6728 = 0;
  rf_string_construct_empty(v25);
  LOBYTE(v29) = 1;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Personas");
  while ( !rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "#End") )
  {
    destination = &byte_6E6730[56 * unk_6E6728++];
    if ( unk_6E6728 >= 16 )
      break;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Name:");
    rf_text_parser_read_delimited_rfstring(self, destination, 34, 34);
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Alert:");
    rf_text_parser_read_delimited_rfstring(self, v25, 34, 34);
    v0 = (char *)rf_string_object_c_str_or_empty(v25);
    name = rf_foley_definition_find_name(v0);
    *((_DWORD *)destination + 2) = name;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Under Alert:");
    rf_text_parser_read_delimited_rfstring(self, v25, 34, 34);
    v2 = (char *)rf_string_object_c_str_or_empty(v25);
    v3 = rf_foley_definition_find_name(v2);
    *((_DWORD *)destination + 3) = v3;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Cower:");
    rf_text_parser_read_delimited_rfstring(self, v25, 34, 34);
    v4 = (char *)rf_string_object_c_str_or_empty(v25);
    v5 = rf_foley_definition_find_name(v4);
    *((_DWORD *)destination + 4) = v5;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Flee:");
    rf_text_parser_read_delimited_rfstring(self, v25, 34, 34);
    v6 = (char *)rf_string_object_c_str_or_empty(v25);
    v7 = rf_foley_definition_find_name(v6);
    *((_DWORD *)destination + 5) = v7;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Use Key:");
    rf_text_parser_read_delimited_rfstring(self, v25, 34, 34);
    v8 = (char *)rf_string_object_c_str_or_empty(v25);
    v9 = rf_foley_definition_find_name(v8);
    *((_DWORD *)destination + 6) = v9;
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "$Healing Gone:") )
    {
      rf_text_parser_read_delimited_rfstring(self, v25, 34, 34);
      v10 = (char *)rf_string_object_c_str_or_empty(v25);
      v11 = rf_foley_definition_find_name(v10);
      *((_DWORD *)destination + 7) = v11;
    }
    if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "$Heal Ignore:") )
    {
      rf_text_parser_read_delimited_rfstring(self, v25, 34, 34);
      v12 = (char *)rf_string_object_c_str_or_empty(v25);
      v13 = rf_foley_definition_find_name(v12);
      *((_DWORD *)destination + 8) = v13;
    }
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Timeout:");
    rf_text_parser_read_delimited_rfstring(self, v25, 34, 34);
    v14 = (char *)rf_string_object_c_str_or_empty(v25);
    v15 = rf_foley_definition_find_name(v14);
    *((_DWORD *)destination + 9) = v15;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Humming:");
    rf_text_parser_read_delimited_rfstring(self, v25, 34, 34);
    v16 = (char *)rf_string_object_c_str_or_empty(v25);
    v17 = rf_foley_definition_find_name(v16);
    *((_DWORD *)destination + 10) = v17;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Fight Single:");
    rf_text_parser_read_delimited_rfstring(self, v25, 34, 34);
    v18 = (char *)rf_string_object_c_str_or_empty(v25);
    v19 = rf_foley_definition_find_name(v18);
    *((_DWORD *)destination + 11) = v19;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Fight Mult:");
    rf_text_parser_read_delimited_rfstring(self, v25, 34, 34);
    v20 = (char *)rf_string_object_c_str_or_empty(v25);
    v21 = rf_foley_definition_find_name(v20);
    *((_DWORD *)destination + 12) = v21;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Panic:");
    rf_text_parser_read_delimited_rfstring(self, v25, 34, 34);
    v22 = (char *)rf_string_object_c_str_or_empty(v25);
    v23 = rf_foley_definition_find_name(v22);
    *((_DWORD *)destination + 13) = v23;
  }
  rf_memory_text_parser_close_buffer(self);
  LOBYTE(v29) = 0;
  rf_string_destroy_buffer(v25);
  v29 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

