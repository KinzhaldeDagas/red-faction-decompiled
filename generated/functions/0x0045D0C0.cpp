// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045D0C0 rf_multiplayer_setup_latch_password_edit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Store shared editLatchBYTE6F2D01=1 only;no string edit,checked/enabled-byte mutation,credential read,registry
// persistence or sound. EAX unspecified. Installed as password edit control callback by45BCD0;not a password validation function.
void rf_multiplayer_setup_latch_password_edit()
{
  unk_6F2D01 = 1;
}

