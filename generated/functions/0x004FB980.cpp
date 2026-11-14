// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB980 rf_mission_event_apply_generic_forward
// UNREALRED VERIFIED [mission-invert-20261020] Type3 routes to0x4FC530, the Invert disabling handler. This is separate from generic forward propagation and invokes mover stopping with suppression=0.
void __thiscall rf_mission_event_apply_generic_forward(int *this)
{
  switch ( *(this + 164) )
  {
    case 2:
      rf_event_remove_object_apply((int)this);
      break;
    case 3:
      rf_event_invert_apply_forward((int)this);
      break;
    case 4:
      rf_event_teleport_apply((int)this);
      break;
    case 8:
      rf_event_shoot_at_apply_forward((int)this);
      break;
    case 25:
      rf_event_make_walk_apply_forward((int)this);
      break;
    case 26:
      rf_event_make_fly_apply_forward((int)this);
      break;
    case 39:
      rf_event_particle_state_apply_forward((int)this);
      break;
    case 43:
      rf_event_bolt_state_apply_forward((int)this);
      break;
    case 51:
      rf_event_push_region_state_apply_forward((int)this);
      break;
    case 53:
      rf_event_headlamp_state_apply_forward((int)this);
      break;
    case 54:
      rf_event_item_pickup_state_apply_forward((int)this);
      break;
    case 55:
      rf_cutscene_begin_by_identifier(*(this + 9));
      break;
    case 56:
      rf_event_strip_player_weapons_apply();
      break;
    case 60:
      rf_event_force_monitor_update_apply((int)this);
      break;
    case 62:
      rf_event_turn_off_physics_apply_forward((int)this);
      break;
    case 63:
      rf_event_teleport_player_apply((int)this);
      break;
    case 64:
      rf_event_holster_weapon_apply((int)this);
      break;
    case 65:
      rf_event_holster_player_weapon_apply();
      break;
    case 67:
      rf_event_clear_endgame_if_killed_apply_forward((int)this);
      break;
    case 68:
      rf_event_win_ps2_demo_apply();
      break;
    case 74:
      rf_event_countdown_end_apply();
      break;
    case 76:
      rf_event_activate_capek_shield_apply_forward((int)this);
      break;
    case 79:
      rf_event_fire_weapon_no_anim_apply((int)this);
      break;
    case 80:
      rf_event_never_leave_vehicle_apply_forward((int)this);
      break;
    case 81:
      rf_event_drop_weapon_apply((int)this);
      break;
    case 82:
      rf_event_ignite_entity_apply((int)this);
      break;
    case 83:
      rf_event_when_cutscene_over_local_noop();
      break;
    case 86:
      rf_event_defuse_nuke_apply();
      break;
    default:
      return;
  }
}

