// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045A3F0 rf_multiplayer_send_chat_line_packet12
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet12/50/51/52/53/54 registry, sound/score/glass layouts, chat routing, RCON source admission and
// native string bounds): Cdecl(text,modeDWORD),existing return/type/SEH chunks preserved; EAX incidental branch result,not uniform success. Dedicated markerBYTE704E83 EXACT1 takes
// precedence: build packet12 with senderIDFF,mode lowBYTE,text+NUL; enqueue local notification with empty prefix636077 and FULL modeDWORD style;unreliable queue to ALL circular
// players,without local/team exclusion. Else runtime1 authority EXACT1: enqueue local player notification FIRST,read local netID (local/net unguarded),lookup that ID;only if found
// send using actual local ID to every peer except local;modeDWORD EXACT1 filters same resolved sender team,other DWORDs all. Every other runtime/authority combination falls through
// to client-like path: unguarded local/net ID,build packet,local notification,unreliable queue(local,...). In all three builds scan unbounded Cstring,copy only strlen LOW16,append
// NUL with16-bit cursor,total=(6+low16len) modulo65536,payloadWORD=total-3; no fixed stack packet capacity check or text truncation. Wire mode is lowBYTE but host filtering/helper
// comparisons use FULL DWORD (e.g.257 differs from1 locally,wire1). No chat sound here. Circular next links read after queue calls. RCON grant sender uses dedicated branch with
// mode0.
_DWORD *__cdecl rf_multiplayer_send_chat_line_packet12(char *Src, int a2)
{
  _DWORD *result; // eax
  int v3[2]; // [esp-14h] [ebp-6B0h] BYREF
  int v4; // [esp-Ch] [ebp-6A8h]
  int v5[3]; // [esp-8h] [ebp-6A4h] BYREF
  int v6; // [esp+4h] [ebp-698h]
  int v7; // [esp+14h] [ebp-688h]
  unsigned int v8; // [esp+18h] [ebp-684h]
  int v9; // [esp+28h] [ebp-674h]
  _DWORD *v10; // [esp+2Ch] [ebp-670h]
  _DWORD *v11; // [esp+30h] [ebp-66Ch]
  _DWORD *v12; // [esp+34h] [ebp-668h]
  unsigned int v13; // [esp+38h] [ebp-664h]
  int *v14; // [esp+48h] [ebp-654h]
  void *v15; // [esp+4Ch] [ebp-650h]
  unsigned __int16 v16; // [esp+5Ch] [ebp-640h]
  char v17; // [esp+60h] [ebp-63Ch] BYREF
  __int16 v18; // [esp+61h] [ebp-63Bh]
  char v19; // [esp+63h] [ebp-639h]
  char v20; // [esp+64h] [ebp-638h]
  _BYTE v21[511]; // [esp+65h] [ebp-637h] BYREF
  __int16 v22; // [esp+264h] [ebp-438h]
  char v23; // [esp+26Ah] [ebp-432h]
  char v24; // [esp+26Bh] [ebp-431h]
  unsigned __int16 v25; // [esp+26Ch] [ebp-430h]
  char v26; // [esp+270h] [ebp-42Ch] BYREF
  __int16 v27; // [esp+271h] [ebp-42Bh]
  char v28; // [esp+273h] [ebp-429h]
  char v29; // [esp+274h] [ebp-428h]
  _BYTE v30[3]; // [esp+275h] [ebp-427h] BYREF
  int j; // [esp+470h] [ebp-22Ch]
  _DWORD *v32; // [esp+474h] [ebp-228h]
  __int16 v33; // [esp+478h] [ebp-224h]
  __int16 v34; // [esp+47Ch] [ebp-220h]
  char v35; // [esp+482h] [ebp-21Ah]
  char v36; // [esp+483h] [ebp-219h]
  unsigned __int16 v37; // [esp+484h] [ebp-218h]
  char v38; // [esp+488h] [ebp-214h] BYREF
  __int16 v39; // [esp+489h] [ebp-213h]
  char v40; // [esp+48Bh] [ebp-211h]
  char v41; // [esp+48Ch] [ebp-210h]
  _BYTE v42[3]; // [esp+48Dh] [ebp-20Fh] BYREF
  int i; // [esp+68Ch] [ebp-10h]
  int v44; // [esp+698h] [ebp-4h]

  if ( byte_704E83 == 1 )
  {
    v38 = 12;
    v36 = -1;
    v40 = -1;
    v35 = a2;
    v41 = a2;
    v37 = 5;
    v13 = strlen(Src);
    v34 = v13;
    memcpy(v42, Src, (unsigned __int16)v13);
    v37 = v13 + 5;
    *(&v38 + v37++) = 0;
    v33 = v37 - 3;
    v39 = v37 - 3;
    v15 = v5;
    v12 = rf_string_construct_from_cstr(v5, (char *)&byte_636077);
    v11 = v12;
    v44 = 0;
    v4 = a2;
    v14 = v3;
    v10 = rf_string_construct_from_cstr(v3, Src);
    v44 = -1;
    rf_multiplayer_notification_enqueue(v3[0], v3[1], v4, v5[0]);
    result = (_DWORD *)dword_87C324;
    for ( i = dword_87C324; i; i = v9 )
    {
      result = (_DWORD *)rf_network_queue_unreliable_player_packet(i, &v38, v37);
      if ( *(_DWORD *)i == dword_87C324 )
      {
        v9 = 0;
      }
      else
      {
        result = (_DWORD *)i;
        v9 = *(_DWORD *)i;
      }
    }
  }
  else if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    rf_multiplayer_enqueue_player_chat_notification(rf_local_fpgun_player, Src, a2);
    result = rf_player_find_by_network_id(*(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20));
    v32 = result;
    if ( result )
    {
      v26 = 12;
      v25 = 3;
      v24 = *(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20);
      v28 = v24;
      v23 = a2;
      v29 = a2;
      v8 = strlen(Src);
      v22 = v8;
      memcpy(v30, Src, (unsigned __int16)v8);
      v25 = v8 + 5;
      *(&v26 + v25++) = 0;
      *(_WORD *)&v21[507] = v25 - 3;
      v27 = v25 - 3;
      result = (_DWORD *)dword_87C324;
      for ( j = dword_87C324; j; j = v7 )
      {
        result = (_DWORD *)j;
        if ( j != rf_local_fpgun_player )
        {
          if ( a2 != 1 || (result = v32, *(unsigned __int8 *)(j + 48) == *((unsigned __int8 *)v32 + 48)) )
            result = (_DWORD *)rf_network_queue_unreliable_player_packet(j, &v26, v25);
        }
        if ( *(_DWORD *)j == dword_87C324 )
        {
          v7 = 0;
        }
        else
        {
          result = (_DWORD *)j;
          v7 = *(_DWORD *)j;
        }
      }
    }
  }
  else
  {
    v17 = 12;
    v16 = 3;
    v19 = *(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20);
    v20 = a2;
    LOWORD(v6) = strlen(Src);
    memcpy(v21, Src, (unsigned __int16)v6);
    v16 = v6 + 5;
    *(&v17 + v16++) = 0;
    v18 = v16 - 3;
    rf_multiplayer_enqueue_player_chat_notification(rf_local_fpgun_player, Src, a2);
    return (_DWORD *)rf_network_queue_unreliable_player_packet(rf_local_fpgun_player, &v17, v16);
  }
  return result;
}

