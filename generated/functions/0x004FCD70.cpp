// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FCD70 rf_mission_event_apply_generic_reverse
// UNREALRED VERIFIED [mission-mover-activation-20261013] All event kinds currently admitted by UnrealRed use this base reverse handler with event IDs outside its distinct-operation cases. Their local reverse operation is a no-op: do not run the forward Message, Switch, countdown, animation, AI or light handler when reached from Switch-off. Forwarding policy remains a separate subsequent decision at0x4FB3C0.
// UNREALRED VERIFIED [mission-mover-events-20261020] Reverse_Mover(type89) and Modify_Rotating_Mover(type66) retain this no-op base reverse handler and suppress generic forwarding. Mover_Pause(type72) instead overrides its reverse vtable slot with0x5015F0; it must not be treated as a base no-op.
// UNREALRED VERIFIED [mission-invert-20261020] Type3 exception to earlier currently-admitted no-op note: Invert REVERSE input invokes0x4FD240 to enable its targets. Forwarding remains suppressed by0x4FB3C0, so each target is dispatched exactly once per authored occurrence.
_DWORD *__thiscall rf_mission_event_apply_generic_reverse(_DWORD *this)
{
  _DWORD *result; // eax

  switch ( *(this + 164) )
  {
    case 3:
      result = (_DWORD *)rf_event_invert_apply_reverse((int)this);
      break;
    case 8:
      result = (_DWORD *)rf_event_shoot_at_apply_reverse((int)this);
      break;
    case 0x27:
      result = (_DWORD *)rf_event_particle_state_apply_reverse((int)this);
      break;
    case 0x2B:
      result = (_DWORD *)rf_event_bolt_state_apply_reverse((int)this);
      break;
    case 0x33:
      result = (_DWORD *)rf_event_push_region_state_apply_reverse((int)this);
      break;
    case 0x35:
      result = (_DWORD *)rf_event_headlamp_state_apply_reverse((int)this);
      break;
    case 0x36:
      result = (_DWORD *)rf_event_item_pickup_state_apply_reverse((int)this);
      break;
    case 0x3E:
      result = (_DWORD *)rf_event_turn_off_physics_apply_reverse((int)this);
      break;
    case 0x43:
      result = (_DWORD *)rf_event_clear_endgame_if_killed_apply_reverse((int)this);
      break;
    case 0x4C:
      result = (_DWORD *)rf_event_activate_capek_shield_apply_reverse((int)this);
      break;
    case 0x50:
      result = (_DWORD *)rf_event_never_leave_vehicle_apply_reverse((int)this);
      break;
    default:
      result = this;
      break;
  }
  return result;
}

