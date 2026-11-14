// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A8390 rf_multiplayer_publish_weapon_fire
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): cdecl(entity,position,matrix,weapon,mode LOW BYTE). Only runtime==EXACT1 AND authority==EXACT1: find player owning entity handle44; if found arm
// PLAYER+192 game-clock deadline with offset0. Routing thereafter uses authority ANY nonzero: non-client paths call packet48 sender4A7800. Client runtime1/authority0 only publishes
// when entity==local entity681E38; before sending, dereferences motion buffer+632 and writes count2300 from4B5420(byte-array2200,WORD-array2232). Other client entities do not
// publish, preventing ordinary receive->relay there. Helper4B5420 caps returned count but not writes. No own pointer/weapon validation or transport-result normalization.
_DWORD *__cdecl rf_multiplayer_publish_weapon_fire(_DWORD *a1, float *a2, float *a3, int a4, char a5)
{
  _DWORD *result; // eax
  _DWORD *v6; // [esp+0h] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    v6 = sub_4DD720(a1[11]);
    if ( v6 )
      rf_replicator_arm_milliseconds(v6 + 48, 0);
  }
  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority )
    return rf_multiplayer_queue_weapon_fire_packet48((int)a1, a2, a3, a4, a5);
  result = a1;
  if ( a1 == (_DWORD *)dword_681E38 )
  {
    *(_DWORD *)(a1[158] + 2300) = rf_replication_collect_all_remote_sample_ids(a1[158] + 2200, a1[158] + 2232);
    return rf_multiplayer_queue_weapon_fire_packet48((int)a1, a2, a3, a4, a5);
  }
  return result;
}

