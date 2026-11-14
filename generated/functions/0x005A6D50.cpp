// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A6D50 rf_text_list_get_selected_entry
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall returns DWORD pointer at+692 (selected entry) in EAX. Inferred int type is misleading for pointer use. Does not reveal,validate membership or retain entry; pointer invalid after removal/destruction.
int __thiscall rf_text_list_get_selected_entry(_DWORD *this)
{
  return *(this + 173);
}

