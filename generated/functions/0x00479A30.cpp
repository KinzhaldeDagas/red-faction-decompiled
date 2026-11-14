// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00479A30 rf_liquid_room_level_update
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Cdecl no arguments. Walks global transition vector6FC46C with signed index and dynamic count. Record24 bytes: room pointer0,start FLOAT4,current FLOAT8,target FLOAT12,duration
// FLOAT16,elapsed FLOAT20. Adds global frame delta to elapsed and stores binary32. If duration>=elapsed OR comparison unordered, stores (target-start)*elapsed/duration+start as
// binary32 current; only ORDERED duration<elapsed copies target and marks complete. Equality still interpolates and retains record. No zero-duration, finite-value or pause guard;
// zero/zero or NaN may propagate and persist.
// Writes current into room FLOAT392 and rebuilds liquid surface using world solid every visited record. On completion raw-deletes record BEFORE removing first matching pointer from
// vector. Remove helper shifts all later pointers left, but updater unconditionally increments index: immediate successor is skipped until next frame. Retests current count each
// loop; normal final EAX is current count. No per-room enable-byte update.
int rf_liquid_room_level_update()
{
  int result; // eax
  char v1; // [esp+7h] [ebp-9h]
  float *v2; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(unk_6FC46C);
    if ( i >= result )
      break;
    v1 = 0;
    v2 = *(float **)sub_552200(unk_6FC46C, i);
    v2[5] = v2[5] + rf_frame_delta_seconds;
    if ( v2[4] >= (double)v2[5] )
    {
      v2[2] = (v2[3] - v2[1]) * v2[5] / v2[4] + v2[1];
    }
    else
    {
      v1 = 1;
      v2[2] = v2[3];
    }
    *(float *)(*(_DWORD *)v2 + 392) = v2[2];
    rf_liquid_room_surface_rebuild(*(_DWORD *)v2, rf_world_solid);
    if ( v1 )
    {
      operator delete(v2);
      rf_pointer_array_remove_first(unk_6FC46C, (int)v2);
    }
  }
  return result;
}

