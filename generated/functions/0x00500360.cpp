// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500360 rf_event_switch_toggle_apply_forward
// UNREALRED VERIFIED [world-uid-ownership]: Switch type 32 forward handler: toggles the event's own binary state, enforces its authored terminal modes, then applies the resulting state to targets.
int __thiscall rf_event_switch_toggle_apply_forward(int this)
{
  int result; // eax

  if ( *(_BYTE *)(this + 712) || (result = this, *(_DWORD *)(this + 716) < *(_DWORD *)(this + 700)) )
  {
    if ( *(_DWORD *)(this + 696) )
      *(_DWORD *)(this + 696) = 0;
    else
      *(_DWORD *)(this + 696) = 1;
    if ( *(_DWORD *)(this + 724) == 1 && *(_DWORD *)(this + 696) == 1 )
    {
      *(_DWORD *)(this + 696) = 0;
      return rf_gamesound_play_event(2, 0, 0.0, 1.0);
    }
    else if ( *(_DWORD *)(this + 724) != 2 || *(_DWORD *)(this + 696) )
    {
      rf_event_switch_apply_targets((int *)this, 0);
      rf_gamesound_play_positional_event(*(_DWORD *)(this + 720), (float *)(this + 64), 1.0, (int)flt_17F10B0, 0);
      result = *(_DWORD *)(this + 716) + 1;
      *(_DWORD *)(this + 716) = result;
    }
    else
    {
      *(_DWORD *)(this + 696) = 1;
      return rf_gamesound_play_event(2, 0, 0.0, 1.0);
    }
  }
  return result;
}

