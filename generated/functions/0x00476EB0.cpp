// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476EB0 rf_cutscene_aux_bezier_record_destroy
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): Native thiscall ECX record, no stack arguments. Calls shared no-op destructor4580D0 on record+8 FIRST, then RFString buffer
// destructor55F6D0 on record+0, with SEH cleanup preserving string ownership. Does not free record storage or iterate the array;62EF20 owns32-record traversal. No defined semantic
// return value.
void __thiscall rf_cutscene_aux_bezier_record_destroy(void *this)
{
  rf_shared_noop_destructor_4580d0();
  rf_string_destroy_buffer(this);
}

