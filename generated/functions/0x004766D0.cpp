// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004766D0 rf_cutscene_activate_completion_events
// UNREALRED VERIFIED [cutscene-playback-20261028]: Scans mission-event registry0x90B0E0; for each event with subtype E+656==83 (When_Cutscene_Over), calls rf_mission_event_activate(E,-1,-1,1). Does not restrict to links of the just-finished cutscene. Registry count reread every iteration; returns final count, not number activated.
int rf_cutscene_activate_completion_events()
{
  int result; // eax
  int **v1; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(unk_90B0E0);
    if ( i >= result )
      break;
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(unk_90B0E0, i) + 656) == 83 )
    {
      v1 = (int **)sub_552200(unk_90B0E0, i);
      rf_mission_event_activate(*v1, -1, -1, 1);
    }
  }
  return result;
}

