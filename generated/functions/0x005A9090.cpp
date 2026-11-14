// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A9090 rf_text_list_inner_height
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall list. Returns signed outer height DWORD+24 minus2*vertical padding DWORD+704. No minimum0 clamp or scrollbar subtraction.
int __thiscall rf_text_list_inner_height(_DWORD *this)
{
  return *(this + 6) - 2 * *(this + 176);
}

