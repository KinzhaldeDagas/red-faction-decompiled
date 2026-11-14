// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049E2E0 rf_multiplayer_hud_select_target_player
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): cdecl(output player-pointer slot); unconditionally writesNULL before any global gate. Requires localPlayer87C318 and local entity681E38
// nonnull. Walks circular player list87C324, using firstDWORD next and terminating when next==head; empty head0 skips. Resolves each player entity handle+20 and calls game-mode
// getter each iteration (return unused); skips missing entity and local player. Normalizes local entity vector+2040, vector(candidate position+60 - local+2004), and
// vector(candidate+2004 - local+2004). Stores forward dot candidate-position direction in binary32 score; squared entity-position distance threshold400 (20-unit radius). Native TEST
// AH,0x41/JNZ admits less/equal AND unordered distance; there is no separate finite check. Requires second dot(directionToPosition,directionToCandidate+2004)<score ordered strictly;
// best candidate must strictly improve prior stored score; ties retain first. Requires geometry_segment_is_obstructed(candidate+60,local+2004,1,0) AL0. On success writes PLAYER
// pointer, not entity. No team/death/health/state/positive-score guard or normalization zero-vector repair in own body; vector/geometry helpers own those. EAX incidental; output slot
// is result.
int *__cdecl rf_multiplayer_hud_select_target_player(int *a1)
{
  int *result; // eax
  int *v2; // [esp+0h] [ebp-40h]
  float v3[3]; // [esp+4h] [ebp-3Ch] BYREF
  float out_vector[3]; // [esp+10h] [ebp-30h] BYREF
  float v5; // [esp+1Ch] [ebp-24h]
  float v6[3]; // [esp+20h] [ebp-20h] BYREF
  float v7; // [esp+2Ch] [ebp-14h]
  int v8; // [esp+30h] [ebp-10h]
  int v9; // [esp+34h] [ebp-Ch]
  int i; // [esp+38h] [ebp-8h]
  float v11; // [esp+3Ch] [ebp-4h]

  result = a1;
  *a1 = 0;
  if ( rf_local_fpgun_player && dword_681E38 )
  {
    v9 = 0;
    for ( i = dword_87C324; i; i = (int)v2 )
    {
      v8 = rf_entity_resolve_handle(*(_DWORD *)(i + 20));
      rf_multiplayer_game_mode_get();
      if ( v8 )
      {
        if ( i != rf_local_fpgun_player )
        {
          rf_vector3_copy_return_destination(v6, (float *)(dword_681E38 + 2040));
          rf_vector_subtract((const float *)(v8 + 60), out_vector, (const float *)(dword_681E38 + 2004));
          rf_vector_subtract((const float *)(v8 + 2004), v3, (const float *)(dword_681E38 + 2004));
          rf_vector_normalize_reciprocal_sqrt(v6);
          rf_vector_normalize_reciprocal_sqrt(out_vector);
          rf_vector_normalize_reciprocal_sqrt(v3);
          v7 = rf_vector_dot(v6, out_vector);
          if ( rf_vector_distance_squared((const float *)(v8 + 60), (const float *)(dword_681E38 + 60)) <= 400.0 )
          {
            v5 = rf_vector_dot(out_vector, v3);
            if ( v5 < (double)v7
              && (!v9 || v11 < (double)v7)
              && !rf_geometry_segment_is_obstructed(v8 + 60, dword_681E38 + 2004, 1, 0) )
            {
              v9 = i;
              v11 = v7;
            }
          }
        }
      }
      if ( *(_DWORD *)i == dword_87C324 )
        v2 = nullptr;
      else
        v2 = *(int **)i;
      result = v2;
    }
    if ( v9 )
    {
      *a1 = v9;
      return a1;
    }
  }
  return result;
}

