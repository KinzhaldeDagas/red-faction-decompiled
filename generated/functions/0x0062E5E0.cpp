// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062E5E0 rf_mouse_initialize_snapshot_button_deadlines
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Recovered CRT initialization routine. Calls vector-constructor iterator on snapshot base193A0B0 with count3,stride16 and button-record deadline constructor58ADE0. Thus initializes deadline+12 in each snapshot record to-1; constructor does not clear other fields. No mouse enabled/critical-section guard or function arguments.
void __cdecl rf_mouse_initialize_snapshot_button_deadlines()
{
  rf_vector_construct_no_unwind(unk_193A0B0, 0x10u, 3, rf_mouse_button_record_construct_deadline);
}

