// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045D040 rf_multiplayer_setup_toggle_password_enabled
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Logical-not raw checkedBYTE6F2EB8 ->normalized0/1;mirror into password-edit enabledBYTE6F36E1. Nonzero result
// sound44,zero sound45 (0,0.0,1.0). Then registry_write_dword(NULL,"ServerPasswordChecked",zeroExtendedChecked). No password-string clear/rewrite,validation,server/network update or
// write-result rollback;checked/enabled state and sound occur before persistence. Return registry delegate result.
int rf_multiplayer_setup_toggle_password_enabled()
{
  byte_6F2EB8[0] = byte_6F2EB8[0] == 0;
  unk_6F36E1 = byte_6F2EB8[0];
  if ( byte_6F2EB8[0] )
    rf_gamesound_play_event(44, 0, 0.0, 1.0);
  else
    rf_gamesound_play_event(45, 0, 0.0, 1.0);
  return rf_registry_write_dword(nullptr, off_661EBC, byte_6F2EB8[0]);
}

