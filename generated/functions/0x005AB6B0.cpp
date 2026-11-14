// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB6B0 rf_ui_gadget_emit_event
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall gadget,event code,argument. Argument-99999 replaced by stored DWORD+288. Calls optional cdecl callback+580(event,arg);ONLY nonzero LOW BYTE of result consumes event. Absent/zero-low-byte result bubbles through parent+616 vtable+4,or owner window+604 vtable+4 when no parent. Returns callback/bubbled result. No owner null,recursion/lifetime guard or automatic event queue;notifications are synchronous.
int __thiscall rf_ui_gadget_emit_event(int this, int a2, int a3)
{
  int result; // eax

  if ( a3 == -99999 )
    a3 = *(_DWORD *)(this + 288);
  if ( !*(_DWORD *)(this + 580) || (result = (*(int (__cdecl **)(int, int))(this + 580))(a2, a3), !(_BYTE)result) )
  {
    if ( *(_DWORD *)(this + 616) )
      return (*(int (__thiscall **)(_DWORD, int, int))(**(_DWORD **)(this + 616) + 4))(*(_DWORD *)(this + 616), a2, a3);
    else
      return (*(int (__thiscall **)(_DWORD, int, int))(**(_DWORD **)(this + 604) + 4))(*(_DWORD *)(this + 604), a2, a3);
  }
  return result;
}

