// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B0690 rf_ui_window_contains_point_if_visible
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall window,x,y,RET8. Calls virtual slot16 first; any nonzero AL returnsfalse. Otherwise subtracts stored window x12/y16 and returns true iff local x>=0,y>=0,x<width20,y<height24. Half-open right/bottom bounds; negative dimensions naturally reject. Does not test bitmap mask,children,disabled byte or clipping state.
bool __thiscall rf_ui_window_contains_point_if_visible(_DWORD *this, int a2, int a3)
{
  int v5; // [esp+Ch] [ebp+8h]
  int v6; // [esp+10h] [ebp+Ch]

  if ( (*(unsigned __int8 (__thiscall **)(_DWORD *))(*this + 16))(this) )
    return 0;
  v5 = a2 - *(this + 3);
  v6 = a3 - *(this + 4);
  return v5 >= 0 && v6 >= 0 && v5 < *(this + 5) && v6 < *(this + 6);
}

