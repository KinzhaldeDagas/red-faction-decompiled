// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049BDD0 rf_geomod_broadcast_live_boolean_packet41
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet registry, field permutations, x87 transfers, face-list mutation and HUD native stores): Cdecl
// pointer to runtime100-byte operation. Unconditionally builds opcode decimal41 (hex29, registry name boolean), WORD payload100, total103 bytes. Wire DWORD order is runtime offsets
// [0,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,4,76,80,84,88,92,96]; not a contiguous memcpy of the runtime struct. Offsets0/4/56 use integer MOV, remaining22 fields use x87
// FLD/FSTP through single precision temporaries, so signaling NaN transformations are not guaranteed bit preservation. Cursor is unsigned16. Walk circular player list87C324, skip
// local player, require unguarded player.net1200 handle10 != -1 AND state0C==2, then reliable-queue(player,packet,103,requireActive0). Success/failure not aggregated; no own
// runtime/authority guard or pointer validation. Next link read after queue call, no saved-next-before-callback protection. Nominal short return is incidental EAX residue, not
// delivery success. Old packet_29 naming referred to hexadecimal opcode29, equivalent to decimal41.
__int16 __cdecl rf_geomod_broadcast_live_boolean_packet41(int a1)
{
  int v1; // eax
  int v3; // [esp+0h] [ebp-278h]
  unsigned __int8 Src[7]; // [esp+70h] [ebp-208h] BYREF
  float v5; // [esp+77h] [ebp-201h]
  float v6; // [esp+7Bh] [ebp-1FDh]
  float v7; // [esp+7Fh] [ebp-1F9h]
  float v8; // [esp+83h] [ebp-1F5h]
  float v9; // [esp+87h] [ebp-1F1h]
  float v10; // [esp+8Bh] [ebp-1EDh]
  float v11; // [esp+8Fh] [ebp-1E9h]
  float v12; // [esp+93h] [ebp-1E5h]
  float v13; // [esp+97h] [ebp-1E1h]
  float v14; // [esp+9Bh] [ebp-1DDh]
  float v15; // [esp+9Fh] [ebp-1D9h]
  float v16; // [esp+A3h] [ebp-1D5h]
  int v17; // [esp+A7h] [ebp-1D1h]
  float v18; // [esp+ABh] [ebp-1CDh]
  float v19; // [esp+AFh] [ebp-1C9h]
  float v20; // [esp+B3h] [ebp-1C5h]
  float v21; // [esp+B7h] [ebp-1C1h]
  int v22; // [esp+BBh] [ebp-1BDh]
  float v23; // [esp+BFh] [ebp-1B9h]
  float v24; // [esp+C3h] [ebp-1B5h]
  float v25; // [esp+C7h] [ebp-1B1h]
  float v26; // [esp+CBh] [ebp-1ADh]
  float v27; // [esp+CFh] [ebp-1A9h]
  float v28; // [esp+D3h] [ebp-1A5h]
  int i; // [esp+274h] [ebp-4h]

  qmemcpy(Src, ")d", 2);
  *(_DWORD *)&Src[3] = *(_DWORD *)a1;
  v5 = *(float *)(a1 + 8);
  v6 = *(float *)(a1 + 12);
  v7 = *(float *)(a1 + 16);
  v8 = *(float *)(a1 + 20);
  v9 = *(float *)(a1 + 24);
  v10 = *(float *)(a1 + 28);
  v11 = *(float *)(a1 + 32);
  v12 = *(float *)(a1 + 36);
  v13 = *(float *)(a1 + 40);
  v14 = *(float *)(a1 + 44);
  v15 = *(float *)(a1 + 48);
  v16 = *(float *)(a1 + 52);
  v17 = *(_DWORD *)(a1 + 56);
  v18 = *(float *)(a1 + 60);
  v19 = *(float *)(a1 + 64);
  v20 = *(float *)(a1 + 68);
  v21 = *(float *)(a1 + 72);
  v22 = *(_DWORD *)(a1 + 4);
  v23 = *(float *)(a1 + 76);
  v24 = *(float *)(a1 + 80);
  v25 = *(float *)(a1 + 84);
  v26 = *(float *)(a1 + 88);
  v27 = *(float *)(a1 + 92);
  v28 = *(float *)(a1 + 96);
  LOWORD(v1) = 100;
  for ( i = dword_87C324; i; i = v3 )
  {
    if ( i != rf_local_fpgun_player
      && *(_DWORD *)(*(_DWORD *)(i + 4608) + 16) != -1
      && *(_DWORD *)(*(_DWORD *)(i + 4608) + 12) == 2 )
    {
      rf_multiplayer_queue_reliable_packet(i, Src, 0x67u, 0);
    }
    LOWORD(v1) = i;
    if ( *(_DWORD *)i == dword_87C324 )
    {
      v3 = 0;
    }
    else
    {
      v1 = *(_DWORD *)i;
      v3 = *(_DWORD *)i;
    }
  }
  return v1;
}

