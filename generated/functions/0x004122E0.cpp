// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004122E0 rf_camera_slot_enter_orbit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(slot pointer), canonicalAL0/1. Resolves shared full COMMON-object handle87C31C. Missing object emits exact RF string "Orbit
// camera requries a target" through44B4B0 with three zero args, returnsAL0 and leaves slot state/global closest point untouched. Success builds contiguous line6 from selected global
// player87C318->DWORD+196->DWORD0 camera position+60 and camera vector+2040 (start then direction); projects target COMMON position+60 onto that line using56CAD0 and writes all3
// closest-point FLOATs to shared666AC4. Discards ST0 projection distance, sets supplied slot state+8=7, returnsAL1. Selected camera need not belong to supplied slot. No
// global-player/camera pointer guards, unit-direction validation, segment clamp or target entity-type requirement.
char __cdecl rf_camera_slot_enter_orbit(int a1)
{
  float v2[3]; // [esp+0h] [ebp-34h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-28h] BYREF
  float v4[3]; // [esp+18h] [ebp-1Ch] BYREF
  float destination[3]; // [esp+24h] [ebp-10h] BYREF
  int v6; // [esp+30h] [ebp-4h]

  v6 = rf_object_resolve_handle(dword_87C31C);
  if ( v6 )
  {
    rf_force_sample44_construct_vectors_noop((char *)v4);
    rf_vector_copy(destination, copy_result, (const float *)(**(_DWORD **)(rf_local_fpgun_player + 196) + 2040));
    rf_vector_copy(v4, v2, (const float *)(**(_DWORD **)(rf_local_fpgun_player + 196) + 60));
    rf_point_project_onto_unit_direction_line(v6 + 60, (int)v4, &flt_666AC4);
    *(_DWORD *)(a1 + 8) = 7;
    return 1;
  }
  else
  {
    rf_hud_message_enqueue_expand_tokens_and_rearm_head("Orbit camera requries a target", 0, 0, nullptr);
    return 0;
  }
}

