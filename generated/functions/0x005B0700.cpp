// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B0700 rf_ui_window_hit_test_top_level_tree
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall window,x,y,RET8. Walks roots from tree1220 through sibling624 untilNULL,calling gadget recursive hit-test on each. Returns LAST nonNULL result across roots,elseNULL. Does not stop at first hit,check window rectangle or modify selection. No cycle/pointer guards.
_DWORD *__thiscall rf_ui_window_hit_test_top_level_tree(_DWORD *this, int a2, int a3)
{
  _DWORD *v4; // [esp+4h] [ebp-Ch]
  _DWORD *v5; // [esp+8h] [ebp-8h]
  _DWORD *i; // [esp+Ch] [ebp-4h]

  v5 = nullptr;
  for ( i = (_DWORD *)*(this + 305); i; i = (_DWORD *)i[156] )
  {
    v4 = rf_ui_gadget_hit_test_tree(i, a2, a3);
    if ( v4 )
      v5 = v4;
  }
  return v5;
}

