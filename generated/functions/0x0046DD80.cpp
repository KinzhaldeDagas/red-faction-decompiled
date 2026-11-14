// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046DD80 rf_persona_history_scroll_group_press
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): cdecl pointer callback(x,y). Hit-tests children6F8B08/count6F8B88; if drag-capture BYTE6F89B5 is nonzero, forces child index2 (slider) even after a miss. For nonnegative
// result invokes nonnull child+32 callback with TWO original(x,y) stack arguments. Forced index is not bounds checked; no own state-byte or modal checks. EAX is incidental.
int __cdecl rf_persona_history_scroll_group_press(int physical_x, int physical_y)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F8B08, dword_6F8B88);
  result = byte_6F89B5[0];
  if ( byte_6F89B5[0] )
    v3 = 2;
  if ( v3 >= 0 )
  {
    if ( *(_DWORD *)(unk_6F8B08[v3] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F8B08[v3] + 32))(physical_x, physical_y);
  }
  return result;
}

