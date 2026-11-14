// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570190 rf_console_begin_close_animation_and_reset_input
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Sets baseline y180A498=192,visible180A486=0,animation180A485=1,then resets all key/event state. Does not hide immediately or clear console history/output;overlay draw steps toward-11.
void rf_console_begin_close_animation_and_reset_input()
{
  dword_180A498 = 192;
  byte_180A486[0] = 0;
  unk_180A485 = 1;
  rf_input_reset_all_key_and_event_state();
}

