// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DA20 rf_multiplayer_setup_game_mode_index_get
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Return raw DWORD6F35C4 from mode chooser asEAX. No runtime validation,normalization,0..2 bound,registry
// read,control update or network game-mode query. Distinct from multiplayer-runtime game-mode getter492030.
int rf_multiplayer_setup_game_mode_index_get()
{
  return unk_6F35C4;
}

