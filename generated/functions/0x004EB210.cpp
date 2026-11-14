// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EB210 sub_4EB210
// UNREALRED VERIFIED [rocket-transport-20260930] Target scan excludes respawn-inactive records, dead entities, and records accepted by 0x4BCE50. The latter scans the global entry array: an entity is excluded if identical to an entry-resolved entity OR if that entity +0x200 equals candidate +0x2C. Thus a generic non-player label omits the second handle relationship. Candidate selection then uses the range, cone score, and either of two visibility rays. The entry-related attachment semantics are not established by this predicate alone; an Unreal target fixture without player/attachment ownership does not certify that second exclusion.
// UNREALRED VERIFIED [local-multiplayer-lock-20261028] The scan traverses all gameplay entities and rejects inactive/dead candidates plus predicate0x4BCE50; it has no blanket player-controlled or network-PlayerState exclusion. Fresh constructor0x4DD030 proves the predicate array0x87C5B0/count0x87C638 contains only local-flag players (maximum2), distinct from the all-player circular list0x87C324. Remote network players therefore remain eligible after ordinary range/cone/visibility checks. The separate resolved-entity+0x200 handle relationship remains preserved but its general gameplay name is not established.
float *__cdecl sub_4EB210(int a1)
{
  float *result; // eax
  float v2; // [esp+0h] [ebp-24h] BYREF
  float v3; // [esp+4h] [ebp-20h]
  int v4; // [esp+8h] [ebp-1Ch]
  float v5; // [esp+Ch] [ebp-18h]
  char v6[12]; // [esp+10h] [ebp-14h] BYREF
  float *v7; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]

  result = (float *)rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v7 = result;
  if ( result )
  {
    result = (float *)rf_vector3_default_construct_noop(v6);
    v4 = -1;
    v5 = 0.0;
    for ( i = dword_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
    {
      if ( !rf_object_has_respawn_inactive_flag(i)
        && !rf_entity_is_dead(i)
        && rf_entity_matches_local_player_or_related_handle(i) != 1 )
      {
        v3 = rf_vector_fast_distance(v7 + 501, (const float *)(i + 2004));
        if ( v3 < 100.0
          && rf_player_target_forward_cone_score(a1, i, &v2)
          && (!rf_geometry_segment_is_obstructed(v7 + 501, (float *)(i + 2004), 3, nullptr)
           || !rf_geometry_segment_is_obstructed(v7 + 501, (float *)(i + 60), 3, nullptr))
          && v5 <= (double)v2 )
        {
          v5 = v2;
          v4 = *(_DWORD *)(i + 44);
        }
      }
      result = (float *)i;
    }
    *(_DWORD *)(a1 + 4000) = v4;
  }
  return result;
}

