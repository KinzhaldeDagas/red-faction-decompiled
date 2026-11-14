// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A4C30 rf_multiplayer_broadcast_left_game_packet7
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Cdecl(raw id BYTE,raw reason BYTE). Fixed5-byte opcode7,payload WORD2,id at3,reason at4; common reliable fanout(buffer,5,0). No own mode/authority/id/reason validation, mutation or
// immediate flush. Both args serialize only low8.
int __cdecl rf_multiplayer_broadcast_left_game_packet7(char a1, char a2)
{
  unsigned __int8 Src; // [esp+Ch] [ebp-208h] BYREF
  __int16 v4; // [esp+Dh] [ebp-207h]
  char v5; // [esp+Fh] [ebp-205h]
  char v6; // [esp+10h] [ebp-204h]

  Src = 7;
  v5 = a1;
  v6 = a2;
  v4 = 2;
  return rf_server_broadcast_packet(&Src, 5, 0);
}

