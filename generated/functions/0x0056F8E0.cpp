// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056F8E0 rf_console_wait_for_input_if_enabled_then_exit_one
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args,noreturn. If byte704E83 exactly1,resets all input state,prints prompt via570820,then loops:breaks on nonzero dequeued input;otherwise console update/render(windowMode1) and continues until quit flag1BC213C nonzero. Regardless gate/exit reason calls CRT exit(1). Does not execute external shell or return a key value;nonlocal global console/input state shared.
void __noreturn rf_console_wait_for_input_if_enabled_then_exit_one()
{
  if ( byte_704E83 == 1 )
  {
    rf_input_reset_all_key_and_event_state();
    rf_console_printf_unbounded_stack2048(unk_88E350);
    do
    {
      if ( rf_input_dequeue_event() )
        break;
      rf_console_update_and_render(1u);
    }
    while ( !unk_1BC213C );
  }
  exit(1);
}

