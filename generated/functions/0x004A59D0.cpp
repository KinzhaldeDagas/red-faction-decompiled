// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A59D0 rf_client_apply_leave_limbo_payload22
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(payload), runtime1/authority0. Registry22=leave_limbo. Reads NUL level filename with unbounded scan,strncpy255 and forced destination[254]=0; cursor uses uint16(full source
// length+1),not truncated display length. Assigns6FC3AC,reads raw CRC DWORD into6FC3A8 (no verification),then passes level plus empty save-name as two owned8-byte RFStrings to
// transition helper (16-byte cleanup,SEH).
// If local net flags20 set, clears it then requests panel5 unforced0. Otherwise resets auxiliary level-name string and returns zero. No local/net-null/payload-length guard, player
// allocation or runtime reinitialization; panel refusal does not restore flag. Paired sender5820 is already verified.
int __cdecl rf_client_apply_leave_limbo_payload22(const char *a1)
{
  int result; // eax
  int v2; // eax
  int v3[2]; // [esp-10h] [ebp-150h] BYREF
  int v4[5]; // [esp-8h] [ebp-148h] BYREF
  _DWORD *v5; // [esp+Ch] [ebp-134h]
  int v6; // [esp+10h] [ebp-130h]
  const char *v7; // [esp+18h] [ebp-128h]
  const char *v8; // [esp+1Ch] [ebp-124h]
  int *v9; // [esp+20h] [ebp-120h]
  void *v10; // [esp+24h] [ebp-11Ch]
  __int16 v11; // [esp+28h] [ebp-118h]
  char Destination[256]; // [esp+2Ch] [ebp-114h] BYREF
  int v13; // [esp+130h] [ebp-10h]
  int v14; // [esp+13Ch] [ebp-4h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    v13 = 0;
    v8 = a1;
    v7 = a1 + 1;
    v8 += strlen(v8) + 1;
    v6 = v8 - (a1 + 1);
    v11 = (_WORD)v8 - ((_WORD)a1 + 1);
    strncpy(Destination, a1, 0xFFu);
    Destination[254] = 0;
    v13 = (unsigned __int16)(v13 + (_WORD)v8 - (_WORD)a1);
    rf_string_assign_from_cstr(unk_6FC3AC, Destination);
    dword_6FC3A8 = *(_DWORD *)&a1[v13];
    v13 += 4;
    v10 = v4;
    v5 = rf_string_construct_from_cstr(v4, (char *)&byte_63ACA3);
    v4[4] = (int)v5;
    v14 = 0;
    v9 = v3;
    rf_string_copy_construct_from_object(v3, (char **)unk_6FC3AC);
    v4[3] = v2;
    v14 = -1;
    rf_level_transition_assign_level_and_save_strings(v3[0], (char *)v3[1], v4[0], (char *)v4[1]);
    if ( (*(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) & 0x20) != 0 )
    {
      *(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) &= ~0x20u;
      return rf_ui_request_panel_immediate(5, 0);
    }
    else
    {
      rf_level_reset_auxiliary_name_string();
      return 0;
    }
  }
  return result;
}

