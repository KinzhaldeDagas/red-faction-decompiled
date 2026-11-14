// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B51F0 rf_multiplayer_apply_netgame_update_payload26
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(payload), no own mode/authority/null/length guard. Descriptor26 netgame_update points here. Reads mask BYTE; ONLY when mask&3 nonzero consumes count BYTE and that many id
// records. Each id always read;mask1 reads metric WORD and quantized BYTE even if player unknown,then if found zero-extends metric into net DWORD+1452 and stores float(byte/255.0)
// at+1456. Runtime1/authority0 plus found LOCAL player seeds reliable RTT from metric (delegate handles invalid connection). Mask2 reads score WORD2/4 and writes found player
// score+44; no net/score-null checks. Unknown player still consumes all flagged fields.
// Mask4 then reads shared clock6FC428 and704EE4 floats at current cursor with native fld/fstp. Mask4 alone therefore has NO count BYTE. Unknown mask bits ignored;no own
// source/player-id association. Clock path returns AL0; other paths return incidental loop/mask artifacts. It updates replicated netgame state, not empty pong25; original repeatable
// misidentification corrected.
unsigned __int8 __cdecl rf_multiplayer_apply_netgame_update_payload26(unsigned __int8 *a1)
{
  unsigned __int8 result; // al
  _DWORD *v2; // [esp+4h] [ebp-24h]
  unsigned __int8 v3; // [esp+Ah] [ebp-1Eh]
  unsigned __int8 v4; // [esp+Bh] [ebp-1Dh]
  unsigned __int16 v5; // [esp+Ch] [ebp-1Ch]
  int i; // [esp+10h] [ebp-18h]
  char v7; // [esp+17h] [ebp-11h]
  __int16 v8; // [esp+18h] [ebp-10h]
  __int16 v9; // [esp+1Ch] [ebp-Ch]
  _BYTE v10[5]; // [esp+23h] [ebp-5h]
  int v11; // [esp+24h] [ebp-4h]
  int v12; // [esp+24h] [ebp-4h]
  char v13; // [esp+27h] [ebp-1h]

  v13 = 0;
  *(_DWORD *)v10 = *a1;
  ++*(_DWORD *)&v10[1];
  result = 0;
  if ( (v10[0] & 3) != 0 )
  {
    result = a1[*(_DWORD *)&v10[1]];
    v3 = result;
    ++*(_DWORD *)&v10[1];
    for ( i = 0; i < v3; ++i )
    {
      v7 = a1[(*(_DWORD *)&v10[1])++];
      v2 = rf_player_find_by_network_id(v7);
      if ( (v10[0] & 1) != 0 )
      {
        v5 = *(_WORD *)&a1[*(_DWORD *)&v10[1]];
        v11 = *(_DWORD *)&v10[1] + 2;
        v4 = a1[v11];
        *(_DWORD *)&v10[1] = v11 + 1;
        if ( v2 )
        {
          *(_DWORD *)(v2[1152] + 1452) = v5;
          *(float *)(v2[1152] + 1456) = (double)v4 / 255.0;
          if ( rf_multiplayer_runtime_mode == 1
            && !rf_multiplayer_server_authority
            && v2 == (_DWORD *)rf_local_fpgun_player )
          {
            rf_reliable_udp_seed_rtt_before_ten_samples(*(_DWORD *)(v2[1152] + 16), *(_DWORD *)(v2[1152] + 1452));
          }
        }
      }
      if ( (v10[0] & 2) != 0 )
      {
        v9 = *(_WORD *)&a1[*(_DWORD *)&v10[1]];
        v12 = *(_DWORD *)&v10[1] + 2;
        v8 = *(_WORD *)&a1[v12];
        *(_DWORD *)&v10[1] = v12 + 2;
        if ( v2 )
        {
          *(_WORD *)(v2[11] + 2) = v9;
          *(_WORD *)(v2[11] + 4) = v8;
        }
      }
      result = i + 1;
    }
  }
  if ( (v10[0] & 4) != 0 )
  {
    dword_6FC428 = *(_DWORD *)&a1[*(_DWORD *)&v10[1]];
    dword_704EE4 = *(_DWORD *)&a1[*(_DWORD *)&v10[1] + 4];
    return 0;
  }
  return result;
}

