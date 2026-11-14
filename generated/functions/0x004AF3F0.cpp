// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AF3F0 rf_multiplayer_send_pregame_boolean_history17
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout): Cdecl
// recipient. No own runtime/authority guard. Walk intrusive network-history sentinel whose global name rf_geomod_network_history_head holds first node; follow nodeDWORD0 AFTER queue
// call until sentinel address. Node has8-byte links then100-byte runtime operation. For EVERY node build separate99-byte opcode17 envelope,WORD payload96, no count. Payload DWORD
// runtime offset order[8,12,16,20,24,28,32,36,40,44,48,52,0,60,64,68,72,4,76,80,84,88,92,96]; corresponding node offsets add8. Omit runtime flags56 /node64 entirely. Integer
// runtime0/4 via MOV, other22 fields native FLD/FSTP single temporaries, not general bit-preserving memcpy. Queue reliable(recipient,packet,99,requireActive0) for each; no recipient,
// cutter, finite-value or per-node failure checks, no batch limit. Last queue EAX if any, head pointer incidental if empty. Does not consume/remove history or execute operations.
// Complements receiver49C7E0 which forces omitted flags1 and steps synchronously; live41 uses different100-byte field order.
int __cdecl rf_multiplayer_send_pregame_boolean_history17(int a1)
{
  int result; // eax
  unsigned __int8 Src; // [esp+68h] [ebp-208h] BYREF
  __int16 Src_1; // [esp+69h] [ebp-207h]
  float Src_3; // [esp+6Bh] [ebp-205h]
  float v5; // [esp+6Fh] [ebp-201h]
  float v6; // [esp+73h] [ebp-1FDh]
  float v7; // [esp+77h] [ebp-1F9h]
  float v8; // [esp+7Bh] [ebp-1F5h]
  float v9; // [esp+7Fh] [ebp-1F1h]
  float v10; // [esp+83h] [ebp-1EDh]
  float v11; // [esp+87h] [ebp-1E9h]
  float v12; // [esp+8Bh] [ebp-1E5h]
  float v13; // [esp+8Fh] [ebp-1E1h]
  float v14; // [esp+93h] [ebp-1DDh]
  float v15; // [esp+97h] [ebp-1D9h]
  int v16; // [esp+9Bh] [ebp-1D5h]
  float v17; // [esp+9Fh] [ebp-1D1h]
  float v18; // [esp+A3h] [ebp-1CDh]
  float v19; // [esp+A7h] [ebp-1C9h]
  float v20; // [esp+ABh] [ebp-1C5h]
  int v21; // [esp+AFh] [ebp-1C1h]
  float v22; // [esp+B3h] [ebp-1BDh]
  float v23; // [esp+B7h] [ebp-1B9h]
  float v24; // [esp+BBh] [ebp-1B5h]
  float v25; // [esp+BFh] [ebp-1B1h]
  float v26; // [esp+C3h] [ebp-1ADh]
  float v27; // [esp+C7h] [ebp-1A9h]
  float *i; // [esp+26Ch] [ebp-4h]

  result = rf_geomod_network_history_head;
  for ( i = (float *)rf_geomod_network_history_head; i != (float *)&rf_geomod_network_history_head; i = *(float **)i )
  {
    Src = 17;
    Src_3 = i[4];
    v5 = i[5];
    v6 = i[6];
    v7 = i[7];
    v8 = i[8];
    v9 = i[9];
    v10 = i[10];
    v11 = i[11];
    v12 = i[12];
    v13 = i[13];
    v14 = i[14];
    v15 = i[15];
    v16 = *((_DWORD *)i + 2);
    v17 = i[17];
    v18 = i[18];
    v19 = i[19];
    v20 = i[20];
    v21 = *((_DWORD *)i + 3);
    v22 = i[21];
    v23 = i[22];
    v24 = i[23];
    v25 = i[24];
    v26 = i[25];
    v27 = i[26];
    Src_1 = 96;
    result = rf_multiplayer_queue_reliable_packet(a1, &Src, 0x63u, 0);
  }
  return result;
}

