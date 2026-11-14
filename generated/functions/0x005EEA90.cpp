// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EEA90 rf_scrollbar_set_thumb_length
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall scrollbar,length. Stores DWORD+656,returns this. No min/max guard,track fit check or redraw/notification in body.
_DWORD *__thiscall rf_scrollbar_set_thumb_length(_DWORD *this, int a2)
{
  *(this + 164) = a2;
  return this;
}

