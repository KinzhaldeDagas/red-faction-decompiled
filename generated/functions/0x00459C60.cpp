// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00459C60 rf_main_menu_open_load_panel
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. First calls459060 begin-close transition, then requests deferred panel6 through446460 with two zero transition flags. Removes12 outgoing stack
// bytes and forwards helper EAX. No own readiness/admission tests, immediate panel allocation or rollback if request fails; close transition precedes request.
int rf_main_menu_open_load_panel()
{
  rf_main_menu_begin_close_transition();
  return rf_ui_request_panel_deferred(6, 0, 0);
}

