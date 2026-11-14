// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A23E0 rf_client_apply_joined_player_payload5
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(payload), requires runtime1 and authority exactly0. No current incoming xrefs/null/length check; packet5 pairing by exact layout. Reads id BYTE0, IPv4 DWORD1, port
// WORD5,flags DWORD7,requested rate DWORD11,name NUL at15. Scans full source name, strncpy255 then destination[254]=0; cursor advances by full source length modulo65536. Existing
// player id returns without updating it, after parsing entire payload.
// Otherwise creates player runtime(0) with NO allocation-result check, assigns truncated name, team byte+48=(flags&80)!=0, network id, IPv4,flags OR into net+8, connection handle=-1
// and rate+2492. Native stack port local initializes only LOW16, then copies FULL DWORD to net+4: high16 padding remains unspecified, not zero-extended. Does not establish reliable
// connection or set net state explicitly. Emits style5 player-name plus localized has-joined suffix88DF48 with empty trailing RFString; native notification owns two8-byte by-value
// strings,20-byte caller cleanup/SEH.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662984 registers opcode5 (new_player), callback0x004A23E0. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
void __cdecl rf_client_apply_joined_player_payload5(int a1)
{
  _DWORD *v1; // eax
  int v2[2]; // [esp-14h] [ebp-174h] BYREF
  int v3; // [esp-Ch] [ebp-16Ch]
  int v4[5]; // [esp-8h] [ebp-168h] BYREF
  _DWORD *v5; // [esp+Ch] [ebp-154h]
  const char *v6; // [esp+10h] [ebp-150h]
  unsigned int v7; // [esp+14h] [ebp-14Ch]
  int v8; // [esp+1Ch] [ebp-144h]
  unsigned int v9; // [esp+20h] [ebp-140h]
  int *v10; // [esp+24h] [ebp-13Ch]
  void *v11; // [esp+28h] [ebp-138h]
  __int16 v12; // [esp+2Ch] [ebp-134h]
  int v13; // [esp+30h] [ebp-130h]
  char Destination[256]; // [esp+34h] [ebp-12Ch] BYREF
  _DWORD *runtime; // [esp+138h] [ebp-28h]
  char v16; // [esp+13Fh] [ebp-21h]
  int v17; // [esp+140h] [ebp-20h]
  int v18; // [esp+144h] [ebp-1Ch]
  int v20; // [esp+14Ch] [ebp-14h]
  int v21; // [esp+150h] [ebp-10h]
  int v22; // [esp+15Ch] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    v20 = 0;
    v16 = *(_BYTE *)a1;
    v20 = 1;
    v17 = *(_DWORD *)(a1 + 1);
    v20 = 5;
    LOWORD(v18) = *(_WORD *)(a1 + 5);
    v20 = 7;
    v13 = *(_DWORD *)(a1 + 7);
    v20 = 11;
    v21 = *(_DWORD *)(a1 + 11);
    v20 = 15;
    v8 = a1 + 16;
    v9 = a1 + 15 + strlen((const char *)(a1 + 15)) + 1;
    v7 = v9 - (a1 + 16);
    v12 = v9 - (a1 + 16);
    strncpy(Destination, (const char *)(a1 + 15), 0xFFu);
    Destination[254] = 0;
    v20 = (unsigned __int16)(v20 + v12 + 1);
    if ( !rf_player_find_by_network_id(v16) )
    {
      runtime = rf_player_create_runtime(0);
      rf_string_assign_from_cstr(runtime + 2, Destination);
      *((_BYTE *)runtime + 48) = (v13 & 0x80) != 0;
      *(_BYTE *)(runtime[1152] + 20) = v16;
      v1 = (_DWORD *)runtime[1152];
      *v1 = v17;
      v1[1] = v18;
      *(_DWORD *)(runtime[1152] + 8) |= v13;
      *(_DWORD *)(runtime[1152] + 16) = -1;
      *(_DWORD *)(runtime[1152] + 2492) = v21;
      v6 = (const char *)unk_88DF48;
      v11 = v4;
      v5 = rf_string_construct_from_cstr(v4, (char *)&byte_63A975);
      v4[4] = (int)v5;
      v22 = 0;
      v3 = 5;
      v10 = v2;
      v4[3] = (int)rf_string_concat_object_cstr(v2, runtime + 2, v6);
      v22 = -1;
      rf_multiplayer_notification_enqueue(v2[0], v2[1], v3, v4[0]);
    }
  }
}

