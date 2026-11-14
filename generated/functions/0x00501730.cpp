// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501730 rf_event_blackout_player_reverse
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_blackout_player reverse, vtable0x63E3D4 slot+8. Require global entity present. Set local player float+0x11D4 to exact float literal at0x63E44C (~249.9). Finite event duration+0x2BC<=0 is mutated to6.0f; copy duration to player+0x11D8 and OR player flags+0x10 bit0x100. Does not directly clear forward bits0x80/0x200/0x1000 or change callback field in this body.
int __thiscall rf_event_blackout_player_reverse(float *this)
{
  int result; // eax

  if ( dword_681E38 )
  {
    *(float *)(rf_local_fpgun_player + 4564) = 249.89999;
    if ( *(this + 175) <= 0.0 )
      *(this + 175) = 6.0;
    *(float *)(rf_local_fpgun_player + 4568) = *(this + 175);
    result = *(_DWORD *)(rf_local_fpgun_player + 16) | 0x100;
    *(_DWORD *)(rf_local_fpgun_player + 16) = result;
  }
  return result;
}

