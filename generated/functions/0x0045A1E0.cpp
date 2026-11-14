// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045A1E0 rf_ui_clear_owned_string_6F2C78
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Noarg. Assign empty original PE Cstring635D2A into owned RFString6F2C78 through assign_from_cstr,return delegate/destination
// pointer. One string clear only,no object destruction, network operation, render/cache reset or broad UI teardown in body. Called from application cleanup4F2542. Storage ownership
// retained by RFString assignment implementation.
_DWORD *rf_ui_clear_owned_string_6F2C78()
{
  return rf_string_assign_from_cstr(unk_6F2C78, (char *)byte_635D2A);
}

