// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459580 rf_main_menu_begin_close_once
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Zero-extend interaction-active byte into EAX. Zero returns EAX0 without transition. Any nonzero calls459060, then clears interaction-active
// byte0 and returns helper EAX. Clear occurs AFTER transition helper returns; no whole menu-state reset and no normalized success result.
int rf_main_menu_begin_close_once()
{
  int result; // eax

  result = rf_main_menu_interaction_active;
  if ( rf_main_menu_interaction_active )
  {
    result = rf_main_menu_begin_close_transition();
    rf_main_menu_interaction_active = 0;
  }
  return result;
}

