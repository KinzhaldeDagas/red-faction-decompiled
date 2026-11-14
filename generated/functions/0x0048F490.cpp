// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048F490 sub_48F490
// UNREALRED VERIFIED [lan-match-flow-20261028] Authority match-limit evaluation, called by 0x48F120. A positive float time limit at 0x704EE4 ends when shared level elapsed seconds at 0x6FC428 reach or exceed it. Raw mode 0 scans all players and sign-extends score(Player+0x2C)+2 as a 16-bit frag value, ending when >= dword frag limit 0x704EE8. There is no positive frag-limit admission guard: zero or -1 is not a recovered unlimited setting. Modes 2/1 use team-frag/capture accessors. Either limit path calls 0x4A5600(NULL); end-reason priority/tie presentation is not recovered here.
char sub_48F490()
{
  int v0; // eax
  _DWORD *v2; // [esp+0h] [ebp-14h]
  bool v3; // [esp+Fh] [ebp-5h]
  _DWORD *i; // [esp+10h] [ebp-4h]

  v3 = 0;
  if ( *(float *)&dword_704EE4 > 0.0 )
    v3 = *(float *)&dword_704EE4 <= (double)*(float *)&dword_6FC428;
  v0 = rf_multiplayer_game_mode_get();
  if ( v0 )
  {
    if ( v0 == 1 )
    {
      LOBYTE(v0) = rf_ctf_red_capture_byte_get();
      if ( (unsigned __int8)v0 >= *(int *)unk_704EF0
        || (LOBYTE(v0) = rf_ctf_blue_capture_byte_get(), (unsigned __int8)v0 >= *(int *)unk_704EF0) )
      {
        v3 = 1;
      }
    }
    else if ( v0 == 2 )
    {
      LOBYTE(v0) = rf_multiplayer_get_team0_score_byte();
      if ( (unsigned __int8)v0 >= *(int *)unk_704EE8
        || (LOBYTE(v0) = rf_multiplayer_get_team1_score_byte(), (unsigned __int8)v0 >= *(int *)unk_704EE8) )
      {
        v3 = 1;
      }
    }
  }
  else
  {
    for ( i = (_DWORD *)dword_87C324; i; i = v2 )
    {
      v0 = *(__int16 *)(i[11] + 2);
      if ( v0 >= *(int *)unk_704EE8 )
      {
        v3 = 1;
        break;
      }
      if ( *i == dword_87C324 )
        v2 = nullptr;
      else
        v2 = (_DWORD *)*i;
      LOBYTE(v0) = (_BYTE)v2;
    }
  }
  if ( v3 )
    LOBYTE(v0) = sub_4A5600(nullptr);
  return v0;
}

