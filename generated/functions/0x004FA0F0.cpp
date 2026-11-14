// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA0F0 rf_event_play_animation_build_from_name
// UNREALRED VERIFIED [mission-play-animation-20261013] Exact case-insensitive token lookup visits23 canonical body states first, then45 canonical actions. No filename inference or whitespace trim. The hold argument is retained independently; state resolution does not fall back to an entity action when that entity lacks the resolved state slot.
int __cdecl rf_event_play_animation_build_from_name(int a1, std::exception *a2, char a3)
{
  char *v3; // eax
  char *v5; // eax
  int canonical_index; // [esp+0h] [ebp-8h]
  int v7; // [esp+0h] [ebp-8h]

  v3 = (char *)rf_string_object_c_str_or_empty(a2);
  canonical_index = rf_body_state_find_canonical_index(v3);
  if ( canonical_index != -1 )
    return rf_event_play_animation_create_resolved(a1, canonical_index, a3, 0);
  v5 = (char *)rf_string_object_c_str_or_empty(a2);
  v7 = rf_body_action_find_canonical_index(v5);
  return rf_event_play_animation_create_resolved(a1, v7, a3, v7 != -1);
}

