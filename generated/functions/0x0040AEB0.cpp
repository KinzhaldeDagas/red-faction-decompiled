// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040AEB0 sub_40AEB0
// UNREALRED VERIFIED [combat-transition-alarm-20261029] Combat diversion checks owner float+0x8C0>0, shared alarm inactive, AI+0x4CC UID resolves event type46, and current owner resolves. It rejects when another noninactive living entity with same alarm UID is already numeric mode16. Successful route to event+0x40 invokes4355A0, stores destination, writes mode16/secondary1 and clears AI+0x530 bit0x200000. This diversion precedes weapon admission in40B2D0; missing alarm-route ownership cannot be treated as recovered generic combat entry.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Gate order for recovery40B2D0: read actual current Entity+8C0 speed; if <=0 returnsfalse. Otherwise querysharedalarmactive; true returnsfalse BEFORE inspecting AI+4CC event UID. Then resolve stored event UID/type46 and owner, peer admission, exact route request. Missing sharedalarm provider cannot be replaced by checking UID-1 early; known early rejects have distinct complete native no-op meaning.
char __cdecl sub_40AEB0(_DWORD *a1)
{
  float copy_result[3]; // [esp+0h] [ebp-1Ch] BYREF
  int v3; // [esp+Ch] [ebp-10h]
  int v4; // [esp+10h] [ebp-Ch]
  int i; // [esp+14h] [ebp-8h]
  int v6; // [esp+18h] [ebp-4h]

  if ( *(float *)(*a1 + 2240) <= 0.0 )
    return 0;
  if ( rf_alarm_get_shared_active() == 1 )
    return 0;
  v3 = rf_mission_event_find_by_uid(a1[307]);
  if ( !v3 )
    return 0;
  if ( *(_DWORD *)(v3 + 656) != 46 )
    return 0;
  v6 = v3;
  v4 = rf_entity_resolve_handle(*(_DWORD *)(*a1 + 44));
  if ( !v4 )
    return 0;
  for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( !rf_object_has_respawn_inactive_flag(i)
      && *(_DWORD *)(i + 44) != *(_DWORD *)(*a1 + 44)
      && !rf_entity_is_dead(i)
      && *(_DWORD *)(i + 1900) == a1[307]
      && *(_DWORD *)(i + 1312) == 16 )
    {
      return 0;
    }
  }
  if ( !rf_ai_route_build(*(_DWORD *)(v4 + 44), v3 + 64) )
    return 0;
  sub_4355A0(v4);
  rf_vector_copy((float *)(v4 + 1772), copy_result, (const float *)(v3 + 64));
  rf_ai_numeric_mode_write(a1, 16, -1, -1);
  rf_ai_secondary_state_write((int)a1, 1);
  a1[332] &= ~0x200000u;
  return 1;
}

