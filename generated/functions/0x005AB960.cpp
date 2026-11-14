// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB960 rf_ui_gadget_is_enabled_hierarchy
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Returnsfalse if owner+604 missing,owner window interaction-blocked,or parent+616 interaction-blocked. Otherwise returns base enabled predicate0x5F1420 (disabled BYTE+28==0). Does not test hidden state or change focus. No parent-cycle guard.
bool __thiscall rf_ui_gadget_is_enabled_hierarchy(unsigned __int8 *this)
{
  if ( !*((_DWORD *)this + 151) )
    return 0;
  if ( rf_ui_window_is_interaction_blocked(*((_DWORD **)this + 151)) )
    return 0;
  if ( *((_DWORD *)this + 154) && rf_ui_gadget_is_interaction_blocked(*((_DWORD **)this + 154)) )
    return 0;
  return rf_ui_base_is_enabled(this);
}

