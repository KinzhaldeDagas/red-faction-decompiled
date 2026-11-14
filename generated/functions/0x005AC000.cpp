// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AC000 rf_ui_gadget_clear_matching_owner_targets
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): If owner+1224 equals this,zero that hover pointer; if owner+1228 equals this,zero navigation pointer. Each equality helper guards missing owner. Returns BOOL from navigation-target equality (not whether either changed). Does not release global keyboard focus,emit events or traverse children.
BOOL __thiscall rf_ui_gadget_clear_matching_owner_targets(_DWORD *this)
{
  BOOL result; // eax

  if ( rf_ui_gadget_is_owner_hover_target(this) )
    *(_DWORD *)(*(this + 151) + 1224) = 0;
  result = rf_ui_gadget_is_owner_navigation_target(this);
  if ( result )
    *(_DWORD *)(*(this + 151) + 1228) = 0;
  return result;
}

