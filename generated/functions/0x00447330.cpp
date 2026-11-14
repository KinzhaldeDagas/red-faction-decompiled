// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00447330 rf_console_command_level_change
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No stack arguments; console globals supply input. If1809818!=0, reads one argument with56F950(mask2,preserveCase0), whose
// rejection nonlocally aborts; then ANY zero multiplayer-mode byte exits immediately, bypassing even existing help. Empty normalized token1809820 sets help DWORD1809814=1. Nonempty
// token becomes a local RFString, is rewritten with '.rfl' through an unbounded last-dot suffix replacement into a512-byte local buffer, then checked through a local VFile resolver.
// Resolver AL0 prints the missing-file diagnostic, destroys both locals and returns before help. After successful resolution RE-READS multiplayer mode: nonzero requires EXACT mode1
// AND EXACT server-authority byte1, otherwise prints server-only diagnostic; admitted requests validate level/game-mode prefix using LIVE704ED4 and call4A5600 on any nonzero
// predicate AL, otherwise print mismatch. If the mode became zero during intervening delegates, constructs TWO8-byte by-value RFStrings (level copy, empty save) and passes all16
// bytes to4798E0, which assigns globals and destroys both argument strings; then re-reads mode for optional teardown, clears level cache, and requests panel5 with force0. Destroys
// VFile then local RFString. Finally, when1809814!=0, outputs localized88E210 and an unbounded sprintf into40-byte buffer using localized88E298 and '     level <%s>'; no help reset
// here. Zero1809818 skips parsing/action and reaches this help gate. C++ unwind map covers local string, VFile and already-constructed by-value empty-save object; no file-load/world
// transition is performed directly.
void rf_console_command_level_change()
{
  char *v0; // eax
  char *v1; // eax
  const char *v2; // eax
  int v3; // eax
  int v4[2]; // [esp-10h] [ebp-39Ch] BYREF
  int v5[7]; // [esp-8h] [ebp-394h] BYREF
  _DWORD *v6; // [esp+14h] [ebp-378h]
  int v7; // [esp+18h] [ebp-374h]
  void *v8; // [esp+20h] [ebp-36Ch]
  char *v9; // [esp+24h] [ebp-368h]
  int *v10; // [esp+28h] [ebp-364h]
  void *v11; // [esp+2Ch] [ebp-360h]
  char Buffer[40]; // [esp+30h] [ebp-35Ch] BYREF
  char *v13[2]; // [esp+58h] [ebp-334h] BYREF
  char String1[512]; // [esp+60h] [ebp-32Ch] BYREF
  int self[71]; // [esp+260h] [ebp-12Ch] BYREF
  int v16; // [esp+388h] [ebp-4h]

  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(2, 0);
    if ( !rf_multiplayer_runtime_mode )
      return;
    v8 = &unk_1809821;
    v9 = &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1;
    v7 = v9 - (char *)&unk_1809821;
    if ( v9 == (char *)&unk_1809821 )
    {
      dword_1809814 = 1;
    }
    else
    {
      rf_string_construct_from_cstr(v13, &MEMORY[0x1809820]);
      v16 = 0;
      v0 = (char *)rf_string_object_c_str_or_empty(v13);
      rf_path_replace_last_dot_suffix_unbounded(String1, v0, ".rfl");
      rf_string_assign_from_cstr(v13, String1);
      rf_vfile_construct_unopened(self);
      LOBYTE(v16) = 1;
      v1 = (char *)rf_string_object_c_str_or_empty(v13);
      if ( !rf_vfile_resolve_open_source((int)self, v1, (int)byte_98967F) )
      {
        v2 = rf_string_object_c_str_or_empty(v13);
        rf_console_printf_unbounded_stack2048("Couldn't find file '%s'\n", v2);
        LOBYTE(v16) = 0;
        rf_vfile_destruct_close_if_open(self);
        v16 = -1;
        rf_string_destroy_buffer(v13);
        return;
      }
      if ( rf_multiplayer_runtime_mode )
      {
        if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
        {
          if ( rf_level_name_matches_game_mode_prefix(String1, unk_704ED4) )
            sub_4A5600(String1);
          else
            rf_console_output_append_text_lines("Sorry, that level doesn't match the current game type.\n", nullptr);
        }
        else
        {
          rf_console_output_append_text_lines("Sorry, only the server can change levels.\n", nullptr);
        }
      }
      else
      {
        v11 = v5;
        v6 = rf_string_construct_from_cstr(v5, (char *)&byte_633C9D);
        v5[6] = (int)v6;
        LOBYTE(v16) = 2;
        v10 = v4;
        rf_string_copy_construct_from_object(v4, v13);
        v5[5] = v3;
        LOBYTE(v16) = 1;
        rf_level_transition_assign_level_and_save_strings(v4[0], (char *)v4[1], v5[0], (char *)v5[1]);
        if ( rf_multiplayer_runtime_mode )
          rf_multiplayer_runtime_teardown();
        rf_level_state_cache_clear();
        rf_ui_request_panel_immediate(5, 0);
      }
      LOBYTE(v16) = 0;
      rf_vfile_destruct_close_if_open(self);
      v16 = -1;
      rf_string_destroy_buffer(v13);
    }
  }
  if ( dword_1809814 )
  {
    v5[4] = (int)dword_88E210;
    rf_console_output_append_text_lines(dword_88E210, nullptr);
    v5[3] = (int)dword_88E298;
    sprintf(Buffer, "     level <%s>", dword_88E298);
    rf_console_output_append_text_lines(Buffer, nullptr);
  }
}

