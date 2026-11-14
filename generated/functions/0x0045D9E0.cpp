// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045D9E0 rf_multiplayer_setup_persist_and_copy_server_name
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl output RFString storage pointer,return same pointer. FIRST write registry Cstring6F3150 under original
// key661EB4 ->"ServerName",then construct output from same live Cstring. Registry failure ignored;no output pointer/length/empty/default validation,live buffer mutation,network name
// update or existing-output destruction in body. Caller must supply construction storage. Native hidden-result style slot is real4-byte stack pointer.
_DWORD *__cdecl rf_multiplayer_setup_persist_and_copy_server_name(_DWORD *a1)
{
  rf_registry_write_cstring_without_terminator(nullptr, lpValueName, byte_6F3150);
  rf_string_construct_from_cstr(a1, (char *)byte_6F3150);
  return a1;
}

