// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049BC50 rf_client_send_fall_damage_packet_49
// UNREALRED VERIFIED [respawn-surrounding]: Multiplayer non-authority sender for packet 49 (fall_damage). Builds a seven-byte packet with type 49, payload length four, and one float containing the already computed raw fall damage, then sends through the local player's connection.
int __cdecl rf_client_send_fall_damage_packet_49(float a1)
{
  int result; // eax
  char Src[516]; // [esp+Ch] [ebp-208h] BYREF

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    Src[0] = 49;
    *(float *)&Src[3] = a1;
    *(_WORD *)&Src[1] = 4;
    return rf_network_queue_unreliable_player_packet(rf_local_fpgun_player, Src, 7);
  }
  return result;
}

