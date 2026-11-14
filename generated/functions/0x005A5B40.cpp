// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5B40 rf_text_list_block_fully_inside_vertical_view
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall list,block. Inclusive containment: scrollY+712<=block.topY AND scrollY+innerHeight>=block.topY+height. No horizontal check,partial-overlap result or pointer validation.
bool __thiscall rf_text_list_block_fully_inside_vertical_view(_DWORD *this, int a2)
{
  return *(this + 178) <= *(_DWORD *)(a2 + 16)
      && *(this + 178) + rf_text_list_inner_height(this) >= *(_DWORD *)(a2 + 24) + *(_DWORD *)(a2 + 16);
}

