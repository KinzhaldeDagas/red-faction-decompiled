// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A4BD0 rf_multiplayer_apply_end_game_callback8
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original55-entry packet registry and dispatcher bounds, departure/limbo ordering, native string ABI, flag-node cleanup and netgame-update versus ping/pong identities): 
// Recovered [4A4BD0,4A4C2A), consumes no arguments; registry8 supplies unused payload/source. Unconditionally calls runtime_teardown(),requests panel13 forced1,then
// modal(title88E1F0,text88E1F4,0,0). No own runtime/authority/source admission or payload validation. Order differs from local left_game modal-before-teardown. Modal refusal does not
// undo teardown/panel request.
void __cdecl rf_multiplayer_apply_end_game_callback8()
{
  rf_multiplayer_runtime_teardown();
  rf_ui_request_panel_immediate(13, 1);
  rf_ui_show_ok_modal((const char *)dword_88E1F0, (char *)dword_88E1F4, nullptr, 0);
}

