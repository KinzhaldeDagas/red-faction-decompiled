// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048E0B0 rf_multiplayer_rules_parse
// UNREALRED VERIFIED [respawn-decode]: Parses $Weapons Stay as game flag 0x10 and $Force Respawn as game flag 0x20.
// UNREALRED VERIFIED [respawn-surrounding]: $Fall Damage sets multiplayer game-rule bit 0x80 when enabled and clears it when disabled. This parser clears internal bit 0x100 in either branch. $Force Respawn remains independent at bit 0x20.
int rf_multiplayer_rules_parse()
{
  char v0; // cl
  const char *v1; // eax
  const char *v2; // eax
  const char *v3; // eax
  char *v4; // eax
  const char *v5; // eax
  char v6; // cl
  const char *v7; // eax
  const char *v8; // eax
  const char *v9; // eax
  char *v10; // eax
  char *v11; // eax
  int v12; // eax
  const char *v13; // eax
  const char *v14; // eax
  char v15; // cl
  const char *v16; // eax
  char v17; // cl
  char v19; // cl
  int v20; // [esp+0h] [ebp-544h] BYREF
  int v21; // [esp+4h] [ebp-540h]
  char *v22; // [esp+10h] [ebp-534h]
  char *v23; // [esp+14h] [ebp-530h]
  char *v24; // [esp+18h] [ebp-52Ch]
  int v25; // [esp+1Ch] [ebp-528h]
  int signed_decimal_or_hex_integer; // [esp+20h] [ebp-524h]
  char *v27; // [esp+24h] [ebp-520h]
  void *v28; // [esp+28h] [ebp-51Ch]
  void *v29; // [esp+2Ch] [ebp-518h]
  int *v30; // [esp+30h] [ebp-514h]
  int *v31; // [esp+34h] [ebp-510h]
  _DWORD *v32; // [esp+38h] [ebp-50Ch]
  _DWORD *v33; // [esp+3Ch] [ebp-508h]
  void *v34; // [esp+40h] [ebp-504h]
  void *v35; // [esp+44h] [ebp-500h]
  char *v36; // [esp+48h] [ebp-4FCh]
  char *v37; // [esp+4Ch] [ebp-4F8h]
  char *v38; // [esp+54h] [ebp-4F0h]
  char v39; // [esp+5Bh] [ebp-4E9h]
  char *v40; // [esp+5Ch] [ebp-4E8h]
  char *v41; // [esp+60h] [ebp-4E4h]
  const char *argument; // [esp+64h] [ebp-4E0h]
  char *Format; // [esp+68h] [ebp-4DCh]
  int *v44; // [esp+6Ch] [ebp-4D8h]
  _BYTE v45[8]; // [esp+70h] [ebp-4D4h] BYREF
  _BYTE v46[8]; // [esp+78h] [ebp-4CCh] BYREF
  _BYTE v47[8]; // [esp+80h] [ebp-4C4h] BYREF
  _BYTE v48[8]; // [esp+88h] [ebp-4BCh] BYREF
  char *v49[2]; // [esp+90h] [ebp-4B4h] BYREF
  CHAR Buffer[4]; // [esp+98h] [ebp-4ACh] BYREF
  void *v51; // [esp+9Ch] [ebp-4A8h]
  DWORD pcbBuffer; // [esp+DCh] [ebp-468h] BYREF
  unsigned int v53; // [esp+E0h] [ebp-464h]
  _DWORD v54[2]; // [esp+E4h] [ebp-460h] BYREF
  int v55; // [esp+ECh] [ebp-458h]
  const char *v56[2]; // [esp+F0h] [ebp-454h] BYREF
  int case_insensitive; // [esp+F8h] [ebp-44Ch]
  int destination[2]; // [esp+FCh] [ebp-448h] BYREF
  char v59; // [esp+107h] [ebp-43Dh]
  char String2[512]; // [esp+108h] [ebp-43Ch] BYREF
  int v61[70]; // [esp+308h] [ebp-23Ch] BYREF
  void *self[69]; // [esp+420h] [ebp-124h] BYREF
  int v63; // [esp+540h] [ebp-4h]

  v59 = 0;
  rf_vfile_construct_unopened(v61);
  v63 = 0;
  if ( rf_command_line_bool_option_is_enabled(byte_88E4D0) )
  {
    if ( unk_88E4E0 )
    {
      argument = rf_command_line_option_get_argument(byte_88E4D0);
      v41 = String2;
      v40 = String2;
      do
      {
        v39 = *argument;
        *v41 = v39;
        ++argument;
        ++v41;
      }
      while ( v39 );
    }
    else
    {
      String2[0] = 0;
      Format = dword_88E188;
      rf_console_printf_unbounded_stack2048(dword_88E188);
      v59 = 1;
    }
  }
  else
  {
    String2[0] = 0;
    v38 = dword_88E18C;
    rf_console_printf_unbounded_stack2048(dword_88E18C);
    v59 = 1;
  }
  rf_memory_text_parser_construct_empty(self);
  LOBYTE(v63) = 1;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "dedicated_server.txt", byte_98967F, 0) )
  {
    rf_console_printf_unbounded_stack2048(unk_88E190);
    v21 = 1;
    rf_console_wait_for_input_if_enabled_then_exit_one(v0);
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "#Dedicated Server Options");
  while ( 1 )
  {
    if ( !rf_text_parser_find_substring_before_optional_stop((char **)self, "$Name:", nullptr) )
    {
      rf_text_parser_find_substring_before_optional_stop((char **)self, "#End", nullptr);
      rf_console_printf_unbounded_stack2048(unk_88E1A0, String2);
      rf_memory_text_parser_close_buffer(self);
      v21 = 1;
      rf_console_wait_for_input_if_enabled_then_exit_one(v19);
    }
    rf_string_construct_empty(destination);
    LOBYTE(v63) = 2;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Name:");
    rf_text_parser_read_delimited_rfstring(self, destination, 34, 34);
    if ( v59 || rf_string_equals_case_insensitive((int)destination, String2) )
      break;
    LOBYTE(v63) = 1;
    rf_string_destroy_buffer(destination);
  }
  v37 = dword_88E194;
  rf_console_printf_unbounded_stack2048(dword_88E194);
  v36 = (char *)unk_88E198;
  v1 = rf_string_object_c_str_or_empty(destination);
  rf_console_printf_unbounded_stack2048(v36, v1);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Server Name:");
  rf_text_parser_read_delimited_rfstring(self, unk_704EC0, 34, 34);
  v2 = rf_string_object_c_str_or_empty(unk_704EC0);
  rf_console_printf_unbounded_stack2048("Server name: %s\n", v2);
  case_insensitive = rf_string_find_case_insensitive(unk_704EC0, "$ME", 0);
  if ( case_insensitive > -1 )
  {
    pcbBuffer = 63;
    if ( !GetUserNameA(Buffer, &pcbBuffer) )
    {
      *(_DWORD *)Buffer = 1852534389;
      v51 = &unk_6E776F;
    }
    v53 = rf_string_length_from_cstr((const char **)unk_704EC0);
    v35 = rf_string_right_count(unk_704EC0, v48, v53 - (case_insensitive + 3));
    v34 = v35;
    LOBYTE(v63) = 3;
    v33 = rf_string_left_count((char **)unk_704EC0, v47, case_insensitive);
    v32 = v33;
    LOBYTE(v63) = 4;
    v31 = (int *)rf_string_concat_object_cstr(v46, v33, Buffer);
    v30 = v31;
    LOBYTE(v63) = 5;
    v29 = rf_string_concat_two_objects(v45, v31, (int)v35);
    v28 = v29;
    LOBYTE(v63) = 6;
    rf_string_assign_from_object(unk_704EC0, (int)v29);
    LOBYTE(v63) = 5;
    rf_string_destroy_buffer(v45);
    LOBYTE(v63) = 4;
    rf_string_destroy_buffer(v46);
    LOBYTE(v63) = 3;
    rf_string_destroy_buffer(v47);
    LOBYTE(v63) = 2;
    rf_string_destroy_buffer(v48);
    v3 = rf_string_object_c_str_or_empty(unk_704EC0);
    rf_console_printf_unbounded_stack2048("Server name = '%s'\n", v3);
  }
  rf_string_construct_empty(v54);
  LOBYTE(v63) = 7;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Game Type:");
  rf_text_parser_read_delimited_rfstring(self, v54, 34, 34);
  v4 = (char *)rf_string_object_c_str_or_empty(v54);
  unk_704ED4 = rf_multiplayer_game_mode_index_from_name(v4);
  if ( (unsigned int)unk_704ED4 > 2 )
  {
    v27 = (char *)unk_88E19C;
    v5 = rf_string_object_c_str_or_empty(v54);
    rf_console_printf_unbounded_stack2048(v27, v5);
    rf_memory_text_parser_close_buffer(self);
    v21 = 1;
    rf_console_wait_for_input_if_enabled_then_exit_one(v6);
  }
  v21 = unk_704ED4;
  v7 = rf_string_object_c_str_or_empty(v54);
  rf_console_printf_unbounded_stack2048("Game type: %s (%d)\n", v7, v21);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Max Players:");
  *(_DWORD *)unk_704EDC = rf_text_parser_read_signed_decimal_or_hex_integer(self);
  rf_integer_clamp_in_place(unk_704EDC, 2, 32);
  rf_console_printf_unbounded_stack2048("Max players: %d\n", *(_DWORD *)unk_704EDC);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Password:");
  rf_text_parser_read_delimited_rfstring(self, dword_704EC8, 34, 34);
  v8 = rf_string_object_c_str_or_empty(dword_704EC8);
  rf_console_printf_unbounded_stack2048("Password: %s\n", v8);
  rf_string_construct_empty(v56);
  LOBYTE(v63) = 8;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Rcon Password:");
  rf_text_parser_read_delimited_rfstring(self, v56, 34, 34);
  if ( (int)rf_string_length_from_cstr(v56) > 16 )
  {
    byte_704E94[0] = 0;
  }
  else
  {
    v9 = rf_string_object_c_str_or_empty(v56);
    sprintf(byte_704E94, "%s", v9);
  }
  rf_console_printf_unbounded_stack2048("Rcon Password : %s\n", byte_704E94);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Max Time:");
  signed_decimal_or_hex_integer = rf_text_parser_read_signed_decimal_or_hex_integer(self);
  *(float *)&dword_704EE4 = (float)signed_decimal_or_hex_integer;
  rf_float_clamp_in_place((float *)&dword_704EE4, 5.0, 60.0);
  rf_console_printf_unbounded_stack2048("Max Time: %d minutes\n", (int)*(float *)&dword_704EE4);
  *(float *)&dword_704EE4 = *(float *)&dword_704EE4 * 60.0;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Max Kills:");
  *(_DWORD *)unk_704EE8 = rf_text_parser_read_signed_decimal_or_hex_integer(self);
  rf_integer_clamp_in_place(unk_704EE8, 1, 100);
  rf_console_printf_unbounded_stack2048("Max Kills: %d\n", *(_DWORD *)unk_704EE8);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Max Captures:");
  *(_DWORD *)unk_704EF0 = rf_text_parser_read_signed_decimal_or_hex_integer(self);
  rf_integer_clamp_in_place(unk_704EF0, 1, 25);
  rf_console_printf_unbounded_stack2048("Max Captures: %d\n", *(_DWORD *)unk_704EF0);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Geomod Limit:");
  *(_DWORD *)unk_704EEC = rf_text_parser_read_signed_decimal_or_hex_integer(self);
  rf_integer_clamp_in_place(unk_704EEC, 0, 128);
  rf_console_printf_unbounded_stack2048("Geomod Limit: %d\n", *(_DWORD *)unk_704EEC);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Team Damage:");
  if ( rf_text_parser_read_boolean_word_prefix((const char **)self) )
  {
    rf_console_printf_unbounded_stack2048("Team Damage: true\n");
    rf_multiplayer_game_flags |= 0x40u;
    rf_multiplayer_game_flags |= 0x200u;
  }
  else
  {
    rf_console_printf_unbounded_stack2048("Team Damage: false\n");
    rf_multiplayer_game_flags &= ~0x40u;
    rf_multiplayer_game_flags &= ~0x200u;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Fall Damage:");
  if ( rf_text_parser_read_boolean_word_prefix((const char **)self) )
  {
    rf_console_printf_unbounded_stack2048("Fall Damage: true\n");
    rf_multiplayer_game_flags |= 0x80u;
  }
  else
  {
    rf_console_printf_unbounded_stack2048("Fall Damage: false\n");
    rf_multiplayer_game_flags &= ~0x80u;
  }
  rf_multiplayer_game_flags &= ~0x100u;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Weapons Stay:");
  if ( rf_text_parser_read_boolean_word_prefix((const char **)self) )
  {
    rf_console_printf_unbounded_stack2048("Weapons Stay: true\n");
    rf_multiplayer_game_flags |= 0x10u;
  }
  else
  {
    rf_console_printf_unbounded_stack2048("Weapons Stay: false\n");
    rf_multiplayer_game_flags &= ~0x10u;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Force Respawn:");
  if ( rf_text_parser_read_boolean_word_prefix((const char **)self) )
  {
    rf_console_printf_unbounded_stack2048("Force Respawn: true\n");
    rf_multiplayer_game_flags |= 0x20u;
  }
  else
  {
    rf_console_printf_unbounded_stack2048("Force Respawn: false\n");
    rf_multiplayer_game_flags &= ~0x20u;
  }
  rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Balance Teams:");
  if ( rf_text_parser_read_boolean_word_prefix((const char **)self) )
  {
    rf_console_printf_unbounded_stack2048("Balance Teams: true\n");
    rf_multiplayer_game_flags |= 0x2000u;
  }
  else
  {
    rf_console_printf_unbounded_stack2048("Balance Teams: false\n");
    rf_multiplayer_game_flags &= ~0x2000u;
  }
  dword_704EFC = -1;
  rf_rfstring_array8_clear_and_release(unk_704F00);
  v55 = 0;
  while ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "$Map:") )
  {
    rf_string_construct_empty(v49);
    LOBYTE(v63) = 9;
    rf_text_parser_read_delimited_rfstring(self, v49, 34, 34);
    v21 = (int)byte_98967F;
    v10 = (char *)rf_string_object_c_str_or_empty(v49);
    if ( rf_vfile_resolve_open_source((int)v61, v10, v21) == 1 )
    {
      v21 = unk_704ED4;
      v11 = (char *)rf_string_object_c_str_or_empty(v49);
      if ( !rf_level_name_matches_game_mode_prefix(v11, v21) )
      {
        v24 = (char *)unk_88E270;
        v14 = rf_string_object_c_str_or_empty(v49);
        rf_console_printf_unbounded_stack2048(v24, v14);
        rf_memory_text_parser_close_buffer(self);
        v21 = 1;
        rf_console_wait_for_input_if_enabled_then_exit_one(v15);
      }
      ++v55;
      v44 = &v20;
      rf_string_copy_construct_from_object(&v20, v49);
      v25 = v12;
      rf_rfstring_array8_append_owned(unk_704F00, v20, v21);
      v13 = rf_string_object_c_str_or_empty(v49);
      rf_console_printf_unbounded_stack2048("Level: %s\n", v13);
    }
    else
    {
      v23 = "Could not find map %s\n";
      v16 = rf_string_object_c_str_or_empty(v49);
      rf_console_printf_unbounded_stack2048(v23, v16);
    }
    LOBYTE(v63) = 8;
    rf_string_destroy_buffer(v49);
  }
  rf_console_printf_unbounded_stack2048("=======================================================\n");
  rf_memory_text_parser_close_buffer(self);
  if ( v55 <= 0 )
  {
    v22 = "Server map list is empty! Aborting...\n";
    rf_console_printf_unbounded_stack2048("Server map list is empty! Aborting...\n");
    v21 = 1;
    rf_console_wait_for_input_if_enabled_then_exit_one(v17);
  }
  LOBYTE(v63) = 7;
  rf_string_destroy_buffer(v56);
  LOBYTE(v63) = 2;
  rf_string_destroy_buffer(v54);
  LOBYTE(v63) = 1;
  rf_string_destroy_buffer(destination);
  LOBYTE(v63) = 0;
  rf_memory_text_parser_destroy_buffer_adapter(self);
  v63 = -1;
  return rf_vfile_destruct_close_if_open(v61);
}

