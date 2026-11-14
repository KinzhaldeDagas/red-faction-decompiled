// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005701C0 rf_console_begin_open_animation
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Sets y180A498=0,visible180A486=1,animation180A485=1. No input reset,initialization or output/history mutation;overlay draw advances toward192.
void rf_console_begin_open_animation()
{
  dword_180A498 = 0;
  byte_180A486[0] = 1;
  unk_180A485 = 1;
}

