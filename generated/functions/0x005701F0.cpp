// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005701F0 rf_console_get_animation_byte
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Returns raw animation byte180A485 inAL,not visibility or keyboard capture status.
char rf_console_get_animation_byte()
{
  return unk_180A485;
}

