// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EEF10 rf_scrollbar_set_total_extent
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall scrollbar,total extent. Sets range DWORD+648=total - page extent DWORD+680 +1,then0x5EEF40 recomputes thumb length. Does not clamp range to positive,change page extent or position+652,or emit notification. Return is thumb-size setter result.
_DWORD *__thiscall rf_scrollbar_set_total_extent(_DWORD *this, int a2)
{
  *(this + 162) = a2 - *(this + 170) + 1;
  return rf_scrollbar_recompute_thumb_length((int)this);
}

