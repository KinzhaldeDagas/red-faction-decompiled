// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A3680 rf_server_admit_player_after_join
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Logical cdecl(endpoint,by-value name RFString8,raw player field DWORD,requestedRate DWORD), native20 bytes/current five-DWORD prototype. Consumes name on EVERY normal
// guard/failure/success path and SEH. Requires runtime1/authority exactly1 but does not repeat admission/password/signature checks. Chooses team before player_create_runtime(0).
// Allocation failure sends rejection1. Success assigns name,team+48,raw player DWORD+24,full8-byte endpoint, unused network id BYTE, net handle=-1, OR flags4, state+12=0; team
// exactly1 additionally ORs flags80 (no explicit80 clear otherwise); stores rate+2492.
// In order recomputes update interval, sends join-accept3 to new endpoint, announces player5 to other peers, emits style5 has-joined notification, stores performance-clock
// milliseconds in net+24, and optionally logs joined name when runtime still1. Pending player and announcements exist BEFORE reliable connection activation; does not allocate an
// entity body or wait for successful transport. No cleanup/rollback when send fails. Native notification two by-value RFStrings plus style consumes20 bytes.
void __cdecl rf_server_admit_player_after_join(_DWORD *a1, int a2, int a3, int a4, int a5)
{
  int v5; // ecx
  _DWORD *v6; // edx
  const char *v7; // eax
  int v8[2]; // [esp-14h] [ebp-44h] BYREF
  int v9; // [esp-Ch] [ebp-3Ch]
  int v10[5]; // [esp-8h] [ebp-38h] BYREF
  _DWORD *v11; // [esp+Ch] [ebp-24h]
  const char *v12; // [esp+10h] [ebp-20h]
  int *v13; // [esp+14h] [ebp-1Ch]
  void *v14; // [esp+18h] [ebp-18h]
  _DWORD *runtime; // [esp+1Ch] [ebp-14h]
  char v16; // [esp+23h] [ebp-Dh]
  int v17; // [esp+2Ch] [ebp-4h]

  v17 = 0;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v16 = rf_multiplayer_choose_balanced_team_byte();
    runtime = rf_player_create_runtime(0);
    if ( runtime )
    {
      rf_string_assign_from_object(runtime + 2, (int)&a2);
      *((_BYTE *)runtime + 48) = v16;
      runtime[6] = a4;
      v5 = a1[1];
      v6 = (_DWORD *)runtime[1152];
      *v6 = *a1;
      v6[1] = v5;
      *(_BYTE *)(runtime[1152] + 20) = rf_multiplayer_allocate_unused_network_id_byte();
      *(_DWORD *)(runtime[1152] + 16) = -1;
      *(_DWORD *)(runtime[1152] + 8) |= 4u;
      *(_DWORD *)(runtime[1152] + 12) = 0;
      if ( v16 == 1 )
        *(_DWORD *)(runtime[1152] + 8) |= 0x80u;
      *(_DWORD *)(runtime[1152] + 2492) = a5;
      rf_multiplayer_peer_update_interval_recompute((int)runtime);
      rf_server_send_join_accept_packet3((int)a1, (int)runtime);
      rf_server_announce_joined_player_packet5(runtime);
      v12 = (const char *)unk_88DF48;
      v14 = v10;
      v11 = rf_string_construct_from_cstr(v10, (char *)&byte_63A92F);
      v10[4] = (int)v11;
      LOBYTE(v17) = 1;
      v9 = 5;
      v13 = v8;
      v10[3] = (int)rf_string_concat_object_cstr(v8, runtime + 2, v12);
      LOBYTE(v17) = 0;
      rf_multiplayer_notification_enqueue(v8[0], v8[1], v9, v10[0]);
      *(_DWORD *)(runtime[1152] + 24) = rf_performance_clock_elapsed_scaled(1000);
      if ( rf_multiplayer_runtime_mode == 1 )
      {
        v7 = rf_string_object_c_str_or_empty(runtime + 2);
        rf_multiplayer_log_printf("Player %s has joined", v7);
      }
      v17 = -1;
      rf_string_destroy_buffer(&a2);
    }
    else
    {
      rf_server_send_join_rejection_packet4((int)a1, 1);
      v17 = -1;
      rf_string_destroy_buffer(&a2);
    }
  }
  else
  {
    v17 = -1;
    rf_string_destroy_buffer(&a2);
  }
}

