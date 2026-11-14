// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453D00 rf_extras_menu_play_summoner_trailer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Call568A00 with raw caller words(1,-1), pop8; call58E020("sumtrailer.bik"), pop4;
// then568A00(0,-1), pop8 and forward finalEAX. Sound pause wrapper consumes its own byte argument; extraDWORD-1 is caller-owned/ignored by that body. Movie/backend result is not
// tested; resume attempt always follows normal movie return. No own readiness/file/window, panel, active-state or input gate, asynchronous launch or rollback.
int rf_extras_menu_play_summoner_trailer()
{
  rf_sound_backend_set_paused(1);
  rf_movie_play_bink_blocking("sumtrailer.bik");
  return rf_sound_backend_set_paused(0);
}

