// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B10A0 rf_multiplayer_apply_team_change_payload23
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Descriptor23 at662A5C. Cdecl payload pointer only consumed; dispatcher source ignored, length not passed. Read unsigned idBYTE0/teamBYTE1, find player
// by claimed ID. If found store raw team to Player48 unconditionally, even unchanged; notification uses nonzero team ->localized88DF3C/style3,zero->88DF40/style2, owned8-byte
// name+suffix and8-byte empty secondary string,20-byte cleanup. No team0/1 constraint, existing-team comparison, source binding or entry runtime gate on local mutation/notification.
// AFTER lookup branch, runtime1 authority EXACT1 calls broadcast wrapper23 EVEN when lookup failed. No entity respawn/kill, score reset or length guard. Return runtime/delegate EAX,
// not uniform success.
int __cdecl rf_multiplayer_apply_team_change_payload23(char *a1)
{
  int result; // eax
  int v2[2]; // [esp-14h] [ebp-60h] BYREF
  int v3; // [esp-Ch] [ebp-58h]
  int v4[5]; // [esp-8h] [ebp-54h] BYREF
  _DWORD *v5; // [esp+Ch] [ebp-40h]
  const char *v6; // [esp+10h] [ebp-3Ch]
  void *v7; // [esp+14h] [ebp-38h]
  _DWORD *v8; // [esp+18h] [ebp-34h]
  _DWORD *v9; // [esp+1Ch] [ebp-30h]
  const char *v10; // [esp+20h] [ebp-2Ch]
  int *v11; // [esp+24h] [ebp-28h]
  void *v12; // [esp+28h] [ebp-24h]
  int *v13; // [esp+2Ch] [ebp-20h]
  void *v14; // [esp+30h] [ebp-1Ch]
  char v15; // [esp+36h] [ebp-16h]
  char v16; // [esp+37h] [ebp-15h]
  _DWORD *v17; // [esp+38h] [ebp-14h]
  int v18; // [esp+3Ch] [ebp-10h]
  int v19; // [esp+48h] [ebp-4h]

  v18 = 0;
  v16 = *a1;
  v18 = 1;
  v15 = a1[1];
  v18 = 2;
  v17 = rf_player_find_by_network_id(v16);
  if ( v17 )
  {
    *((_BYTE *)v17 + 48) = v15;
    if ( v15 )
    {
      v6 = (const char *)unk_88DF3C;
      v12 = v4;
      v5 = rf_string_construct_from_cstr(v4, (char *)byte_63B58A);
      v4[4] = (int)v5;
      v19 = 1;
      v3 = 3;
      v11 = v2;
      v4[3] = (int)rf_string_concat_object_cstr(v2, v17 + 2, v6);
    }
    else
    {
      v10 = (const char *)unk_88DF40;
      v14 = v4;
      v9 = rf_string_construct_from_cstr(v4, (char *)&byte_63B589);
      v8 = v9;
      v19 = 0;
      v3 = 2;
      v13 = v2;
      v7 = rf_string_concat_object_cstr(v2, v17 + 2, v10);
    }
    v19 = -1;
    rf_multiplayer_notification_enqueue(v2[0], v2[1], v3, v4[0]);
  }
  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
    return rf_server_broadcast_team_change_packet23(v16, v15);
  return result;
}

