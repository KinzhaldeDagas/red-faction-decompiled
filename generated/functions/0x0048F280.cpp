// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048F280 rf_multiplayer_server_prune_reliable_peers
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, multiplayer session dispatch and deadlines, reliable-peer timeout and acceptance, rename payload ordering, disabled native drawing and wrapped network-id allocation): 
// Cdecl no arguments. Traverses player circle but SAVES next pointer before notification/removal; skips local player. Nonlocal net4608 unguarded. Peer handle net16!=-1 with reliable
// state EXACT0,2 or3 immediately builds notification(player name RFString8+localized88DF58,style5,empty trailing RFString),then delegates removal4A5590(player).
// Otherwise,only pending flag(netDWORD8 &4) tests performance-clock elapsed_ms(1000) against signed start net24: if now<start OR signed(now-start)>5000,notifies with localized88DF5C
// and delegates same removal. Equality5000 retained. Invalid handle-1 does NOT immediately remove absent pending timeout. Non-pending state outside0/2/3 retained. By-value
// notification stack occupies20 bytes,two8-byte RFStrings plus style; notification consumes string temporaries,SEH protects constructed trailing argument. No internal server/mode
// guard; removal delegate4A5590 itself requires mode1/authority1. Return register incidental.
_DWORD *__cdecl rf_multiplayer_server_prune_reliable_peers()
{
  _DWORD *result; // eax
  int v1; // [esp-14h] [ebp-68h] BYREF
  int v2; // [esp-10h] [ebp-64h]
  int v3; // [esp-Ch] [ebp-60h]
  int v4[5]; // [esp-8h] [ebp-5Ch] BYREF
  _DWORD *v5; // [esp+Ch] [ebp-48h]
  const char *v6; // [esp+10h] [ebp-44h]
  void *v7; // [esp+14h] [ebp-40h]
  _DWORD *v8; // [esp+18h] [ebp-3Ch]
  _DWORD *v9; // [esp+1Ch] [ebp-38h]
  const char *v10; // [esp+20h] [ebp-34h]
  _DWORD *v11; // [esp+24h] [ebp-30h]
  int *v12; // [esp+28h] [ebp-2Ch]
  void *v13; // [esp+2Ch] [ebp-28h]
  int *v14; // [esp+30h] [ebp-24h]
  void *v15; // [esp+34h] [ebp-20h]
  int v16; // [esp+38h] [ebp-1Ch]
  int peer_state; // [esp+3Ch] [ebp-18h]
  _DWORD *v18; // [esp+40h] [ebp-14h]
  _DWORD *v19; // [esp+44h] [ebp-10h]
  int v20; // [esp+50h] [ebp-4h]

  result = (_DWORD *)dword_87C324;
  v19 = (_DWORD *)dword_87C324;
  while ( v19 )
  {
    if ( *v19 == dword_87C324 )
      v11 = nullptr;
    else
      v11 = (_DWORD *)*v19;
    v18 = v11;
    result = (_DWORD *)rf_local_fpgun_player;
    if ( (_DWORD *)rf_local_fpgun_player == v19 )
    {
      v19 = v18;
    }
    else if ( *(_DWORD *)(v19[1152] + 16) == -1
           || (peer_state = rf_reliable_udp_get_peer_state(*(_DWORD *)(v19[1152] + 16)), peer_state != 2)
           && peer_state != 3
           && peer_state )
    {
      result = v19;
      if ( (*(_DWORD *)(v19[1152] + 8) & 4) != 0 )
      {
        v16 = rf_performance_clock_elapsed_scaled(1000);
        if ( v16 < *(_DWORD *)(v19[1152] + 24) || (result = v19, v16 - *(_DWORD *)(v19[1152] + 24) > 5000) )
        {
          v6 = (const char *)unk_88DF5C;
          v13 = v4;
          v5 = rf_string_construct_from_cstr(v4, (char *)&byte_63932E);
          v4[4] = (int)v5;
          v20 = 1;
          v3 = 5;
          v12 = &v1;
          v4[3] = (int)rf_string_concat_object_cstr(&v1, v19 + 2, v6);
          v20 = -1;
          rf_multiplayer_notification_enqueue(v1, v2, v3, v4[0]);
          result = (_DWORD *)rf_server_kick_and_remove_player((int)v19);
        }
      }
      v19 = v18;
    }
    else
    {
      v10 = (const char *)unk_88DF58;
      v15 = v4;
      v9 = rf_string_construct_from_cstr(v4, (char *)&byte_63932D);
      v8 = v9;
      v20 = 0;
      v3 = 5;
      v14 = &v1;
      v7 = rf_string_concat_object_cstr(&v1, v19 + 2, v10);
      v20 = -1;
      rf_multiplayer_notification_enqueue(v1, v2, v3, v4[0]);
      result = (_DWORD *)rf_server_kick_and_remove_player((int)v19);
      v19 = v18;
    }
  }
  return result;
}

