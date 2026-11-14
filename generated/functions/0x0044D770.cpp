// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044D770 rf_hud_three_string_record_destroy
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Thiscall receiver, no stack arguments, void. Destroy owned RFString members in EXACT reverse order
// receiver+16,receiver+8,receiver+0 through55F6D0. Each helper frees nonNULL member buffer at member+4 and clears that pointer, but preserves stored extent at member+0; outer body
// does not clear remaining record bytes or free containing receiver. No NULL receiver guard, allocation, refcount/vtable cleanup or extra string member. Native SEH state1 before+16
// destruction, state0 before+8, state-1 before base member; captured funclets destroy receiver+8/base as required on unwind, preserving member order if earlier destruction throws.
// Compiler handler validates security cookie and delegates CxxFrameHandler3; it does not constitute additional normal-path member cleanup. Normal tail restores FS exception chain;
// result register incidental.
void __thiscall rf_hud_three_string_record_destroy(char *this)
{
  rf_string_destroy_buffer(this + 16);
  rf_string_destroy_buffer(this + 8);
  rf_string_destroy_buffer(this);
}

