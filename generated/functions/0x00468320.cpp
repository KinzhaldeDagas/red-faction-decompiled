// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00468320 rf_controls_action_list_press
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl(x,y). Either coordinate<=0 ->visible ordinal=selected6F62BC-scroll6F62B8;positiveXY ->ordinal=(y-trunc(absListY*scaleY))/pixelRowHeight via signed IDIV;X
// otherwise ignored. CaptureDWORD6F62B4==EXACT1 ->poll/accept mouse binding4683C0(-1),ignoring clicked row. Other capture values:if ordinal equals current selected visible
// ordinal,begin capture ONLY when capture==0;else selected=ordinal+scroll. NO ordinal>=0/visibleRows/actionCount checks,no ensure-visible or double-click timer. Can set out-of-range
// selected index;hit-test/caller supplies usual geometry. Return incidental mixed pointer/EAX residue.
int *__cdecl rf_controls_action_list_press(int a1, int a2)
{
  int *result; // eax
  int v3; // [esp+8h] [ebp-4h]

  if ( a1 <= 0 || a2 <= 0 )
    v3 = dword_6F62BC - dword_6F62B8;
  else
    v3 = (a2 - (int)((double)rf_ui_control_absolute_y(&dword_6F62C0) * rf_ui_scale_y)) / dword_6F299C;
  if ( unk_6F62B4 == 1 )
    return (int *)rf_controls_accept_binding_input(-1);
  result = (int *)(dword_6F62BC - dword_6F62B8);
  if ( v3 == dword_6F62BC - dword_6F62B8 )
  {
    if ( !unk_6F62B4 )
      return rf_controls_binding_capture_begin();
  }
  else
  {
    dword_6F62BC = v3 + dword_6F62B8;
  }
  return result;
}

