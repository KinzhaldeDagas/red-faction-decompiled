// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C11D0 rf_bolt_emitter_register_empty_exit_hook
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, four-slot emitter lifecycle, allocation and constructor layouts, native ordered lifetime gates, attachment transforms and paused rendering): 
// Cdecl no arguments. Registers no-op4C11F0 with atexit, returns registration result EAX. No emitter/pool construction, list clearing or slot resource ownership.
int rf_bolt_emitter_register_empty_exit_hook()
{
  return atexit(rf_bolt_emitter_exit_hook_noop);
}

