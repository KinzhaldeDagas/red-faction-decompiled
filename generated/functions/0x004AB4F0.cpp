// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AB4F0 rf_server_send_clutter_active_bitset_packet29
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): cdecl(recipient). Only runtime==EXACT1 AND authority==EXACT1. Builds opcode decimal29 (hex1D), payload signed countDWORD666B74 followed by
// signed-trunc((count+7)/8) bytes from bitset666B88. Uses unsigned16 cursor, payloadWORD=total-3, reliable queue(recipient,packet,total,requireActive0). No count<=3200,
// stack-capacity, negative-count/overflow or bitset/source guard; negative count can yield no bytes, oversized count can exceed local buffer before cursor wrap. Receiver4AB650 owns
// separate equality/upper-bound admission. Return is guard/queue residue.
int __cdecl rf_server_send_clutter_active_bitset_packet29(int a1)
{
  int result; // eax
  int i; // [esp+8h] [ebp-214h]
  unsigned __int16 v3; // [esp+10h] [ebp-20Ch]
  unsigned __int8 Src[516]; // [esp+14h] [ebp-208h] BYREF

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    Src[0] = 29;
    *(_DWORD *)&Src[3] = dword_666B74;
    v3 = 7;
    for ( i = 0; i < (dword_666B74 + 7) / 8; ++i )
      Src[v3++] = unk_666B88[i];
    *(_WORD *)&Src[1] = v3 - 3;
    return rf_multiplayer_queue_reliable_packet(a1, Src, v3, 0);
  }
  return result;
}

