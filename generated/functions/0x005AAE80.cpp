// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AAE80 rf_ui_window_get_hit_mask
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall returns DWORD pointer at window+1240. Inferred int return is a borrowed BYTE raster pointer;0 means no hit mask. Pixel interpretation established by0x5B1020. Does not copy,allocate or validate dimensions.
int __thiscall rf_ui_window_get_hit_mask(_DWORD *this)
{
  return *(this + 310);
}

