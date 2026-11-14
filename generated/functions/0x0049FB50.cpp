// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049FB50 rf_multiplayer_dispatch_packet_envelopes
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(buffer,signed total bytes,source endpoint,optional statistics player), returns bytes consumed before first rejection. Signed cursor starts0; total<=0 consumes0. Needs>=3
// remaining bytes,reads opcodeBYTE and payload lengthWORD. Opcodes0..4 bypass endpoint admission. Others: runtime1/authority1 requires any known player at source endpoint;
// runtime1/authority0 requires strict server endpoint704EF4 equality including port; every other state requires opaque DWORD664810!=-1. No claimed payload-id/source binding here.
// Rejects payload length>total input,opcode>55,total envelope(payload+3)>remaining, returning current cursor. Native JLE55 ACCEPTS opcode55 even though original descriptor
// table662948 has only55 valid rows0..54. It indexes callback66294C+12*opcode; opcode55 uses662BE0 (not valid descriptor callback; shared logging checkpoint), original following
// bytes are FFFFFFFF FFFFFFFF 00000000. No callback-null/code-address validation.
// For accepted opcode invokes callback(payloadPointer,source) with8-byte caller cleanup, NO payload length passed. Advances cursor,then if optional stats player still in live list
// records incoming envelope bytes/opcode at net+28; no net-null guard. Handler removal suppresses its stats update. Processes concatenated envelopes synchronously; returns whole
// input length only when fully consumed. All55 opcode/name/callback rows and names independently PE-verified.
// Compiled registry (opcode/name => callback), all55 rows and names verified against original PE:
// 0 game_info_request => 0x004A4250
// 1 game_info => 0x004A3D70
// 2 join_request => 0x004A3200
// 3 join_accept => 0x004A29E0
// 4 join_deny => 0x004A2000
// 5 new_player => 0x004A23E0
// 6 players => 0x004B03C0
// 7 left_game => 0x004A4F40
// 8 end_game => 0x004A4BD0
// 9 state_info_req => 0x004AFD60
// 10 state_info_done => 0x004AFBC0
// 11 client_in_game => 0x004B0890
// 12 chat_line => 0x0045AF80
// 13 name_change => 0x0048F990
// 14 respawn_request => 0x004AE110
// 15 trigger_activate => 0x004B2310
// 16 use_key_pressed => 0x004B2490
// 17 pregame_boolean => 0x0049C7E0
// 18 pregame_glass => 0x0049CB30
// 19 pregame_remote_charge => 0x004AC5E0
// 20 suicide => 0x0049AC60
// 21 enter_limbo => 0x004A57C0
// 22 leave_limbo => 0x004A59D0
// 23 team_change => 0x004B10A0
// 24 ping => 0x004B4BA0
// 25 pong => 0x004B4C90
// 26 netgame_update => 0x004B51F0
// 27 rate_change => 0x004ADD30
// 28 select_weapon_request => 0x004B6080
// 29 clutter_update => 0x004AB650
// 30 clutter_kill => 0x004AB9A0
// 31 ctf_flag_picked_up => 0x00497BC0
// 32 ctf_flag_captured => 0x00498100
// 33 ctf_flag_update => 0x00498E50
// 34 ctf_flag_returned => 0x00498400
// 35 ctf_flag_dropped => 0x00499A00
// 36 remote_charge_kill => 0x004B65F0
// 37 item_update => 0x004A1D90
// 38 obj_update => 0x004A8F70
// 39 obj_kill => 0x004AABA0
// 40 item_apply => 0x004A0830
// 41 boolean => 0x0049C440
// 42 mover_update => 0x004A99D0
// 43 respawn => 0x004A0AB0
// 44 entity_create => 0x0049A550
// 45 item_create => 0x004A16F0
// 46 reload => 0x004B6310
// 47 reload_request => 0x004B6280
// 48 weapon_fire => 0x004A7F20
// 49 fall_damage => 0x0049BD40
// 50 rcon_request => 0x0048C1E0
// 51 rcon => 0x0048C630
// 52 sound_packet => 0x00494950
// 53 team_score => 0x00494E80
// 54 glass_kill => 0x00495200
int __cdecl rf_multiplayer_dispatch_packet_envelopes(int a1, int a2, int a3, _DWORD *a4)
{
  int v5; // [esp+0h] [ebp-18h]
  int v6; // [esp+8h] [ebp-10h]
  unsigned __int8 v7; // [esp+13h] [ebp-5h]
  unsigned __int16 v8; // [esp+14h] [ebp-4h]

  v6 = 0;
  while ( v6 < a2 )
  {
    if ( a2 - v6 < 3 )
      return v6;
    v7 = *(_BYTE *)(v6 + a1);
    v8 = *(_WORD *)(v6 + a1 + 1);
    if ( v7 && v7 != 1 && v7 != 2 && v7 != 3 && v7 != 4 )
    {
      if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      {
        if ( !rf_player_find_by_network_endpoint(a3) )
          return v6;
      }
      else if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
      {
        if ( dword_664810 == -1 )
          return v6;
      }
      else if ( rf_network_compare_endpoints((int)&dword_704EF4, a3, 1) )
      {
        return v6;
      }
    }
    if ( v8 > a2 )
      return v6;
    if ( v7 > 0x37u )
      return v6;
    v5 = v8 + 3;
    if ( v5 > a2 - v6 )
      return v6;
    (*(&off_66294C + 3 * v7))(v6 + a1 + 3, a3);
    v6 += v5;
    if ( a4 )
    {
      if ( rf_player_record_is_in_live_list(a4) )
        rf_net_statistics_record_packet((_DWORD *)(a4[1152] + 28), v5, 0, v7);
    }
  }
  return v6;
}

