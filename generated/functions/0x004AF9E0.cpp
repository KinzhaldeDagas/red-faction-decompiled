// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AF9E0 rf_server_send_pregame_glass_bitset18
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout): Cdecl
// recipient. Only runtime1 authority EXACT1 AND signed global glassCount822714>0. Build opcode18, copy signed native truncating(glassCount+7)/8 bytes from global8222F8 directly,
// preserving all padding bits. No count field: shared authored count determines receiver layout. WORD payload bytesCopied,total3+bytesCopied using unsigned16 cursor. Single512-byte
// stack buffer, no <=509-byte/128-bit count clamp or finite arithmetic overflow guard; no allocation or packet splitting. Reliable_queue(recipient,packet,total,requireActive0). No
// recipient validation; returns delegate/incidental EAX. Count<=0 sends nothing, not empty reset packet. Receiver49CB30 uses fixed borrowed128-bit stack storage and removes bit0
// groups; sender does not invert or sanitize bits.
int __cdecl rf_server_send_pregame_glass_bitset18(int a1)
{
  int result; // eax
  int i; // [esp+8h] [ebp-210h]
  unsigned __int16 v3; // [esp+Ch] [ebp-20Ch]
  unsigned __int8 Src; // [esp+10h] [ebp-208h] BYREF
  __int16 v5; // [esp+11h] [ebp-207h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 && dword_822714 > 0 )
  {
    Src = 18;
    v3 = 3;
    for ( i = 0; i < (dword_822714 + 7) / 8; ++i )
      *(&Src + v3++) = unk_8222F8[i];
    v5 = v3 - 3;
    return rf_multiplayer_queue_reliable_packet(a1, &Src, v3, 0);
  }
  return result;
}

