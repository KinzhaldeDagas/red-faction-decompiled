// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EEA50 rf_scrollbar_set_position_unclamped
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall scrollbar,position. Stores DWORD+652 and returns this. Accepts negative/out-of-range positions; does not clamp,notify or recompute thumb.
_DWORD *__thiscall rf_scrollbar_set_position_unclamped(_DWORD *this, int a2)
{
  *(this + 163) = a2;
  return this;
}

