// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049ACC0 sub_49ACC0
// UNREALRED VERIFIED [lan-body-credit-20261029] Explicit local suicide path: on multiplayer server sets local entity life=-1000 and common+0x270 to local player network-id before server death handling. This byte writer is not evidence of recording an attacker on ordinary nonlethal damage.
void sub_49ACC0()
{
  if ( dword_681E38 )
  {
    if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
      rf_client_send_suicide_packet20();
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 && dword_681E38 )
    {
      *(float *)(dword_681E38 + 52) = -1000.0;
      *(_BYTE *)(dword_681E38 + 624) = *(_BYTE *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 20);
      if ( rf_local_fpgun_player )
      {
        rf_ctf_drop_player_carried_flag(rf_local_fpgun_player);
        rf_network_remove_player_flag_nodes(rf_local_fpgun_player);
      }
    }
  }
}

