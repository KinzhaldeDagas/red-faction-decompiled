// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045CDC0 rf_multiplayer_setup_server_name_press_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Cdecl(x,y). Enabled-button hit test against child pointer table6F32B0/count6F3330. If signed index>=0 and hit
// control DWORD32 callback nonNULL,call callback cdecl with ORIGINAL(x,y);otherwise return hit index. No own upper-index/controlNULL/state9 recheck or sound. Return callback EAX when
// invoked,not uniform bool. Native callback32 differs from drag callback36 used by45B530.
int __cdecl rf_multiplayer_setup_server_name_press_dispatch(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F32B0, dword_6F3330);
  if ( result >= 0 )
  {
    if ( *(_DWORD *)(unk_6F32B0[result] + 32) )
      return (*(int (__cdecl **)(int, int))(unk_6F32B0[result] + 32))(physical_x, physical_y);
  }
  return result;
}

