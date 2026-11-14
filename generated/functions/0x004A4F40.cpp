// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A4F40 rf_multiplayer_apply_left_game_payload7
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(payload), ignores dispatcher's extra source endpoint. No own entry mode/authority/null/length check or claimed-id/source binding. Reads id/reason unsigned bytes; idFF is
// normal lookup. If player exists, style5 notification appends suffix to name: reason1=>88DF50(left),2=>88DF4C(kicked),4=>88E204(incompatible),5=>88E218(between
// levels),6=>88E21C(timeout),7=>literal missing-level text; all others=>88DF54(unknown). Original seven-entry jump table verified, case3 is default. Two owned RFStrings/style
// occupy20 native argument bytes with SEH cleanup.
// Then only runtime1/authority1 drops carried CTF flag if either carrier matches, and removes player's flag nodes4AD410. Local player: reason modal88E208 FIRST,teardown(),panel13
// forced1. Remote: delegates remove_player_and_mark_object. Finally RECHECKS runtime1/authority1 and rebroadcasts raw id/reason through packet7, EVEN if player lookup failed;
// teardown can disable this final branch. No reason normalization or rollback after modal/send failure.
int __cdecl rf_multiplayer_apply_left_game_payload7(char *a1)
{
  int result; // eax
  int v2; // [esp-14h] [ebp-E4h] BYREF
  int v3; // [esp-10h] [ebp-E0h]
  int v4; // [esp-Ch] [ebp-DCh]
  int v5[6]; // [esp-8h] [ebp-D8h] BYREF
  _DWORD *v6; // [esp+10h] [ebp-C0h]
  const char *v7; // [esp+14h] [ebp-BCh]
  void *v8; // [esp+18h] [ebp-B8h]
  _DWORD *v9; // [esp+1Ch] [ebp-B4h]
  _DWORD *v10; // [esp+20h] [ebp-B0h]
  const char *v11; // [esp+24h] [ebp-ACh]
  void *v12; // [esp+28h] [ebp-A8h]
  _DWORD *v13; // [esp+2Ch] [ebp-A4h]
  _DWORD *v14; // [esp+30h] [ebp-A0h]
  const char *v15; // [esp+34h] [ebp-9Ch]
  void *v16; // [esp+38h] [ebp-98h]
  _DWORD *v17; // [esp+3Ch] [ebp-94h]
  _DWORD *v18; // [esp+40h] [ebp-90h]
  const char *v19; // [esp+44h] [ebp-8Ch]
  void *v20; // [esp+48h] [ebp-88h]
  _DWORD *v21; // [esp+4Ch] [ebp-84h]
  _DWORD *v22; // [esp+50h] [ebp-80h]
  const char *v23; // [esp+54h] [ebp-7Ch]
  void *v24; // [esp+58h] [ebp-78h]
  _DWORD *v25; // [esp+5Ch] [ebp-74h]
  _DWORD *v26; // [esp+60h] [ebp-70h]
  const char *v27; // [esp+64h] [ebp-6Ch]
  void *v28; // [esp+68h] [ebp-68h]
  _DWORD *v29; // [esp+6Ch] [ebp-64h]
  _DWORD *v30; // [esp+70h] [ebp-60h]
  const char *v31; // [esp+74h] [ebp-5Ch]
  int v32; // [esp+78h] [ebp-58h]
  int *v33; // [esp+7Ch] [ebp-54h]
  void *v34; // [esp+80h] [ebp-50h]
  int *v35; // [esp+84h] [ebp-4Ch]
  void *v36; // [esp+88h] [ebp-48h]
  int *v37; // [esp+8Ch] [ebp-44h]
  void *v38; // [esp+90h] [ebp-40h]
  int *v39; // [esp+94h] [ebp-3Ch]
  void *v40; // [esp+98h] [ebp-38h]
  int *v41; // [esp+9Ch] [ebp-34h]
  void *v42; // [esp+A0h] [ebp-30h]
  int *v43; // [esp+A4h] [ebp-2Ch]
  void *v44; // [esp+A8h] [ebp-28h]
  int *v45; // [esp+ACh] [ebp-24h]
  void *v46; // [esp+B0h] [ebp-20h]
  char *v47; // [esp+B4h] [ebp-1Ch]
  unsigned __int8 v48; // [esp+BAh] [ebp-16h]
  char v49; // [esp+BBh] [ebp-15h]
  _DWORD *v50; // [esp+BCh] [ebp-14h]
  int v51; // [esp+C0h] [ebp-10h]
  int v52; // [esp+CCh] [ebp-4h]

  v51 = 0;
  v49 = *a1;
  v51 = 1;
  v48 = a1[1];
  v51 = 2;
  v50 = rf_player_find_by_network_id(v49);
  if ( v50 )
  {
    v32 = v48 - 1;
    switch ( v48 )
    {
      case 1u:
        v23 = (const char *)unk_88DF50;
        v42 = v5;
        v22 = rf_string_construct_from_cstr(v5, (char *)&byte_63AC0F);
        v21 = v22;
        v52 = 2;
        v4 = 5;
        v41 = &v2;
        v20 = rf_string_concat_object_cstr(&v2, v50 + 2, v23);
        v52 = -1;
        rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
        break;
      case 2u:
        v31 = (const char *)unk_88DF4C;
        v46 = v5;
        v30 = rf_string_construct_from_cstr(v5, (char *)&byte_63AC0D);
        v29 = v30;
        v52 = 0;
        v4 = 5;
        v45 = &v2;
        v28 = rf_string_concat_object_cstr(&v2, v50 + 2, v31);
        v52 = -1;
        rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
        break;
      case 4u:
        v27 = (const char *)unk_88E204;
        v44 = v5;
        v26 = rf_string_construct_from_cstr(v5, (char *)&byte_63AC0E);
        v25 = v26;
        v52 = 1;
        v4 = 5;
        v43 = &v2;
        v24 = rf_string_concat_object_cstr(&v2, v50 + 2, v27);
        v52 = -1;
        rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
        break;
      case 5u:
        v19 = (const char *)unk_88E218;
        v40 = v5;
        v18 = rf_string_construct_from_cstr(v5, (char *)&byte_63AC23);
        v17 = v18;
        v52 = 3;
        v4 = 5;
        v39 = &v2;
        v16 = rf_string_concat_object_cstr(&v2, v50 + 2, v19);
        v52 = -1;
        rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
        break;
      case 6u:
        v15 = (const char *)unk_88E21C;
        v38 = v5;
        v14 = rf_string_construct_from_cstr(v5, (char *)&byte_63AC2B);
        v13 = v14;
        v52 = 4;
        v4 = 5;
        v37 = &v2;
        v12 = rf_string_concat_object_cstr(&v2, v50 + 2, v15);
        v52 = -1;
        rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
        break;
      case 7u:
        v11 = " left the game, did not have the level file";
        v36 = v5;
        v10 = rf_string_construct_from_cstr(v5, (char *)&byte_63AC89);
        v9 = v10;
        v52 = 5;
        v4 = 5;
        v35 = &v2;
        v8 = rf_string_concat_object_cstr(&v2, v50 + 2, v11);
        v52 = -1;
        rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
        break;
      default:
        v7 = (const char *)unk_88DF54;
        v34 = v5;
        v6 = rf_string_construct_from_cstr(v5, (char *)&byte_63AC8A);
        v5[5] = (int)v6;
        v52 = 6;
        v4 = 5;
        v33 = &v2;
        v5[4] = (int)rf_string_concat_object_cstr(&v2, v50 + 2, v7);
        v52 = -1;
        rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
        break;
    }
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
    {
      if ( (_DWORD *)rf_ctf_red_carrier_get() == v50 || (_DWORD *)rf_ctf_blue_carrier_get() == v50 )
        rf_ctf_drop_player_carried_flag((int)v50);
      rf_network_remove_player_flag_nodes((int)v50);
    }
    if ( v50 == (_DWORD *)rf_local_fpgun_player )
    {
      v47 = (char *)rf_multiplayer_left_game_reason_text(v48);
      v5[3] = (int)dword_88E208;
      rf_ui_show_ok_modal(dword_88E208, v47, nullptr, 0);
      rf_multiplayer_runtime_teardown();
      rf_ui_request_panel_immediate(13, 1);
    }
    else
    {
      rf_multiplayer_remove_player_and_mark_object((int)v50);
    }
  }
  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
    return rf_multiplayer_broadcast_left_game_packet7(v49, v48);
  return result;
}

