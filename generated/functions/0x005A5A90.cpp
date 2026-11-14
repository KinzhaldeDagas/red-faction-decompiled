// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5A90 rf_text_list_layout_block
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall list,block,callback Y. Default width999999. If list flags DWORD+628 mask0x1 set,uses configured width DWORD+672; if selected width0,uses inner width0x5A9070. Delegates0x5A57A0(block,width,Y,list callback+796),returns line count. Does not lay out other blocks,set block Y or clamp negative available width.
int __thiscall rf_text_list_layout_block(int this, int *a2, int a3)
{
  int v5; // [esp+4h] [ebp-4h]

  v5 = 999999;
  if ( (*(_DWORD *)(this + 628) & 1) != 0 )
    v5 = *(_DWORD *)(this + 672);
  if ( !v5 )
    v5 = rf_text_list_inner_width((_DWORD *)this);
  return rf_text_block_layout_wrapped_lines(a2, v5, a3, *(int (__cdecl **)(int, int))(this + 796));
}

