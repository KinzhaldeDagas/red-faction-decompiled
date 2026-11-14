// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DA2B0 rf_console_set_player_display_name
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): No arguments; console globals supply execute1809818/help1809814. Execute nonzero requires nonNULL local player or returns immediately (including skipping help); reads string argument with mask2,required1. Empty input sets help=1. Nonempty constructs8-byte owned RFString BY VALUE in outgoing stack space and passes its two DWORDs to verified name setter, which consumes it; false AL returns immediately. On success, multiplayer EXACT1 sends name update48F7B0; if multiplayer and server-authority both still EXACT1 and local player nonNULL, sets session RFString704EC0 to player name8 concatenated with apostrophe-s game, then destroys temporary including SEH cleanup. Help prints localized
// pointer88E210 then sprintf into40-byte stack buffer with format five spaces/name <%s>/newline and localized pointer88E144. Constant XOR branches force localized pointers, hardcoded fallback strings unreachable; no sprintf length cap or own local feedback on successful rename.
void rf_console_set_player_display_name()
{
  int v0[6]; // [esp-8h] [ebp-8Ch] BYREF
  void *v1; // [esp+10h] [ebp-74h]
  _DWORD *v3; // [esp+18h] [ebp-6Ch]
  int v4; // [esp+1Ch] [ebp-68h]
  void *v5; // [esp+24h] [ebp-60h]
  const char *v6; // [esp+28h] [ebp-5Ch]
  int v7; // [esp+2Ch] [ebp-58h]
  void *v8; // [esp+34h] [ebp-50h]
  char *v9; // [esp+38h] [ebp-4Ch]
  _BYTE v10[8]; // [esp+3Ch] [ebp-48h] BYREF
  int *v11; // [esp+44h] [ebp-40h]
  char Buffer[40]; // [esp+48h] [ebp-3Ch] BYREF
  int v13; // [esp+74h] [ebp-10h]
  int v14; // [esp+80h] [ebp-4h]

  if ( dword_1809818 )
  {
    if ( !rf_local_fpgun_player )
      return;
    rf_console_read_argument_validate_type_mask(2, 1);
    v8 = &unk_1809821;
    v9 = &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1;
    v7 = v9 - (char *)&unk_1809821;
    if ( v9 == (char *)&unk_1809821 )
    {
      dword_1809814 = 1;
    }
    else
    {
      v6 = &MEMORY[0x1809820];
      v5 = &unk_1809821;
      v6 += strlen(v6) + 1;
      v4 = v6 - (const char *)&unk_1809821;
      v13 = v6 - (const char *)&unk_1809821;
      v11 = v0;
      v3 = rf_string_construct_from_cstr(v0, &MEMORY[0x1809820]);
      if ( !rf_player_set_display_name_from_owned_string(v0[0], (char *)v0[1]) )
        return;
      if ( rf_multiplayer_runtime_mode == 1 )
      {
        rf_multiplayer_send_local_display_name();
        if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 && rf_local_fpgun_player )
        {
          v1 = rf_string_concat_object_cstr(v10, (_DWORD *)(rf_local_fpgun_player + 8), "'s game");
          v0[5] = (int)v1;
          v14 = 0;
          rf_string_assign_from_object(unk_704EC0, (int)v1);
          v14 = -1;
          rf_string_destroy_buffer(v10);
        }
      }
    }
  }
  if ( dword_1809814 )
  {
    v0[4] = (int)dword_88E210;
    rf_console_output_append_text_lines(dword_88E210, nullptr);
    v0[3] = (int)dword_88E144;
    sprintf(Buffer, "     name <%s>\n", dword_88E144);
    rf_console_output_append_text_lines(Buffer, nullptr);
  }
}

