// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB830 rf_ui_gadget_absolute_x
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall gadget,extra X offset. Returns local X+12+offset plus recursive parent absolute X if parent+616 exists,else owner window X+12. No clipping,scroll offsets,scale conversion,parent-cycle or owner-null validation.
int __thiscall rf_ui_gadget_absolute_x(_DWORD *this, int a2)
{
  int v2; // esi

  if ( !*(this + 154) )
    return *(_DWORD *)(*(this + 151) + 12) + *(this + 3) + a2;
  v2 = *(this + 3) + a2;
  return v2 + rf_ui_gadget_absolute_x((_DWORD *)*(this + 154), 0);
}

