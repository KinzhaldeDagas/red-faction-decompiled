// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049C7E0 rf_geomod_apply_pregame_boolean_payload17
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet registry, field permutations, x87 transfers, face-list mutation and HUD native stores):
// Original descriptor row17 at662A14 is pregame_boolean, decimal17 (hex11). Cdecl payload pointer; dispatcher-supplied source ignored, no length. Call operation_init then zero ALL100
// bytes. Consume24 DWORDs /96 bytes in runtime offset order [8,12,16,20,24,28,32,36,40,44,48,52,0,60,64,68,72,4,76,80,84,88,92,96], with native FLD/FSTP for float fields. Flags
// runtime56 are absent on wire and forced exactly1, overwriting no incoming flags. Arm timer7B25EC8000ms, operation_begin(local100), then repeatedly operation_step ONLY while
// unsigned AL==1 (MOVZX then CMP1), not arbitrary nonzero. No iteration budget, presentation rollback, runtime/server guard, length/cutter validation here. After loop call
// network_poll_udp_into_receive_queues ONCE and return its EAX; this polls input without invoking dispatcher recursively. This synchronous pregame replay differs from live41
// impact+queued execution.
int __cdecl rf_geomod_apply_pregame_boolean_payload17(int a1)
{
  _DWORD v2[27]; // [esp+0h] [ebp-70h] BYREF
  int v3; // [esp+6Ch] [ebp-4h]

  v3 = 0;
  rf_geomod_operation_init((char *)v2);
  memset(v2, 0, 0x64u);
  v2[2] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[3] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[4] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[5] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[6] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[7] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[8] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[9] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[10] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[11] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[12] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[13] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[0] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[15] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[16] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[17] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[18] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[1] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[19] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[20] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[21] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[22] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[23] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[24] = *(_DWORD *)(v3 + a1);
  v3 += 4;
  v2[14] = 1;
  rf_replication_timer7B25EC_arm_8s();
  rf_geomod_operation_begin((int)v2);
  while ( rf_geomod_operation_step() )
    ;
  return rf_network_poll_udp_into_receive_queues();
}

