// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A4E40 rf_multiplayer_send_left_game_unreliable_packet7
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(endpoint,raw id BYTE,raw reason BYTE). Fixed5-byte opcode7,payload2,raw low bytes at3/4. Sends directly unreliable, no aggregation, state mutation, endpoint/id/reason
// validation or mode/authority guard. Client leave helper sends to shared server endpoint704EF4.
int __cdecl rf_multiplayer_send_left_game_unreliable_packet7(int a1, char a2, char a3)
{
  char v4; // [esp+Ch] [ebp-208h] BYREF
  __int16 v5; // [esp+Dh] [ebp-207h]
  char v6; // [esp+Fh] [ebp-205h]
  char v7; // [esp+10h] [ebp-204h]

  v4 = 7;
  v6 = a2;
  v7 = a3;
  v5 = 2;
  return rf_network_send_unreliable(a1, &v4, 5u);
}

