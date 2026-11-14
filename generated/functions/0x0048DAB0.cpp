// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048DAB0 rf_multiplayer_process_initialize
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ban-list validation and wildcard matching, native text-reader capacity and list ownership, multiplayer process initialization and character-cache ABI): 
// Cdecl process-level multiplayer subsystem initializer. Constructs memory text parser; opens pc_multi.tbl using path context98967F,flags0. Nonzero failure enters fatal-message
// loop(source multi.cpp,line1709,'Unable to open pc_multi.tbl'); normal success native pushes parser pointer to49B200 and cleans4,even though pseudocode may hide argument. Closes
// parser buffer. Sets FLOAT704EE4=-1,DWORD704EE8=-1,704EEC=-1,704EF0=0,704EFC=-1; clears/release helper45DD20(receiver704F00) resets two count fields and backing pointer.
// If config RFString704EAC length>0,opens that path with contextDWORD88E3F4,flags0. On success constructs temporary RFString and repeatedly reads CR lines; only AL EXACT1 invokes
// console_execute_command_line,then closes parser and destroys temporary. Config-open failure silently skips commands. No independent command filtering/result checking in this
// routine.
// Then calls,in order:banlist_load48D910,49FD10,491820,4B0E70,4ADB50,49CD30,4ACCE0; these are delegated subsystem steps,not inferred from adjacent names. Native4ADB50 call has NO
// pushed args (pseudocode ECX parameter artifact). Loads RedJack.vbm(-1,1) into global66286C; ignores bitmap failure. Final parser destructor normal/unwind. Does not itself set
// multiplayer runtime mode/authority or create world objects. No stable Boolean return.
void **rf_multiplayer_process_initialize()
{
  const char *v0; // eax
  const char *v1; // eax
  void *v3; // [esp-8h] [ebp-138h]
  _DWORD v4[2]; // [esp+4h] [ebp-12Ch] BYREF
  void *self[69]; // [esp+Ch] [ebp-124h] BYREF
  int v6; // [esp+12Ch] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v6 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "pc_multi.tbl", byte_98967F, 0) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\multi\\multi.cpp",
      1709,
      "Unable to open pc_multi.tbl");
  sub_49B200();
  rf_memory_text_parser_close_buffer(self);
  *(float *)&dword_704EE4 = -1.0;
  *(_DWORD *)unk_704EE8 = -1;
  *(_DWORD *)unk_704EEC = -1;
  *(_DWORD *)unk_704EF0 = 0;
  dword_704EFC = -1;
  rf_rfstring_array8_clear_and_release(unk_704F00);
  if ( (int)rf_string_length_from_cstr((const char **)&unk_704EAC) > 0 )
  {
    v3 = (void *)dword_88E3F4;
    v0 = rf_string_object_c_str_or_empty(&unk_704EAC);
    if ( !rf_memory_text_parser_open_file_to_owned_buffer(self, v0, v3, 0) )
    {
      rf_string_construct_empty(v4);
      LOBYTE(v6) = 1;
      while ( rf_text_parser_read_cr_line_into_rfstring((int)self, v4) == 1 )
      {
        v1 = rf_string_object_c_str_or_empty(v4);
        rf_console_execute_command_line(v1);
      }
      rf_memory_text_parser_close_buffer(self);
      LOBYTE(v6) = 0;
      rf_string_destroy_buffer(v4);
    }
  }
  rf_banlist_load_text_file();
  rf_multiplayer_packet_state_initialize_noop();
  rf_respawn_register_name_cleanup_at_exit();
  rf_multiplayer_initialize_team_names_and_colors();
  rf_multiplayer_load_network_update_rate();
  rf_multiplayer_hud_load_resources_and_register_cleanup();
  rf_powerup_nodes_initialize_and_register_cleanup();
  dword_66286C = rf_bitmap_load_with_optional_mipmap_generation("RedJack.vbm", (void *)0xFFFFFFFF, 1);
  v6 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

