// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049BD40 rf_server_process_fall_damage_packet_49
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662B94 registers opcode49 (fall_damage), callback0x0049BD40. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
void __cdecl rf_server_process_fall_damage_packet_49(float *a1, int a2)
{
  float v2; // [esp+1Ch] [ebp-10h]
  int v3; // [esp+20h] [ebp-Ch]
  _DWORD *v4; // [esp+24h] [ebp-8h]

  v2 = *a1;
  v4 = rf_player_find_by_network_endpoint(a2);
  if ( v4 )
  {
    v3 = rf_entity_resolve_handle(v4[5]);
    if ( v3 )
      rf_damage_dispatch(*(_DWORD *)(v3 + 44), v2, *(_DWORD *)(v3 + 44), -1, 9, 0, -1, 0);
  }
}

