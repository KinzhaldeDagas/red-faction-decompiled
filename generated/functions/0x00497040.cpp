// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00497040 rf_ctf_flag_touch
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// Cdecl(player, item). Requires mode1; rejects cooldown only when is_armed returns exactly1 and elapsed is zero. Item instance +700 bit20 selects red; every other item follows blue
// path. Already-carried selected flag returns immediately. For red, any nonzero player team byte +48 is enemy pickup; zero is own return. For blue, team exactly1 is own return; every
// other value is enemy pickup.
// Enemy pickup sets selected carrier, plays positional event64, sets player score[+44] byte+6=1, broadcasts packet31, and if local player emits style4 localized stolen-enemy-flag
// text88E324. Own return requires selected instance home bit200 clear, then event66, home reset(selector,1), packet34(selector,player), return feedback and +1 frag in that order. No
// own authority/initialized/player/item/score/net null guard. Setter ABI is one pointer despite reserved/sound stack words in caller. Notifications consume two RFStrings with native
// 20-byte caller cleanup.
void __cdecl rf_ctf_flag_touch(int a1, int a2)
{
  int v2; // [esp-8h] [ebp-54h] BYREF
  int v3; // [esp-4h] [ebp-50h]
  int v4; // [esp+0h] [ebp-4Ch]
  int v5[5]; // [esp+4h] [ebp-48h] BYREF
  _DWORD *v6; // [esp+18h] [ebp-34h]
  char *v7; // [esp+1Ch] [ebp-30h]
  _DWORD *v8; // [esp+20h] [ebp-2Ch]
  _DWORD *v9; // [esp+24h] [ebp-28h]
  _DWORD *v10; // [esp+28h] [ebp-24h]
  char *Source; // [esp+2Ch] [ebp-20h]
  int *v12; // [esp+30h] [ebp-1Ch]
  void *v13; // [esp+34h] [ebp-18h]
  int *v14; // [esp+38h] [ebp-14h]
  void *v15; // [esp+3Ch] [ebp-10h]
  int v16; // [esp+48h] [ebp-4h]

  if ( rf_multiplayer_game_mode_get() == 1
    && (!rf_replicator_is_armed(&unk_77D72C) || rf_replicator_has_elapsed(&unk_77D72C)) )
  {
    if ( (*(_DWORD *)(a2 + 700) & 0x20) != 0 )
    {
      if ( !rf_ctf_red_carrier_get() )
      {
        if ( *(_BYTE *)(a1 + 48) )
        {
          rf_ctf_red_carrier_set(a1);
          rf_gamesound_play_positional_event(64, (float *)(a2 + 60), 1.0, (int)&unk_17F10B0, 0);
          *(_BYTE *)(*(_DWORD *)(a1 + 44) + 6) = 1;
          rf_ctf_broadcast_flag_taken_packet31(a1);
          if ( rf_local_fpgun_player && a1 == rf_local_fpgun_player )
          {
            Source = (char *)unk_88E324;
            v15 = v5;
            v10 = rf_string_construct_from_cstr(v5, (char *)&byte_639FC3);
            v9 = v10;
            v16 = 0;
            v4 = 4;
            v14 = &v2;
            v8 = rf_string_construct_from_cstr(&v2, Source);
            v16 = -1;
            rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
          }
        }
        else if ( (*(_DWORD *)(a2 + 700) & 0x200) == 0 )
        {
          rf_gamesound_play_event(66, 0, 0.0, 1.0);
          rf_ctf_return_flag_home(1, 1);
          rf_ctf_broadcast_flag_returned_packet34(1, a1);
          rf_ctf_flag_return_notification(a1, 1);
          rf_multiplayer_player_add_frags(a1, 1);
        }
      }
    }
    else if ( !rf_ctf_blue_carrier_get() )
    {
      if ( *(_BYTE *)(a1 + 48) == 1 )
      {
        if ( (*(_DWORD *)(a2 + 700) & 0x200) == 0 )
        {
          rf_gamesound_play_event(66, 0, 0.0, 1.0);
          rf_ctf_return_flag_home(0, 1);
          rf_ctf_broadcast_flag_returned_packet34(0, a1);
          rf_ctf_flag_return_notification(a1, 0);
          rf_multiplayer_player_add_frags(a1, 1);
        }
      }
      else
      {
        rf_ctf_blue_carrier_set(a1);
        rf_gamesound_play_positional_event(64, (float *)(a2 + 60), 1.0, (int)&unk_17F10B0, 0);
        *(_BYTE *)(*(_DWORD *)(a1 + 44) + 6) = 1;
        rf_ctf_broadcast_flag_taken_packet31(a1);
        if ( rf_local_fpgun_player && a1 == rf_local_fpgun_player )
        {
          v7 = (char *)unk_88E324;
          v13 = v5;
          v6 = rf_string_construct_from_cstr(v5, (char *)&byte_639FDF);
          v5[4] = (int)v6;
          v16 = 1;
          v4 = 4;
          v12 = &v2;
          v5[3] = (int)rf_string_construct_from_cstr(&v2, v7);
          v16 = -1;
          rf_multiplayer_notification_enqueue(v2, v3, v4, v5[0]);
        }
      }
    }
  }
}

