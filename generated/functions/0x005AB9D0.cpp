// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB9D0 rf_ui_gadget_is_hidden_hierarchy
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Returns1 when owner+604 missing,owner virtual hidden predicate+16 true,or parent+616 virtual hidden predicate+16 true. Else returns own hidden BYTE+29 via0x5F1440 without normalization. Does not combine disabled/modal blocking or mutate visibility/focus.
char __thiscall rf_ui_gadget_is_hidden_hierarchy(_DWORD *this)
{
  if ( !*(this + 151) )
    return 1;
  if ( (*(unsigned __int8 (__thiscall **)(_DWORD))(*(_DWORD *)*(this + 151) + 16))(*(this + 151)) )
    return 1;
  if ( *(this + 154) && (*(unsigned __int8 (__thiscall **)(_DWORD))(*(_DWORD *)*(this + 154) + 16))(*(this + 154)) )
    return 1;
  return rf_ui_base_get_hidden_byte(this);
}

