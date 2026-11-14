// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB470 rf_mission_event_update_delayed_and_special
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Precise update ordering: elapsed shared deadline+0x298 invokes stored direction byte+0x2B4 through forward vtable+4 or reverse+8; then evaluate common auto-forward policy and dispatch with stored context+0x2AC/+0x2A8 and raw direction. Reset deadline AFTER callback/forwarding, then run special updater for numeric type52/75/77/78. This body has no enabled-byte gate before either stage; special helpers have their own distinct admission. Callback writes to same embedded deadline can be overwritten by reset afterward.
void __thiscall rf_mission_event_update_delayed_and_special(char *this)
{
  if ( rf_replicator_has_elapsed((int *)this + 166) )
  {
    if ( *(this + 692) )
      (*(void (__thiscall **)(char *))(*(_DWORD *)this + 4))(this);
    else
      (*(void (__thiscall **)(char *))(*(_DWORD *)this + 8))(this);
    if ( rf_mission_event_auto_forward_after_handler(*((_DWORD *)this + 164)) == 1 )
      rf_mission_event_forward_targets((int)this, *((_DWORD *)this + 171), *((_DWORD *)this + 170), *(this + 692));
    rf_replicator_reset((_DWORD *)this + 166);
  }
  switch ( *((_DWORD *)this + 164) )
  {
    case '4':
      rf_event_when_hit_update((int)this);
      break;
    case 'K':
      rf_event_when_countdown_over_update((int)this);
      break;
    case 'M':
      rf_event_when_enter_vehicle_update((int)this);
      break;
    case 'N':
      rf_event_when_try_exit_vehicle_update((int)this);
      break;
    default:
      return;
  }
}

