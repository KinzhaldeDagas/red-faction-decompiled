// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A7890 rf_text_list_scroll_left_step
// UNREALRED VERIFIED [list-selection-20261029]: Sets scrollX through0x5A87B0 to current scrollX+708 minus step DWORD+720. Returns setter result; step not validated,so negative step reverses direction.
_DWORD *__thiscall rf_text_list_scroll_left_step(_DWORD *this)
{
  return rf_text_list_set_scroll_x(this, *(this + 177) - *(this + 180));
}

