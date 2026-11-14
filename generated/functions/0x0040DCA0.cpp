// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040DCA0 sub_40DCA0
// UNREALRED VERIFIED [ai-health-goals-20261028] Resolves entityhandle, validates selected waypoint-list index against0x487360 count, requires positive pointcount, validates current pointcursor, resolves stored index through0x552200, then submits route query0x518BE0. Rejects absentpoint or resulting route count<2. This validates movement to authored waypoint data; it does not resolve health pickup availability or grant health.
char __cdecl sub_40DCA0(int a1)
{
  float copy_result[3]; // [esp+0h] [ebp-1Ch] BYREF
  int v3; // [esp+Ch] [ebp-10h]
  float *v4; // [esp+10h] [ebp-Ch]
  float *v5; // [esp+14h] [ebp-8h]
  _DWORD *v6; // [esp+18h] [ebp-4h]

  v5 = (float *)rf_entity_resolve_handle(a1);
  if ( !v5 )
    return 0;
  v4 = v5 + 354;
  v6 = nullptr;
  if ( *((int *)v5 + 426) >= 0 && *((_DWORD *)v4 + 72) < rf_waypoint_list_count_get() )
    v6 = &unk_700480[131 * *((_DWORD *)v4 + 72)];
  if ( !v6 || (int)v6[2] <= 0 )
    return 0;
  unk_666408 = 0;
  if ( *((int *)v4 + 73) >= 0 && *((_DWORD *)v4 + 73) < v6[2] )
  {
    v3 = v6[*((_DWORD *)v4 + 73) + 3];
    unk_666408 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 768), v3);
  }
  if ( !unk_666408 )
    return 0;
  rf_ai_publish_owner_route_search_request(v5);
  unk_66641E = 0;
  if ( !rf_nav_graph_find_path_to_request_target((void *)(rf_world_solid + 768), &dword_6663FC) )
    return 0;
  *(_DWORD *)v4 = unk_666430;
  if ( *(int *)v4 < 2 )
    return 0;
  v4[5] = 0.0;
  *((_DWORD *)v4 + 6) = 1;
  rf_replicator_arm_milliseconds((int *)v4 + 77, 0);
  rf_vector_copy(v4 + 83, copy_result, v5 + 501);
  return 1;
}

