// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BCDD0 rf_sound_event_play_for_object_view
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Cdecl(object,positionX,positionY,positionZ,eventID,floatA,floatB), seven DWORD stack slots; XYZ passed BY VALUE, positional address points into caller stack. If type0/player-pointer predicate4BD1F0 is false OR its player+196 view-wrapper DWORD8 is nonzero, calls positional sound(event,&XYZ,volume1,shared17F10B0,flags0), ignoring floatA/B. Otherwise calls game event(event,0,floatB,floatA). Returns PLAY FUNCTION EAX, unlike sound-list helper4BCD20 which returns selected asset ID after ignoring playback result. No null-object/player/view/event/position validation or randomized selection.
int __cdecl rf_sound_event_play_for_object_view(int a1, float a2, int a3, int a4, int a5, float a6, float a7)
{
  if ( !rf_entity_has_player_pointer_if_type0(a1)
    || rf_view_wrapper_get_dword8(*(_DWORD *)(*(_DWORD *)(a1 + 5168) + 196)) )
  {
    return rf_gamesound_play_positional_event(a5, &a2, 1.0, (int)flt_17F10B0, 0);
  }
  else
  {
    return rf_gamesound_play_event(a5, 0, a7, a6);
  }
}

