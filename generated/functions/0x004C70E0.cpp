// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C70E0 rf_glass_face_break_directional
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, persistent shard pool and keyed buckets, launch-delay/damage cadence, first-hit face traversal, native ordered branches and settling ownership): 
// Cdecl(face,impactPosition,direction,lowBYTEforce). Suppressed only multiplayer BYTE==1 AND authorityBYTE0 AND forceBYTE0. Nonzero authority admits; successful validate_register
// required. Plays Glass Smash then dispatch(face,position,direction) without copying/normalizing direction. Registry/sound survive room-resolution failure downstream.
// Broadcast494F20(face.owner68->DWORD36,position,direction,0) only multiplayer==1 AND authority==1 EXACT AND owner nonnull; authority2 admits local action but no broadcast.
// AL return NOT handled/success bool: suppressed mode1 route retainsAL1, successful mode0 route reloads/returns0, registry failure0, broadcast returns delegate lowBYTE. No separate
// material/corner/direction validation or rollback; nondirectional counterpart uses NULLdirection locally and broadcast final1/listener vector instead.
char __cdecl rf_glass_face_break_directional(_DWORD *a1, float *a2, float *a3, char a4)
{
  char result; // al

  result = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode != 1 || rf_multiplayer_server_authority || a4 )
  {
    result = rf_glass_face_validate_and_register(a1);
    if ( result )
    {
      rf_glass_smash_sound_play(a2);
      rf_glass_face_shatter_dispatch((int)a1, (int)a2, (int)a3);
      result = rf_multiplayer_runtime_mode;
      if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
      {
        if ( a1[17] )
          return rf_server_send_glass_break_packet54(*(_DWORD *)(a1[17] + 36), a2, a3, 0);
      }
    }
  }
  return result;
}

