// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005701E0 rf_console_get_visible_byte
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Returns raw byte180A486 inAL;does not include animation state or perform readiness test.
unsigned __int8 __cdecl rf_console_get_visible_byte()
{
  return byte_180A486[0];
}

