// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB880 rf_ui_gadget_absolute_y
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall gadget,extra Y offset. Returns local Y+16+offset plus recursive parent absolute Y if parent+616 exists,else owner window Y+16. No padding,scroll,scale conversion or pointer-cycle guards.
int __thiscall rf_ui_gadget_absolute_y(_DWORD *this, int a2)
{
  int v2; // esi

  if ( !*(this + 154) )
    return *(_DWORD *)(*(this + 151) + 16) + *(this + 4) + a2;
  v2 = *(this + 4) + a2;
  return v2 + rf_ui_gadget_absolute_y((_DWORD *)*(this + 154), 0);
}

