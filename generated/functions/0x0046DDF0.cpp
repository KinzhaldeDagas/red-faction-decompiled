// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046DDF0 rf_persona_history_scroll_group_drag
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): cdecl pointer callback(x,y). Hit-tests enabled scroll children6F8B08/count6F8B88 and for nonnegative hit invokes nonnull child+36 drag callback with TWO original(x,y) stack
// arguments. Unlike press wrapper, does not force slider during capture. EAX is incidental.
int __cdecl rf_persona_history_scroll_group_drag(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F8B08, dword_6F8B88);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F8B08[result] + 36) )
      return (*(int (__cdecl **)(int, int))(unk_6F8B08[result] + 36))(physical_x, physical_y);
  }
  return result;
}

