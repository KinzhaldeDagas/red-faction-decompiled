// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570200 rf_console_get_overlay_height
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Returns signed32 baseline180A498+11 throughEAX without clamp,initialization or animation update. Ordinary closed target-11 yields0,open target192 yields203.
int __cdecl rf_console_get_overlay_height()
{
  return dword_180A498 + 11;
}

