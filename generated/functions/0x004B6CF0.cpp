// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B6CF0 rf_console_print_multiplayer_session_info
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): Noarg console report. Reads level age FLOAT6FC428;
// seconds=trunc(age)%60,minutes=trunc(age/DOUBLE60)%60,hours=trunc(age/3600)%24,days=trunc(age/86400), each fresh read and signed division/remainder (no negative/finite
// normalization). Prints separator, localized level label88E298 plus current RFString6FC31C, localized level-time/day labels88E2A0/A4 plus values. Prints literal Framerate / FPS:
// followed by frameDelta663EC8 fixed3 and FLOAT663ECC fixed0, joined by / and newline; six owned8-byte RFString temporaries destroyed normally and by SEH. Does not calculate
// reciprocal FPS here. If player-list count>0, prints localized client/ping heading88E2A8 then walks circular players87C324. Ping=netDWORD1452 when net exists, except
// runtime1/authorityEXACT1 forces local-player ping0. Then UNCONDITIONALLY reads net first8 bytes despite earlier null guards, applies ntohl to addressDWORD and inet_ntoa; second
// endpointDWORD copied but unused. Row includes IP only if conversion nonNULL,player!=local AND(runtime!=1 OR authority!=0); otherwise name RFString+8 and ping only. Uses unbounded
// sprintf local516, immediate console appends with secondNULL, reads next after output. No port display, player/net lifetime guard, networking/statistics mutation or refresh timer.
// Return incidental.
_DWORD *rf_console_print_multiplayer_session_info()
{
  const char *v0; // eax
  const char *v1; // eax
  _DWORD *result; // eax
  u_long *v3; // eax
  u_long v4; // edx
  const char *v5; // eax
  const char *v6; // eax
  int v7; // [esp+10h] [ebp-2C0h]
  int v8; // [esp+14h] [ebp-2BCh]
  const char *v9; // [esp+14h] [ebp-2BCh]
  _DWORD *v10; // [esp+1Ch] [ebp-2B4h]
  std::exception *v11; // [esp+24h] [ebp-2ACh]
  _DWORD *v12; // [esp+2Ch] [ebp-2A4h]
  int *v13; // [esp+34h] [ebp-29Ch]
  _DWORD *v14; // [esp+3Ch] [ebp-294h]
  const void **v15; // [esp+44h] [ebp-28Ch]
  void *v16; // [esp+4Ch] [ebp-284h]
  const char *v17; // [esp+5Ch] [ebp-274h]
  _BYTE v18[8]; // [esp+60h] [ebp-270h] BYREF
  _BYTE v19[8]; // [esp+68h] [ebp-268h] BYREF
  _BYTE v20[8]; // [esp+70h] [ebp-260h] BYREF
  _BYTE v21[8]; // [esp+78h] [ebp-258h] BYREF
  int v22[2]; // [esp+80h] [ebp-250h] BYREF
  int v23[2]; // [esp+88h] [ebp-248h] BYREF
  int v24; // [esp+90h] [ebp-240h]
  struct in_addr in; // [esp+94h] [ebp-23Ch]
  char *v26; // [esp+98h] [ebp-238h]
  _DWORD *i; // [esp+9Ch] [ebp-234h]
  u_long netlong; // [esp+A0h] [ebp-230h]
  u_long v29; // [esp+A4h] [ebp-22Ch]
  int v30; // [esp+A8h] [ebp-228h]
  int v31; // [esp+ACh] [ebp-224h]
  int v32; // [esp+B0h] [ebp-220h]
  char Buffer[516]; // [esp+B4h] [ebp-21Ch] BYREF
  int v34; // [esp+2BCh] [ebp-14h]
  int v35; // [esp+2C0h] [ebp-10h]
  int v36; // [esp+2CCh] [ebp-4h]

  v32 = (int)*(float *)&dword_6FC428 % 60;
  v34 = (int)(*(float *)&dword_6FC428 / 60.0) % 60;
  v31 = (int)(*(float *)&dword_6FC428 / 3600.0) % 24;
  v35 = (int)(*(float *)&dword_6FC428 / 86400.0);
  rf_console_output_append_text_lines("======================================\n", nullptr);
  v17 = dword_88E298;
  v0 = rf_string_object_c_str_or_empty(unk_6FC31C);
  sprintf(Buffer, "%s:  %s \n", v17, v0);
  rf_console_output_append_text_lines(Buffer, nullptr);
  sprintf(Buffer, "%s:  %d %s, %dh %dm %ds\n", unk_88E2A0, v35, unk_88E2A4, v31, v34, v32);
  rf_console_output_append_text_lines(Buffer, nullptr);
  v16 = rf_string_format_float_fixed_precision(v23, flt_663ECC, 0);
  v36 = 0;
  v15 = (const void **)rf_string_format_float_fixed_precision(v22, rf_frame_delta_seconds, 3);
  LOBYTE(v36) = 1;
  v14 = rf_string_concat_cstr_object(v21, "Framerate / FPS:  ", v15);
  LOBYTE(v36) = 2;
  v13 = (int *)rf_string_concat_object_cstr(v20, v14, " / ");
  LOBYTE(v36) = 3;
  v12 = rf_string_concat_two_objects(v19, v13, (int)v16);
  LOBYTE(v36) = 4;
  v11 = (std::exception *)rf_string_concat_object_cstr(v18, v12, "\n");
  LOBYTE(v36) = 5;
  v1 = rf_string_object_c_str_or_empty(v11);
  rf_console_output_append_text_lines(v1, nullptr);
  LOBYTE(v36) = 4;
  rf_string_destroy_buffer(v18);
  LOBYTE(v36) = 3;
  rf_string_destroy_buffer(v19);
  LOBYTE(v36) = 2;
  rf_string_destroy_buffer(v20);
  LOBYTE(v36) = 1;
  rf_string_destroy_buffer(v21);
  LOBYTE(v36) = 0;
  rf_string_destroy_buffer(v22);
  v36 = -1;
  rf_string_destroy_buffer(v23);
  rf_console_output_append_text_lines("======================================\n", nullptr);
  result = (_DWORD *)rf_player_runtime_list_count();
  if ( (int)result > 0 )
  {
    rf_console_output_append_text_lines(unk_88E2A8, nullptr);
    v30 = 0;
    result = (_DWORD *)dword_87C324;
    for ( i = (_DWORD *)dword_87C324; i; i = v10 )
    {
      v24 = 0;
      if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      {
        if ( i != (_DWORD *)rf_local_fpgun_player && i[1152] )
          v24 = *(_DWORD *)(i[1152] + 1452);
      }
      else if ( i[1152] )
      {
        v24 = *(_DWORD *)(i[1152] + 1452);
      }
      v3 = (u_long *)i[1152];
      v4 = v3[1];
      netlong = *v3;
      v29 = v4;
      netlong = ntohl(netlong);
      in = (struct in_addr)netlong;
      v26 = inet_ntoa((struct in_addr)netlong);
      if ( v26
        && i != (_DWORD *)rf_local_fpgun_player
        && (rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority) )
      {
        v9 = v26;
        v7 = v24;
        v6 = rf_string_object_c_str_or_empty(i + 2);
        sprintf(Buffer, "\"%s\" (%d) (%s)\n", v6, v7, v9);
      }
      else
      {
        v8 = v24;
        v5 = rf_string_object_c_str_or_empty(i + 2);
        sprintf(Buffer, "\"%s\" (%d)\n", v5, v8);
      }
      result = (_DWORD *)rf_console_output_append_text_lines(Buffer, nullptr);
      if ( *i == dword_87C324 )
      {
        v10 = nullptr;
      }
      else
      {
        result = i;
        v10 = (_DWORD *)*i;
      }
    }
  }
  return result;
}

