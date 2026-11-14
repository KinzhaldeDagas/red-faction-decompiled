// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00445FF0 rf_clear_strings6F2C78_and87C65C
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, void. Assign PE empty Cstring63385C to RFString6F2C78, then distinct PE empty Cstring63385D to RFString87C65C
// through55FFA0. No panel/depth/pending reset or containing allocation deletion. Assignment helper owns buffer retention/reallocation behavior; this body does not guarantee prior
// reserve capacity is freed or zeroed.
void __cdecl rf_clear_strings6F2C78_and87C65C()
{
  rf_string_assign_from_cstr(unk_6F2C78, (char *)&byte_63385C);
  rf_string_assign_from_cstr(unk_87C65C, (char *)&byte_63385D);
}

