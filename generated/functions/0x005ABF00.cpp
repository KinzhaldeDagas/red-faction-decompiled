// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABF00 rf_ui_gadget_draw_children_and_notify
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall. If virtual predicate+16 false,walks child+620 and sibling+624,invokes each child virtual draw+28,then calls own virtual event+4 with code2,arg-99999. Predicate true skips both. Does not restore clip/render state,select focus or reset child list;return is predicate/event result.
int __thiscall rf_ui_gadget_draw_children_and_notify(_DWORD *this)
{
  int result; // eax
  _DWORD *i; // [esp+4h] [ebp-4h]

  result = (*(int (__thiscall **)(_DWORD *))(*this + 16))(this);
  if ( !(_BYTE)result )
  {
    for ( i = (_DWORD *)*(this + 155); i; i = (_DWORD *)i[156] )
      (*(void (__thiscall **)(_DWORD *))(*i + 28))(i);
    return (*(int (__thiscall **)(_DWORD *, int, int))(*this + 4))(this, 2, -99999);
  }
  return result;
}

