// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AE510 rf_splitscreen_reset_input_and_apply_weapon_profile
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, packet14/27 registry bindings, rate-width/clamp policy, native string ABI and pregame17/18 wire layout): Noarg
// sequence: mouse centering permission1; request centering; reset all keyboard/event input; mouse buttons/motion reset TWICE (two actual calls58A950); invoke448BA0 with forceBYTE0
// conditional-unpause; finally5086D0 apply multiplayer weapon runtime values and return its EAX. No mode/split/authority gate in this body, level/player allocation or inferred
// profile selection from split byte alone. Pause lock byte can keep game paused through helper despite later weapon-profile call; input resets precede unpause attempt.
int rf_splitscreen_reset_input_and_apply_weapon_profile()
{
  rf_mouse_set_centering_permission_byte(1);
  rf_mouse_enable_centering_request();
  rf_input_reset_all_key_and_event_state();
  rf_mouse_reset_buttons_and_motion();
  rf_mouse_reset_buttons_and_motion();
  rf_game_unpause_unless_locked(0);
  return rf_weapon_apply_multiplayer_runtime_values();
}

