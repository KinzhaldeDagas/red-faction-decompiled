// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EEA10 rf_scrollbar_get_position
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall returns DWORD+652 directly. No range clamp,recalculation or event consumption.
int __thiscall rf_scrollbar_get_position(_DWORD *this)
{
  return *(this + 163);
}

