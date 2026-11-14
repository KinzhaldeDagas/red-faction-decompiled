// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045CE20 rf_multiplayer_setup_latch_server_name_edit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Store BYTE6F2D01=1 only;no input read,string change,registry write,focus change or network call. EAX
// unspecified. Server-name edit callback assigned during setup construction;shared edit latch is later cleared by focus/pointer/render paths.
void rf_multiplayer_setup_latch_server_name_edit()
{
  unk_6F2D01 = 1;
}

