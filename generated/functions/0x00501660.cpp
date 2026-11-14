// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501660 rf_event_blackout_player_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_blackout_player forward, vtable0x63E3D4 slot+4. Require global entity0x681E38 non-null, then operate on rf_local_fpgun_player. Finite duration event+0x2BC<=0 is overwritten in event with1.5f. Call0x4E25F0(player,duration,empty callback0x501720); OR player+0x10 bit0x80, optionally bit0x200 for nonzero byte+0x2B8 and0x1000 for nonzero byte+0x2B9. Does not clear previously set optional bits when bytes false.
int __thiscall rf_event_blackout_player_forward(int this)
{
  int result; // eax

  if ( dword_681E38 )
  {
    if ( *(float *)(this + 700) <= 0.0 )
      *(float *)(this + 700) = 1.5;
    rf_player_begin_blackout_transition(
      rf_local_fpgun_player,
      *(float *)(this + 700),
      (int)rf_event_blackout_completion_noop);
    *(_DWORD *)(rf_local_fpgun_player + 16) |= 0x80u;
    if ( *(_BYTE *)(this + 696) )
      *(_DWORD *)(rf_local_fpgun_player + 16) |= 0x200u;
    result = this;
    if ( *(_BYTE *)(this + 697) )
    {
      result = *(_DWORD *)(rf_local_fpgun_player + 16) | 0x1000;
      *(_DWORD *)(rf_local_fpgun_player + 16) = result;
    }
  }
  return result;
}

