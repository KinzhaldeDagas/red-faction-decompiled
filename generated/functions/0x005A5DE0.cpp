// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A5DE0 rf_text_list_last_block_starting_at_or_before_y
// UNREALRED VERIFIED [text-layout-20261029]: Thiscall list,Y. Empty or negative Y returns0. Advances nodes while node.topY<=Y,then returns PREVIOUS pointer at resulting node+12,including sentinel.prev after end. Result is a block pointer,not an ID despite inferred int return. No explicit sentinel rejection when Y precedes first stale/nonzero top; measured first top normally0.
int __thiscall rf_text_list_last_block_starting_at_or_before_y(_DWORD *this, int a2)
{
  _DWORD *i; // [esp+4h] [ebp-4h]

  if ( (_DWORD *)*(this + 183) == this + 181 )
    return 0;
  if ( a2 < 0 )
    return 0;
  for ( i = (_DWORD *)*(this + 183); i != this + 181 && i[4] <= a2; i = (_DWORD *)i[2] )
    ;
  return i[3];
}

