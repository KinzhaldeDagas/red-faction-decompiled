// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A99E0 rf_multiplayer_client_queue_entity_update_packet38
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): No arguments. Runs ONLY runtime1/authority0 AND deadline7B2538 elapsed any nonzero; no separate armed test. Rearms50ms BEFORE serialization. Builds
// local512-byte packet opcode38, calls record encoder4A8630(localPlayer,localEntity,&packet[3]), appends DWORD-1 sentinel even when record encoder returns0, sets payloadWORD=total-3,
// queues unreliable to local player. No pointer/capacity/size, connection-state or encoder-failure gate and no transport-result rollback/retry compensation. Native game-clock
// deadline, not performance-clock elapsed delta.
char rf_multiplayer_client_queue_entity_update_packet38()
{
  char result; // al
  size_t Size; // [esp+4h] [ebp-20Ch]
  char Src[512]; // [esp+8h] [ebp-208h] BYREF
  int v3; // [esp+20Ch] [ebp-4h]

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    result = rf_clock_deadline_has_elapsed_half_period(&dword_7B2538);
    if ( result )
    {
      rf_clock_deadline_set_wrapped_offset(&dword_7B2538, 50);
      Src[0] = 38;
      Size = rf_replication_encode_entity_record38(rf_local_fpgun_player, dword_681E38, (int)&Src[3]) + 3;
      v3 = -1;
      *(_DWORD *)&Src[Size] = -1;
      Size += 4;
      *(_WORD *)&Src[1] = Size - 3;
      return rf_network_queue_unreliable_player_packet(rf_local_fpgun_player, Src, Size);
    }
  }
  return result;
}

