// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB7B0 rf_ui_gadget_destroy
// UNREALRED VERIFIED [ui-properties-20261029]: If global focus0x1CF75D8==this,clears it. Clears owner window DWORD+604,then delegates0x5F0F30 to destroy auxiliary records and clear live byte. Does not unlink owner registration,parent/sibling chains or recursively delete child gadgets in this body. Returns base-destruction result,not a freed-object status.
int __thiscall rf_ui_gadget_destroy(_DWORD *this)
{
  if ( dword_1CF75D8 == this )
    dword_1CF75D8 = nullptr;
  *(this + 151) = 0;
  return rf_ui_base_destroy_auxiliary_records((int)this);
}

