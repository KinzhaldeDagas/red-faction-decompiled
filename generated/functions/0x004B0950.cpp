// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B0950 rf_multiplayer_autobalance_teams_by_stats_word0
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Noarg. Require game ruleflags2000 and game-mode delegate EXACT1 or2; NO own runtime/authority gate on team mutation. Gather every circular-list player
// pointer into stack scratch starting EBP-A4; fixed next local EBP-24 lies after32 slots, no capacity clamp. For exactly2 players swap only when signed statsWORD0(first)<second; >2
// use qsort comparator4B08F0 descending, equal order not promised. No player/net/stats NULL guard. Desired odd/even selectors initialize signed-1. If BYTE704E83 EXACT1 choose
// odd0,even1. Otherwise find local-player pointer in sorted array: preserve its raw teamBYTE for its parity, opposite parity=logical(team==0), so invalid team values are not
// generally normalized. If local absent BOTH selectors remain-1; comparison zero-extended existing teamBYTE0..255 against signed-1 ALWAYS differs, then store lowBYTE255. Process
// evens first then odds; for changed entry write raw teamBYTE48 BEFORE strict-server broadcast wrapper23, then notification(playerName+localized suffix,style2 if selector0
// else3,empty suffix),20-byte owned-string ABI with SEH cleanup. No rollback, entity respawn, score reset, balancing by team totals or changes-only network admission beyond each
// comparison. Repeated absent-local calls can keep notifying/storing255 because -1 never equals unsigned255. EAX incidental, not team-change count.
int rf_multiplayer_autobalance_teams_by_stats_word0()
{
  int result; // eax
  int v1; // [esp-14h] [ebp-124h] BYREF
  int v2; // [esp-10h] [ebp-120h]
  int v3; // [esp-Ch] [ebp-11Ch]
  int v4[5]; // [esp-8h] [ebp-118h] BYREF
  _DWORD *v5; // [esp+Ch] [ebp-104h]
  const char *v6; // [esp+10h] [ebp-100h]
  void *v7; // [esp+14h] [ebp-FCh]
  _DWORD *v8; // [esp+18h] [ebp-F8h]
  _DWORD *v9; // [esp+1Ch] [ebp-F4h]
  const char *v10; // [esp+20h] [ebp-F0h]
  void *v11; // [esp+24h] [ebp-ECh]
  _DWORD *v12; // [esp+28h] [ebp-E8h]
  _DWORD *v13; // [esp+2Ch] [ebp-E4h]
  const char *v14; // [esp+30h] [ebp-E0h]
  void *v15; // [esp+34h] [ebp-DCh]
  _DWORD *v16; // [esp+38h] [ebp-D8h]
  _DWORD *v17; // [esp+3Ch] [ebp-D4h]
  const char *v18; // [esp+40h] [ebp-D0h]
  _DWORD *v19; // [esp+44h] [ebp-CCh]
  int *v20; // [esp+48h] [ebp-C8h]
  void *v21; // [esp+4Ch] [ebp-C4h]
  int *v22; // [esp+50h] [ebp-C0h]
  void *v23; // [esp+54h] [ebp-BCh]
  int *v24; // [esp+58h] [ebp-B8h]
  void *v25; // [esp+5Ch] [ebp-B4h]
  int *v26; // [esp+60h] [ebp-B0h]
  void *v27; // [esp+64h] [ebp-ACh]
  int v28; // [esp+68h] [ebp-A8h]
  int Base; // [esp+6Ch] [ebp-A4h] BYREF
  int v30; // [esp+70h] [ebp-A0h]
  int v31; // [esp+ECh] [ebp-24h]
  size_t NumOfElements; // [esp+F0h] [ebp-20h]
  int v33; // [esp+F4h] [ebp-1Ch]
  _DWORD *i; // [esp+F8h] [ebp-18h]
  signed int j; // [esp+FCh] [ebp-14h]
  int v36; // [esp+100h] [ebp-10h]
  int v37; // [esp+10Ch] [ebp-4h]

  result = rf_multiplayer_game_flags & 0x2000;
  if ( (rf_multiplayer_game_flags & 0x2000) != 0 )
  {
    result = rf_multiplayer_game_mode_get();
    v31 = result;
    if ( result == 1 || v31 == 2 )
    {
      NumOfElements = 0;
      for ( i = (_DWORD *)dword_87C324; i; i = v19 )
      {
        *(&Base + NumOfElements++) = (int)i;
        if ( *i == dword_87C324 )
          v19 = nullptr;
        else
          v19 = (_DWORD *)*i;
      }
      if ( NumOfElements == 2 )
      {
        if ( **(__int16 **)(Base + 44) < **(__int16 **)(v30 + 44) )
        {
          v28 = Base;
          Base = v30;
          v30 = v28;
        }
      }
      else if ( (int)NumOfElements > 2 )
      {
        qsort(&Base, NumOfElements, 4u, rf_multiplayer_compare_stats_word0_descending);
      }
      v36 = -1;
      v33 = -1;
      if ( byte_704E83 == 1 )
      {
        v36 = 0;
        v33 = 1;
      }
      else
      {
        for ( j = 0; j < (int)NumOfElements; ++j )
        {
          if ( *(&Base + j) == rf_local_fpgun_player )
          {
            if ( (j & 1) != 0 )
            {
              v36 = *(unsigned __int8 *)(*(&Base + j) + 48);
              v33 = v36 == 0;
            }
            else
            {
              v33 = *(unsigned __int8 *)(*(&Base + j) + 48);
              v36 = v33 == 0;
            }
            break;
          }
        }
      }
      for ( j = 0; j < (int)NumOfElements; j += 2 )
      {
        if ( *(unsigned __int8 *)(*(&Base + j) + 48) != v33 )
        {
          *(_BYTE *)(*(&Base + j) + 48) = v33;
          rf_server_broadcast_team_change_packet23(*(_BYTE *)(*(_DWORD *)(*(&Base + j) + 4608) + 20), v33);
          if ( v33 )
          {
            v14 = (const char *)unk_88DF3C;
            v25 = v4;
            v13 = rf_string_construct_from_cstr(v4, (char *)&byte_63B515);
            v12 = v13;
            v37 = 1;
            v3 = 3;
            v24 = &v1;
            v11 = rf_string_concat_object_cstr(&v1, (_DWORD *)(*(&Base + j) + 8), v14);
            v37 = -1;
            rf_multiplayer_notification_enqueue(v1, v2, v3, v4[0]);
          }
          else
          {
            v18 = (const char *)unk_88DF40;
            v27 = v4;
            v17 = rf_string_construct_from_cstr(v4, (char *)&byte_63B514);
            v16 = v17;
            v37 = 0;
            v3 = 2;
            v26 = &v1;
            v15 = rf_string_concat_object_cstr(&v1, (_DWORD *)(*(&Base + j) + 8), v18);
            v37 = -1;
            rf_multiplayer_notification_enqueue(v1, v2, v3, v4[0]);
          }
        }
      }
      for ( j = 1; ; j += 2 )
      {
        result = j;
        if ( j >= (int)NumOfElements )
          break;
        if ( *(unsigned __int8 *)(*(&Base + j) + 48) != v36 )
        {
          *(_BYTE *)(*(&Base + j) + 48) = v36;
          rf_server_broadcast_team_change_packet23(*(_BYTE *)(*(_DWORD *)(*(&Base + j) + 4608) + 20), v36);
          if ( v36 )
          {
            v6 = (const char *)unk_88DF3C;
            v21 = v4;
            v5 = rf_string_construct_from_cstr(v4, (char *)&byte_63B517);
            v4[4] = (int)v5;
            v37 = 3;
            v3 = 3;
            v20 = &v1;
            v4[3] = (int)rf_string_concat_object_cstr(&v1, (_DWORD *)(*(&Base + j) + 8), v6);
            v37 = -1;
            rf_multiplayer_notification_enqueue(v1, v2, v3, v4[0]);
          }
          else
          {
            v10 = (const char *)unk_88DF40;
            v23 = v4;
            v9 = rf_string_construct_from_cstr(v4, (char *)&byte_63B516);
            v8 = v9;
            v37 = 2;
            v3 = 2;
            v22 = &v1;
            v7 = rf_string_concat_object_cstr(&v1, (_DWORD *)(*(&Base + j) + 8), v10);
            v37 = -1;
            rf_multiplayer_notification_enqueue(v1, v2, v3, v4[0]);
          }
        }
      }
    }
  }
  return result;
}

