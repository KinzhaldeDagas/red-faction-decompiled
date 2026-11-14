// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448A90 rf_clear_level_strings_and_parser_text_state
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, void/incidental final delegate result. In strict order assign empty C strings through55FFA0 RFString assignment
// to global objects6FC31C,6FC3AC,6FC324,6FC32C,6FC478,6FC300,6FC2F8,6FC308. Eight source addresses633CAF/633CBB/633CCE/633CCF/633CD6/633CD7/633CDD/633CDE are each original PE byte00;
// adjacent nonempty literals are not these arguments. These are string assignments, not memset or destruction of containing objects. Then4838A0 clears parser scratch,4855D0 clears
// level-text slots,48F740 clears global multiplayer string704EC0, in that order; results ignored. No runtime/pause/authority admission, own resource-array iteration or rollback.
// Delegate allocations/releases and partial prior clears remain observable if later work fails.
void __cdecl rf_clear_level_strings_and_parser_text_state()
{
  rf_string_assign_from_cstr(unk_6FC31C, (char *)&byte_633CAF);
  rf_string_assign_from_cstr(unk_6FC3AC, (char *)&byte_633CBB);
  rf_string_assign_from_cstr(unk_6FC324, (char *)&byte_633CCE);
  rf_string_assign_from_cstr(unk_6FC32C, (char *)&byte_633CCF);
  rf_string_assign_from_cstr(unk_6FC478, (char *)&byte_633CD6);
  rf_string_assign_from_cstr(unk_6FC300, (char *)&byte_633CD7);
  rf_string_assign_from_cstr(unk_6FC2F8, (char *)&byte_633CDD);
  rf_string_assign_from_cstr(dword_6FC308, (char *)byte_633CDE);
  rf_rfl_clear_parser_scratch();
  rf_level_text_clear_slots();
  rf_multiplayer_clear_string_704EC0();
}

