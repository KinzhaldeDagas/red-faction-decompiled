// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A4110 rf_multiplayer_lan_broadcast_query
// UNREALRED VERIFIED [local-multiplayer-20261028] Builds query type0 with16-bit payload length0 and broadcasts3 bytes through0x59BAB0 on retail UDP port7755. This is native transport evidence; Unreal session transport is an explicit adaptation and is not RF wire-compatible.
int rf_multiplayer_lan_broadcast_query()
{
  char v1; // [esp+8h] [ebp-208h] BYREF
  __int16 v2; // [esp+9h] [ebp-207h]

  v1 = 0;
  v2 = 0;
  rf_network_send_broadcast_unreliable(7755, (int)&v1, 3);
  return 0;
}

