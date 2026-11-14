// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056EC20 rf_console_update_and_render
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl one BYTE windowMode. If initialized byte0 calls570210(1). Processes input and renders when windowMode!=0 OR visibleByte180A486==1 OR animationByte180A485==1. Chooses GDI56EC80 ONLY when windowMode exactly1;other nonzero modes choose renderer overlay56F4B0. No render when all predicates false. Returns low byte of renderer/deadline/API result,not normalized visibility/success; no incoming EBX/EDI/ESI arguments.
unsigned __int8 __cdecl rf_console_update_and_render(unsigned __int8 window_mode)
{
  unsigned __int8 result; // al

  if ( !unk_180A484 )
    rf_console_initialize_once_and_load_history(1);
  if ( window_mode || unk_180A486 == 1 || (result = unk_180A485, unk_180A485 == 1) )
  {
    rf_console_process_input_event();
    if ( window_mode == 1 )
      return (unsigned __int8)rf_console_draw_window_gdi_when_dirty();
    else
      return rf_console_draw_renderer_overlay_and_slide();
  }
  return result;
}

