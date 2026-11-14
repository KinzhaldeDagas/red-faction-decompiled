// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045D130 rf_multiplayer_setup_destroy_level_catalogs
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg,atexit callback registered only on first setup construction. Clear/destroy master two-RFString array6F2E14
// then filtered array6F2DC4 via45DE40. Does not release selected-index array6F2E64,UI child arrays,reset initialization latch or persist settings in this body. No broad
// application/network shutdown semantics;callee owns backing-record destruction.
void __cdecl rf_multiplayer_setup_destroy_level_catalogs()
{
  rf_two_rfstring_array16_clear_and_release(dword_6F2E14);
  rf_two_rfstring_array16_clear_and_release(dword_6F2DC4);
}

