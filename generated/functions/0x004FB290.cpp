// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB290 rf_mission_event_activate
// UNREALRED VERIFIED [mission-when-dead-20261013] Explicit type16 When_Dead activation uses the ordinary local no-op handler plus generic auto-forward policy. It does not test object liveness or set the monitor fired byte; repeated explicit activation can forward even after the autonomous monitor latched. Its ordinary authored delay arms the replicator, which temporarily gates the autonomous update.
// UNREALRED VERIFIED [mission-invert-20261020] Invert retains ordinary authored-delay behavior on entry, in either direction. The local opposite-direction routing only runs after the deadline; type3 completion suppresses additional generic propagation. Nested Invert targets may independently rearm their own delays.
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] Raw-direction detail: always store context arguments at event+0x2AC/+0x2A8 BEFORE disabled mask1 test. Nonpositive authored delay resets pending deadline; immediate direction is forward ONLY when input byte==1, else reverse. Positive delay stores raw direction byte; delayed updater0x4FB470 later treats any nonzero as forward. Type79 Fire_Weapon_No_Anim delay specifically uses trunc(delay/float1.017579913139343*1000+0.5); other types use trunc(delay*1000+0.5). Single embedded deadline means later accepted delayed activation replaces pending direction/context.
int __thiscall rf_mission_event_activate(int *this, int a2, int a3, char a4)
{
  int result; // eax

  *(this + 170) = a3;
  result = a2;
  *(this + 171) = a2;
  if ( (*(this + 172) & 1) == 0 )
  {
    if ( *((float *)this + 165) <= 0.0 )
    {
      rf_replicator_reset(this + 166);
      if ( a4 == 1 )
        (*(void (__thiscall **)(int *))(*this + 4))(this);
      else
        (*(void (__thiscall **)(int *))(*this + 8))(this);
      result = (unsigned __int8)rf_mission_event_auto_forward_after_handler(*(this + 164));
      if ( (unsigned __int8)result == 1 )
        return rf_mission_event_forward_targets((int)this, a2, *(this + 170), a4);
    }
    else
    {
      if ( *(this + 164) == 79 )
        result = rf_replicator_arm_milliseconds(
                   this + 166,
                   (int)(*((float *)this + 165) / 1.017579913139343 * 1000.0 + 0.5));
      else
        result = rf_replicator_arm_milliseconds(this + 166, (int)(*((float *)this + 165) * 1000.0 + 0.5));
      *((_BYTE *)this + 692) = a4;
    }
  }
  return result;
}

