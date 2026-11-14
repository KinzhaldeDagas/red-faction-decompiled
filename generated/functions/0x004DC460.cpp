// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DC460 rf_player_dispatch_use_after_local_special_action
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl player. Missing resolved entity does nothing. Only global local player invokes special-use handler; AL EXACT1 suppresses all following general dispatch. AL0 after successful remote-charge pickup therefore continues. Multiplayer EXACT1 with server-authority byte0 sends four-byte packet helper4B23C0 using byte20 of player network record4608; otherwise calls general use dispatch(player,entity). Nonzero authority values accepted. No own network-record NULL check, request-result handling or retry.
void __usercall rf_player_dispatch_use_after_local_special_action(double a1@<st0>, _DWORD *a2)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = rf_entity_resolve_handle(a2[5]);
  if ( v2 && (a2 != (_DWORD *)rf_local_fpgun_player || rf_player_try_local_special_use_action((int)a2, v2) != 1) )
  {
    if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
      rf_player_use_interaction_dispatch(a1, a2, v2);
    else
      rf_client_send_use_key_pressed_packet16(*(_BYTE *)(a2[1152] + 20));
  }
}

