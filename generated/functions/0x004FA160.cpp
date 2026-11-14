// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FA160 rf_event_play_animation_create_resolved
// UNREALRED VERIFIED [mission-event-play-animation]: Creates event type 11 and stores the resolved body state/action index, action selector, and authored hold byte.
int __cdecl rf_event_play_animation_create_resolved(float *a1, int a2, char a3, char a4)
{
  int v5; // [esp+0h] [ebp-4h]

  if ( a2 == -1 )
    return 0;
  v5 = rf_mission_event_create_at_position(a1, 0xBu);
  if ( v5 )
  {
    *(_DWORD *)(v5 + 696) = a2;
    *(_BYTE *)(v5 + 700) = a4;
    *(_BYTE *)(v5 + 701) = a3;
  }
  return v5;
}

