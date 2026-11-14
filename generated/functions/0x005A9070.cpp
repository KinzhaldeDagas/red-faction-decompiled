// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A9070 rf_text_list_inner_width
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall list. Returns signed outer width DWORD+20 minus2*horizontal padding DWORD+700. No minimum0 clamp,scrollbar subtraction,wrapping or mutation.
int __thiscall rf_text_list_inner_width(_DWORD *this)
{
  return *(this + 5) - 2 * *(this + 175);
}

