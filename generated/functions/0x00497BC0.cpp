// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00497BC0 rf_client_apply_ctf_flag_taken_payload
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Cdecl(payload pointer), no payload length argument/check. Requires runtime mode exactly1, authority byte exactly0, game mode1 and any nonzero initialized byte77D6E2. Reads
// payload[0] player id and unconditionally copies payload[1]/[2] into red/blue capture BYTES77D6E0/77D6E1 BEFORE player lookup/team validation. Unknown player leaves updated counts
// but no other effects. Team byte[player+48] exactly0 sets BLUE carrier; exactly1 sets RED carrier; every other team returns after count update. Does not set score contribution
// byte+6. Packet31 association follows exact sender payload layout; no static incoming xrefs to this routine in current database, so live dispatch reachability is not established.
// For accepted team sets carrier first; resolves player entity handle+20 and plays positional event64 at entity common position+60 if resolved. Always emits style5 localized prefix
// Blue flag stolen by (88DF2C) or Red flag stolen by (88DF30) plus player RFString+8, even without local player/entity. If local player exists and team differs, arms deferred sound
// timer77D730 for0ms. If player is local, also emits style4 stolen-enemy-flag text88E324; otherwise different-team local player receives style4 enemy-stole-your-flag text88E328.
// Trailing empty RFStrings use original-PE-verified NUL bytes; notification ABI is two 8-byte by-value RFStrings plus style DWORD, 20-byte caller cleanup, callee consumption and SEH
// protection. Extra literal1 stack words around carrier setters do not change their one-pointer ABI.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662ABC registers opcode31 (ctf_flag_picked_up), callback0x00497BC0. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
void __cdecl rf_client_apply_ctf_flag_taken_payload(char *a1)
{
  int v1; // [esp-8h] [ebp-98h] BYREF
  int v2; // [esp-4h] [ebp-94h]
  int v3; // [esp+0h] [ebp-90h]
  int v4; // [esp+4h] [ebp-8Ch] BYREF
  int v5; // [esp+8h] [ebp-88h]
  _DWORD *v6; // [esp+10h] [ebp-80h]
  _DWORD *v7; // [esp+14h] [ebp-7Ch]
  _DWORD *v8; // [esp+18h] [ebp-78h]
  char *v9; // [esp+1Ch] [ebp-74h]
  _DWORD *v10; // [esp+20h] [ebp-70h]
  _DWORD *v11; // [esp+24h] [ebp-6Ch]
  _DWORD *v12; // [esp+28h] [ebp-68h]
  char *Source; // [esp+2Ch] [ebp-64h]
  void *v14; // [esp+30h] [ebp-60h]
  _DWORD *v15; // [esp+34h] [ebp-5Ch]
  _DWORD *v16; // [esp+38h] [ebp-58h]
  const char *v17; // [esp+3Ch] [ebp-54h]
  void *v18; // [esp+40h] [ebp-50h]
  _DWORD *v19; // [esp+44h] [ebp-4Ch]
  _DWORD *v20; // [esp+48h] [ebp-48h]
  const char *v21; // [esp+4Ch] [ebp-44h]
  int *v22; // [esp+50h] [ebp-40h]
  void *v23; // [esp+54h] [ebp-3Ch]
  int *v24; // [esp+58h] [ebp-38h]
  void *v25; // [esp+5Ch] [ebp-34h]
  int *v26; // [esp+60h] [ebp-30h]
  void *v27; // [esp+64h] [ebp-2Ch]
  int *v28; // [esp+68h] [ebp-28h]
  void *v29; // [esp+6Ch] [ebp-24h]
  int v30; // [esp+70h] [ebp-20h]
  int v31; // [esp+74h] [ebp-1Ch]
  char v32; // [esp+7Bh] [ebp-15h]
  _DWORD *v33; // [esp+7Ch] [ebp-14h]
  int v34; // [esp+80h] [ebp-10h]
  int v35; // [esp+8Ch] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority && rf_multiplayer_game_mode_get() == 1 )
  {
    if ( byte_77D6E2 )
    {
      v34 = 0;
      v32 = *a1;
      v34 = 1;
      byte_77D6E0 = a1[1];
      v34 = 2;
      byte_77D6E1 = a1[2];
      v34 = 3;
      v33 = rf_player_find_by_network_id(v32);
      if ( v33 )
      {
        if ( *((_BYTE *)v33 + 48) )
        {
          if ( *((_BYTE *)v33 + 48) != 1 )
            return;
          v5 = 1;
          rf_ctf_red_carrier_set((int)v33);
          v30 = rf_entity_resolve_handle(v33[5]);
          if ( v30 )
            rf_gamesound_play_positional_event(64, (float *)(v30 + 60), 1.0, (int)&unk_17F10B0, 0);
          v17 = (const char *)unk_88DF30;
          v27 = &v4;
          v16 = rf_string_construct_from_cstr(&v4, (char *)&byte_63A049);
          v15 = v16;
          v35 = 1;
          v3 = 5;
          v26 = &v1;
          v14 = rf_string_concat_cstr_object(&v1, v17, (const void **)v33 + 2);
          v35 = -1;
          rf_multiplayer_notification_enqueue(v1, v2, v3, v4);
        }
        else
        {
          v5 = 1;
          rf_ctf_blue_carrier_set((int)v33);
          v31 = rf_entity_resolve_handle(v33[5]);
          if ( v31 )
            rf_gamesound_play_positional_event(64, (float *)(v31 + 60), 1.0, (int)&unk_17F10B0, 0);
          v21 = (const char *)unk_88DF2C;
          v29 = &v4;
          v20 = rf_string_construct_from_cstr(&v4, (char *)&byte_639FFB);
          v19 = v20;
          v35 = 0;
          v3 = 5;
          v28 = &v1;
          v18 = rf_string_concat_cstr_object(&v1, v21, (const void **)v33 + 2);
          v35 = -1;
          rf_multiplayer_notification_enqueue(v1, v2, v3, v4);
        }
        if ( rf_local_fpgun_player )
        {
          if ( *((unsigned __int8 *)v33 + 48) != *(unsigned __int8 *)(rf_local_fpgun_player + 48) )
            rf_replicator_arm_milliseconds(&unk_77D730, 0);
          if ( v33 == (_DWORD *)rf_local_fpgun_player )
          {
            Source = (char *)unk_88E324;
            v25 = &v4;
            v12 = rf_string_construct_from_cstr(&v4, (char *)&byte_63A04A);
            v11 = v12;
            v35 = 2;
            v3 = 4;
            v24 = &v1;
            v10 = rf_string_construct_from_cstr(&v1, Source);
            v35 = -1;
            rf_multiplayer_notification_enqueue(v1, v2, v3, v4);
          }
          else if ( *(unsigned __int8 *)(rf_local_fpgun_player + 48) != *((unsigned __int8 *)v33 + 48) )
          {
            v9 = (char *)unk_88E328;
            v23 = &v4;
            v8 = rf_string_construct_from_cstr(&v4, (char *)&byte_63A04B);
            v7 = v8;
            v35 = 3;
            v3 = 4;
            v22 = &v1;
            v6 = rf_string_construct_from_cstr(&v1, v9);
            v35 = -1;
            rf_multiplayer_notification_enqueue(v1, v2, v3, v4);
          }
        }
      }
    }
  }
}

