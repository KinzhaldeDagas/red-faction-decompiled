// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045BCA0 rf_multiplayer_setup_toggle_lan_only
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Logical-not raw LANBYTE6F5E51 (zero->1,ANY nonzero->0),store normalized result there,then mirror into
// checkbox stateBYTE6F2DC0. Return normalized EAX0/1. No registry persistence,search restart,network operation,sound or independent checkbox-state read. Registry persistence is
// separate45D150 and tests EXACT1.
BOOL rf_multiplayer_setup_toggle_lan_only()
{
  BOOL result; // eax

  result = byte_6F5E51[0] == 0;
  byte_6F5E51[0] = byte_6F5E51[0] == 0;
  unk_6F2DC0 = byte_6F5E51[0];
  return result;
}

