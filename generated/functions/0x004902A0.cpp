// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004902A0 rf_multiplayer_draw_stalled_connection_icon
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl no arguments. Only stalled DWORD704E90 nonzero AND state accessor446190 EXACT11 sets current RGBA white255 and draws bitmap66286C (RedJack.vbm loaded by process init)
// unscaled/clipped atx22,y135 with global187CD38 draw flags. No bitmap handle validation,session/mode check or prior-color restore. Other states do nothing.
void rf_multiplayer_draw_stalled_connection_icon()
{
  if ( unk_704E90 )
  {
    if ( rf_ui_panel_stack_current_id() == 11 )
    {
      rf_render_color_set_rgba8(255, 255, 255, 255);
      rf_bitmap_draw_unscaled_clipped(dword_66286C, 22, 135, unk_187CD38);
    }
  }
}

