// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062EF20 rf_cutscene_aux_bezier_array_atexit_destroy
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): No-argument static cleanup. Calls EH vector destructor iterator on base6FB670, stride100 bytes, count32, destructor476EB0, then returns.
// Callee-cleaned iterator arguments total16 bytes. Own body does not free static storage, reset registry counts or destroy other cutscene arrays; element destructor owns inline
// string cleanup.
void rf_cutscene_aux_bezier_array_atexit_destroy()
{
  `eh vector destructor iterator'(byte_6FB670, 0x64u, 32, rf_cutscene_aux_bezier_record_destroy);
}

