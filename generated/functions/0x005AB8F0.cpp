// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB8F0 rf_ui_gadget_is_interaction_blocked
// UNREALRED VERIFIED [ui-properties-20261029]: Returns1 if owner+604 null,owner-window blocking predicate0x5B10B0 true,or recursive parent+616 blocked. Otherwise returns base disabled BYTE+28 via0x5F1400 without normalization. Does not test virtual hidden predicate directly,change focus or flags. No parent-cycle guard.
char __thiscall rf_ui_gadget_is_interaction_blocked(_DWORD *this)
{
  if ( !*(this + 151) )
    return 1;
  if ( rf_ui_window_is_interaction_blocked((_DWORD *)*(this + 151)) )
    return 1;
  if ( *(this + 154) && rf_ui_gadget_is_interaction_blocked((_DWORD *)*(this + 154)) )
    return 1;
  return rf_ui_base_get_disabled_byte(this);
}

