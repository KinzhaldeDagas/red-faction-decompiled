// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571950 rf_renderer_reserved_noop_571950
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): Standalone prologue/epilogue with no side effects,calls or defined return. EAX/ST0 preserved;not a gamma getter.
void __cdecl rf_renderer_reserved_noop_571950()
{
  ;
}

