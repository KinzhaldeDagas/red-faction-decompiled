// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A1F10 rf_server_send_join_rejection_packet4
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(destination endpoint,raw reason BYTE). Requires runtime mode exactly1 and authority exactly1. Fixed4-byte opcode4: header payload WORD1=1, low argument byte at3 without
// normalization/range validation. Direct unreliable send to supplied endpoint; no peer lookup, queue, pending-join mutation or own endpoint-null guard. Existing
// request/admission/allocation-failure paths call this; EAX is guard/transport artifact.
int __cdecl rf_server_send_join_rejection_packet4(int a1, char a2)
{
  int result; // eax
  char v3; // [esp+Ch] [ebp-208h] BYREF
  __int16 v4; // [esp+Dh] [ebp-207h]
  char v5; // [esp+Fh] [ebp-205h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v3 = 4;
    v5 = a2;
    v4 = 1;
    return rf_network_send_unreliable(a1, &v3, 4u);
  }
  return result;
}

