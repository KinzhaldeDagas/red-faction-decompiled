// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A78C0 rf_text_list_scroll_right_step
// UNREALRED VERIFIED [list-selection-20261029]: Sets scrollX through0x5A87B0 to current scrollX+708 plus step DWORD+720. Returns setter result. No selection notification or step normalization.
_DWORD *__thiscall rf_text_list_scroll_right_step(_DWORD *this)
{
  return rf_text_list_set_scroll_x(this, *(this + 180) + *(this + 177));
}

