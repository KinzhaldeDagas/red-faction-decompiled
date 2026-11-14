// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004478C0 rf_ui_reset_keyboard_and_mouse_input
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Calls58B6C0 to reset all keyboard/key-event state, then58A950 to reset mouse button/motion state. Adds no
// conditional guard or own state writes and forwards the final helper's incidental EAX; not an event-poll or cursor-centering operation.
void rf_ui_reset_keyboard_and_mouse_input()
{
  rf_input_reset_all_key_and_event_state();
  rf_mouse_reset_buttons_and_motion();
}

