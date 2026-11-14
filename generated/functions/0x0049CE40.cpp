// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049CE40 rf_multiplayer_hud_reset_state_and_announce_team
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet registry, field permutations, x87 transfers, face-list mutation and HUD native stores): Noarg
// HUD reset with no runtime/authority guard. Set float662914/66291C/66293C=255 and bytes662918/662919/66291A=1; zero10 bytes77FE30..39; set DWORD662938=10; zero time-left
// alpha77FE3C, bytes77FE3A/3B, seconds77FE48/minutes77FE44/hours77FE40 and visibility77FE4C. Set float662944=192. Arm77FF14 for3000ms; assign empty verified63A41F to RFString77FE58;
// disarm77FF18 and77FE6C; clear bytes77FE4D/4E, set66291B=1, zero float77FE50; arm chat blink77FE68 offset0 and set77FE2C=1. Then only if local player nonNULL AND game-mode delegate
// nonzero, build localized88E1B4 plus team text: local BYTE48==0 uses88E1B8 with notification style2, any nonzero uses88E1BC with style3; both pass empty8-byte suffix and own
// concatenated8-byte RFString (20-byte caller cleanup). Hardcoded You are on team/RED/BLUE branches are unreachable XOR/JZ paths; localized pointers used. Destroy local prefix string
// with SEH cleanup. Does not clear eight stored notification rows here; all reset writes precede optional team announcement.
void rf_multiplayer_hud_reset_state_and_announce_team()
{
  int v0[2]; // [esp-14h] [ebp-64h] BYREF
  int v1; // [esp-Ch] [ebp-5Ch]
  int v2[5]; // [esp-8h] [ebp-58h] BYREF
  _DWORD *v3; // [esp+Ch] [ebp-44h]
  const char *v4; // [esp+10h] [ebp-40h]
  void *v5; // [esp+14h] [ebp-3Ch]
  _DWORD *v6; // [esp+18h] [ebp-38h]
  _DWORD *v7; // [esp+1Ch] [ebp-34h]
  const char *v8; // [esp+20h] [ebp-30h]
  char *Source; // [esp+24h] [ebp-2Ch]
  int *v10; // [esp+28h] [ebp-28h]
  void *v11; // [esp+2Ch] [ebp-24h]
  int *v12; // [esp+30h] [ebp-20h]
  void *v13; // [esp+34h] [ebp-1Ch]
  _DWORD v14[2]; // [esp+38h] [ebp-18h] BYREF
  int i; // [esp+40h] [ebp-10h]
  int v16; // [esp+4Ch] [ebp-4h]

  flt_662914 = 255.0;
  byte_662918 = 1;
  flt_66291C = 255.0;
  byte_662919 = 1;
  for ( i = 0; i < 10; ++i )
    unk_77FE30[i] = 0;
  dword_662938 = 10;
  flt_66293C = 255.0;
  byte_66291A = 1;
  rf_multiplayer_time_left_alpha = 0.0;
  unk_77FE3A = 0;
  unk_77FE3B = 0;
  rf_multiplayer_time_left_seconds = 0;
  rf_multiplayer_time_left_minutes = 0;
  rf_multiplayer_time_left_hours = 0;
  rf_multiplayer_time_left_visible = 0;
  flt_662944 = 192.0;
  rf_replicator_arm_milliseconds(&unk_77FF14, 3000);
  rf_string_assign_from_cstr(dword_77FE58, (char *)&byte_63A41F);
  rf_replicator_reset(dword_77FF18);
  rf_replicator_reset(&unk_77FE6C);
  unk_77FE4D = 0;
  unk_77FE4E = 0;
  byte_66291B = 1;
  unk_77FE50 = 0.0;
  rf_replicator_arm_milliseconds(&unk_77FE68, 0);
  unk_77FE2C = 1;
  if ( rf_local_fpgun_player && rf_multiplayer_game_mode_get() )
  {
    Source = dword_88E1B4;
    rf_string_construct_from_cstr(v14, dword_88E1B4);
    v16 = 0;
    if ( *(_BYTE *)(rf_local_fpgun_player + 48) )
    {
      v4 = (const char *)unk_88E1BC;
      v11 = v2;
      v3 = rf_string_construct_from_cstr(v2, (char *)&byte_63A462);
      v2[4] = (int)v3;
      LOBYTE(v16) = 2;
      v1 = 3;
      v10 = v0;
      v2[3] = (int)rf_string_concat_object_cstr(v0, v14, v4);
    }
    else
    {
      v8 = (const char *)unk_88E1B8;
      v13 = v2;
      v7 = rf_string_construct_from_cstr(v2, (char *)&byte_63A461);
      v6 = v7;
      LOBYTE(v16) = 1;
      v1 = 2;
      v12 = v0;
      v5 = rf_string_concat_object_cstr(v0, v14, v8);
    }
    LOBYTE(v16) = 0;
    rf_multiplayer_notification_enqueue(v0[0], v0[1], v1, v2[0]);
    v16 = -1;
    rf_string_destroy_buffer(v14);
  }
}

