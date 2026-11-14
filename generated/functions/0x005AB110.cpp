// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB110 rf_ui_gadget_unlink_parent_chain
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall gadget. Parent+616 nonnull selects parent.child head+620;otherwise selects owner window+604 root-child head+1220. Walks singly linked sibling fields+624 using pointer-to-link. On matching this,splices next sibling into link,clears parent+616 and sibling+624,returns this. Not found leaves fields unchanged,incidental return. Does not alter own child head+620,owner-registration doubly linked fields+608/+612,focus or allocation. Missing owner/cycles not checked.
_DWORD *__thiscall rf_ui_gadget_unlink_parent_chain(_DWORD *this)
{
  _DWORD *result; // eax
  _DWORD *v2; // [esp+4h] [ebp-4h]

  result = this;
  if ( *(this + 154) )
  {
    v2 = (_DWORD *)(*(this + 154) + 620);
  }
  else
  {
    result = this;
    v2 = (_DWORD *)(*(this + 151) + 1220);
  }
  while ( *v2 )
  {
    result = v2;
    if ( (_DWORD *)*v2 == this )
    {
      *v2 = *(this + 156);
      *(this + 154) = 0;
      *(this + 156) = 0;
      return this;
    }
    v2 = (_DWORD *)(*v2 + 624);
  }
  return result;
}

