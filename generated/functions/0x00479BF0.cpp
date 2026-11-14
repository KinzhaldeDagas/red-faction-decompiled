// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00479BF0 rf_liquid_room_set_depth_by_id
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Cdecl(room id,target FLOAT,duration FLOAT), normalized AL Boolean. Exact-1 or missing first matching room DWORD36 in world vector+156 returns0. Computes binary32
// cap=maxY24-minY12-double0.10000000149011612. Ordered target<0 becomes0 and bypasses upper test; otherwise only ordered cap<target replaces target with cap. Unordered comparisons
// keep target. Thus NaN target survives, and a negative cap may produce negative final depth for nonnegative input; no second lower clamp. Forwards room,target,duration to
// transition_start and returns1. No duration validation or immediate room depth/surface change.
char __cdecl rf_liquid_room_set_depth_by_id(int a1, float a2, float a3)
{
  int v4; // [esp+8h] [ebp-10h]
  float v5; // [esp+Ch] [ebp-Ch]
  int i; // [esp+10h] [ebp-8h]
  int v7; // [esp+14h] [ebp-4h]

  if ( a1 == -1 )
    return 0;
  v7 = 0;
  for ( i = 0; i < rf_receiver_get_first_dword((void *)(rf_world_solid + 156)); ++i )
  {
    v4 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 156), i);
    if ( *(_DWORD *)(v4 + 36) == a1 )
    {
      v7 = v4;
      break;
    }
  }
  if ( !v7 )
    return 0;
  if ( a2 >= 0.0 )
  {
    v5 = *(float *)(v7 + 24) - *(float *)(v7 + 12) - 0.1000000014901161;
    if ( v5 < (double)a2 )
      a2 = *(float *)(v7 + 24) - *(float *)(v7 + 12) - 0.1000000014901161;
  }
  else
  {
    a2 = 0.0;
  }
  rf_liquid_room_level_transition_start(v7, a2, a3);
  return 1;
}

