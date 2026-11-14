// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00406130 sub_406130
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Mode10 lazy order:402840/no681E38→saved restore; resolve optional player vehicle else originalplayer; ifAI2DC elapsed arm500 BEFORE friendliness401180, facing4024E0 and radiusFILTER1.3/publicmask3 object/world trace. Friendly+facing+clear OR nonfriendly distanceSquared<4 resetsroute+savedrestore. Else secondary!=1 andAI230elapsed calls434150 to current globalplayerCOMMON+3C; native failure-1→Arm1000+route reset, success0→secondary1 AGAIN. Secondary1 calls40ECE0. Host unavailable is not native failed admission.
void __cdecl sub_406130(int *a1)
{
  int v1; // [esp+14h] [ebp-4h]

  if ( rf_ai_no_local_player_object_available() || !dword_681E38 )
  {
    sub_40A2A0(a1);
    return;
  }
  v1 = dword_681E38;
  if ( rf_entity_has_attached_use_vehicle(dword_681E38) )
  {
    v1 = rf_entity_resolve_handle(*(_DWORD *)(dword_681E38 + 512));
    if ( !v1 )
      v1 = dword_681E38;
  }
  if ( rf_replicator_has_elapsed(a1 + 183) )
  {
    rf_replicator_arm_milliseconds(a1 + 183, 500);
    if ( sub_401180(*a1, dword_681E38) == 1 )
    {
      if ( sub_4024E0(*a1, v1)
        && !rf_segment_objects_or_world_hit_filtered_by_radius(*a1 + 2004, v1 + 2004, 1.3, 3, *a1, v1, 0) )
      {
        goto LABEL_11;
      }
    }
    else if ( rf_vector_distance_squared((const float *)(*a1 + 60), (const float *)(v1 + 60)) < 4.0 )
    {
LABEL_11:
      rf_ai_route_reset((int)(a1 + 186));
      sub_40A2A0(a1);
      return;
    }
  }
  if ( a1[173] != 1 && rf_replicator_has_elapsed(a1 + 140) )
  {
    if ( rf_ai_scripted_route_admit(*(_DWORD *)(*a1 + 44), dword_681E38 + 60) )
    {
      rf_replicator_arm_milliseconds(a1 + 140, 1000);
      rf_ai_route_reset((int)(a1 + 186));
    }
    else
    {
      rf_ai_secondary_state_write((int)a1, 1);
    }
  }
  if ( a1[173] == 1 )
    rf_ai_route_update((int)(a1 + 186));
}

