// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E25D0 rf_player_request_panel13_and_stop_voices
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): No arguments. Request UI panel13 with payload0, then stop all voice slots568650. No own entity/room/resource cleanup; native final EAX is delegated residue.
void rf_player_request_panel13_and_stop_voices()
{
  rf_ui_request_panel_immediate(13, 0);
  rf_gamesound_stop_all_voice_slots();
}

