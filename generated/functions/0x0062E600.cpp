// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062E600 rf_mouse_initialize_pending_button_deadlines
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Recovered CRT initialization routine. Calls vector-constructor iterator on pending-button base193A080 with count3,stride16 and constructor58ADE0. Sets each pending deadline+12 to-1 while other fields rely on static initialization/reset paths. No runtime mouse polling, synchronization or arguments.
void __cdecl rf_mouse_initialize_pending_button_deadlines()
{
  rf_vector_construct_no_unwind(unk_193A080, 0x10u, 3, rf_mouse_button_record_construct_deadline);
}

