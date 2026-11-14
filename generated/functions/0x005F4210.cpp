// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F4210 rf_ui_inputbox_destroy
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): If cursor animation pointer1440 nonNULL,calls VANI deleting destructor(flag1),then full gadget destroy0x5AB7B0. Does NOT zero1440 here or release bitmap handles1444/1448/1452. No allocation delete for this object;return forwarded.
int __thiscall rf_ui_inputbox_destroy(int this)
{
  if ( *(_DWORD *)(this + 1440) )
    rf_vani_player_scalar_deleting_destructor(*(int **)(this + 1440), 1);
  return rf_ui_gadget_destroy((_DWORD *)this);
}

