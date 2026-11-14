// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045D150 rf_multiplayer_setup_persist_lan_only
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. Registry_write_dword(NULL,"ListLAN",rawLANBYTE6F5E51==EXACT1). Values other than1 persist0,including other
// nonzero bytes;distinct from toggle/load normalization. Does not normalize live byte,mirror checkbox,refresh network listing or play sound. Return registry result.
int rf_multiplayer_setup_persist_lan_only()
{
  return rf_registry_write_dword(nullptr, "ListLAN", byte_6F5E51[0] == 1);
}

