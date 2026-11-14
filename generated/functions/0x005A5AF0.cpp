// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5AF0 rf_text_list_block_intersects_vertical_view
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall list,block. Strict overlap test: scrollY+712 < block.topY+16+height+24 AND scrollY+innerHeight > block.topY. Equality at touching edge is NOT overlap. No horizontal visibility,clipping or state mutation.
bool __thiscall rf_text_list_block_intersects_vertical_view(_DWORD *this, int a2)
{
  return *(this + 178) < *(_DWORD *)(a2 + 24) + *(_DWORD *)(a2 + 16)
      && *(this + 178) + rf_text_list_inner_height(this) > *(_DWORD *)(a2 + 16);
}

