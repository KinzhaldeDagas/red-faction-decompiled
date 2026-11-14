// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045AF80 rf_multiplayer_apply_chat_line_payload12
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet12/50/51/52/53/54 registry, sound/score/glass layouts, chat routing, RCON source admission and
// native string bounds): Compiled descriptor12 chat_line, existing SEH function/chunks preserved. Payload senderID BYTE0,modeBYTE1,NUL text+2; source extra dispatcher word unused.
// Scan full incoming text before strncpy255 and force local index254 NUL (max254 characters); no payload-length check. IDFF displays bounded text with RFString prefix "Server: " and
// style0 regardless mode. Other ID: zero-extend ID for player lookup; mode EXACT1 requires nonNULL local player and equal teamBYTE48 before local notification45A200;all other mode
// bytes display unconditionally when player exists. Separately runtime1 authority EXACT1 resolves claimed ID again; if found reconstruct packet12 (senderID,mode,bounded
// text+NUL,total6+length), queue unreliable to circular peers except local and resolved sender;mode1 only matching sender team,others all. No source-to-ID binding. Server-text branch
// itself does not bypass second player lookup for relay. Finally dedicated marker!=EXACT1 and displayed flag ->sound event4(0,0.0,1.0). Next links read after sends; notification uses
// two owned8-byte RFStrings plus styleDWORD (20 native stack bytes).
void __cdecl rf_multiplayer_apply_chat_line_payload12(int a1)
{
  int v1[2]; // [esp-Ch] [ebp-394h] BYREF
  int v2; // [esp-4h] [ebp-38Ch]
  int v3; // [esp+0h] [ebp-388h] BYREF
  int v4; // [esp+Ch] [ebp-37Ch]
  int v5; // [esp+10h] [ebp-378h]
  _BYTE *v6; // [esp+18h] [ebp-370h]
  char *p_Destination; // [esp+1Ch] [ebp-36Ch]
  _DWORD *v8; // [esp+20h] [ebp-368h]
  _DWORD *v9; // [esp+24h] [ebp-364h]
  _DWORD *v10; // [esp+28h] [ebp-360h]
  unsigned int v11; // [esp+2Ch] [ebp-35Ch]
  int v12; // [esp+34h] [ebp-354h]
  unsigned int v13; // [esp+38h] [ebp-350h]
  int *v14; // [esp+3Ch] [ebp-34Ch]
  void *v15; // [esp+40h] [ebp-348h]
  __int16 v16; // [esp+44h] [ebp-344h]
  unsigned __int16 v17; // [esp+48h] [ebp-340h]
  unsigned __int8 v18; // [esp+4Eh] [ebp-33Ah]
  char v19; // [esp+4Fh] [ebp-339h]
  unsigned __int16 v20; // [esp+50h] [ebp-338h]
  char Src; // [esp+54h] [ebp-334h] BYREF
  __int16 v22; // [esp+55h] [ebp-333h]
  char v23; // [esp+57h] [ebp-331h]
  unsigned __int8 v24; // [esp+58h] [ebp-330h]
  _BYTE v25[3]; // [esp+59h] [ebp-32Fh] BYREF
  int i; // [esp+258h] [ebp-130h]
  _DWORD *v27; // [esp+25Ch] [ebp-12Ch]
  bool v28; // [esp+263h] [ebp-125h]
  int v29; // [esp+264h] [ebp-124h]
  __int16 v30; // [esp+268h] [ebp-120h]
  char v31; // [esp+26Dh] [ebp-11Bh]
  char v32; // [esp+26Eh] [ebp-11Ah]
  unsigned __int8 v33; // [esp+26Fh] [ebp-119h]
  int v34; // [esp+270h] [ebp-118h]
  char Destination; // [esp+274h] [ebp-114h] BYREF
  _BYTE v36[259]; // [esp+275h] [ebp-113h] BYREF
  int v37; // [esp+384h] [ebp-4h]

  v34 = 0;
  v32 = *(_BYTE *)a1;
  v34 = 1;
  v33 = *(_BYTE *)(a1 + 1);
  v12 = a1 + 3;
  v13 = a1 + 2 + strlen((const char *)(a1 + 2)) + 1;
  v11 = v13 - (a1 + 3);
  v30 = v13 - (a1 + 3);
  strncpy(&Destination, (const char *)(a1 + 2), 0xFFu);
  v36[253] = 0;
  v34 = (unsigned __int16)(v13 - a1);
  v31 = 0;
  if ( v32 == -1 )
  {
    v31 = 1;
    v15 = &v3;
    v10 = rf_string_construct_from_cstr(&v3, "Server: ");
    v9 = v10;
    v37 = 0;
    v2 = 0;
    v14 = v1;
    v8 = rf_string_construct_from_cstr(v1, &Destination);
    v37 = -1;
    rf_multiplayer_notification_enqueue(v1[0], v1[1], v2, v3);
  }
  else
  {
    v29 = (int)rf_player_find_by_network_id(v32);
    if ( v29 )
    {
      v28 = 1;
      if ( v33 == 1 )
        v28 = rf_local_fpgun_player
           && *(unsigned __int8 *)(rf_local_fpgun_player + 48) == *(unsigned __int8 *)(v29 + 48);
      if ( v28 )
      {
        v31 = 1;
        rf_multiplayer_enqueue_player_chat_notification(v29, &Destination, v33);
      }
    }
  }
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v27 = rf_player_find_by_network_id(v32);
    if ( v27 )
    {
      Src = 12;
      v19 = v32;
      v23 = v32;
      v18 = v33;
      v24 = v33;
      v20 = 5;
      p_Destination = &Destination;
      v6 = v36;
      p_Destination += strlen(p_Destination);
      v5 = ++p_Destination - v36;
      v17 = (_WORD)p_Destination - (unsigned __int16)v36;
      memcpy(v25, &Destination, v17);
      v20 += v17;
      *(&Src + v20++) = 0;
      v16 = v20 - 3;
      v22 = v20 - 3;
      for ( i = dword_87C324; i; i = v4 )
      {
        if ( i != rf_local_fpgun_player
          && (_DWORD *)i != v27
          && (v33 != 1 || *(unsigned __int8 *)(i + 48) == *((unsigned __int8 *)v27 + 48)) )
        {
          rf_network_queue_unreliable_player_packet(i, &Src, v20);
        }
        if ( *(_DWORD *)i == dword_87C324 )
          v4 = 0;
        else
          v4 = *(_DWORD *)i;
      }
    }
  }
  if ( byte_704E83 != 1 && v31 )
    rf_gamesound_play_event(4, 0, 0.0, 1.0);
}

