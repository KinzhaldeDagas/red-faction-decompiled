// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABA50 rf_ui_gadget_set_parent
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall gadget,new parent pointer. First unlinks old parent/root sibling chain through0x5AB110. Sets parent+616;nonnull parent prepends this to its child head+620,else prepends to owner window root-child head+1220. Uses sibling+624. No cycle/owner compatibility checks,coordinate conversion,focus mutation or owner-registration update. Returns this on parent branch,owner pointer on root branch.
_DWORD *__thiscall rf_ui_gadget_set_parent(_DWORD *this, int a2)
{
  _DWORD *result; // eax

  rf_ui_gadget_unlink_parent_chain(this);
  *(this + 154) = a2;
  if ( a2 )
  {
    *(this + 156) = *(_DWORD *)(a2 + 620);
    *(_DWORD *)(a2 + 620) = this;
    return this;
  }
  else
  {
    *(this + 156) = *(_DWORD *)(*(this + 151) + 1220);
    result = (_DWORD *)*(this + 151);
    result[305] = this;
  }
  return result;
}

