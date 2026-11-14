// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB4B0 rf_ui_gadget_find_navigation_candidate_left
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall gadget,screen point X,Y. If virtual predicate vtable+32 true,gets absolute widget origin,computes forward gap=pointX-(candidateX+width) and vertical perpendicular gap (0 inside half-open extent;distance outside,far-edge case includes+1). Candidate accepted when forward gap>=perpendicular gap and sum STRICTLY less than global best0x1CF7C20;stores sum and gadget pointer0x1CF7C1C. Recurses child+620 then sibling+624 EVEN when current gadget ineligible. Does not reset best globals,move focus,validate dimensions or detect cycles. Returns incidental predicate/this/recursive result,not selected candidate pointer.
_DWORD *__thiscall rf_ui_gadget_find_navigation_candidate_left(_DWORD *this, int a2, int a3)
{
  _DWORD *result; // eax
  int v5; // [esp+4h] [ebp-10h]
  int v6; // [esp+8h] [ebp-Ch]
  int v7; // [esp+Ch] [ebp-8h]
  int v8; // [esp+10h] [ebp-4h]

  v6 = 0;
  if ( (*(unsigned __int8 (__thiscall **)(_DWORD *))(*this + 32))(this) )
  {
    v7 = rf_ui_gadget_absolute_x(this, 0);
    v8 = rf_ui_gadget_absolute_y(this, 0);
    if ( v8 <= a3 )
    {
      if ( *(this + 6) + v8 <= a3 )
        v6 = a3 - v8 - *(this + 6) + 1;
    }
    else
    {
      v6 = v8 - a3;
    }
    v5 = a2 - v7 - *(this + 5);
    if ( v5 >= v6 && v6 + v5 < dword_1CF7C20 )
    {
      dword_1CF7C20 = v6 + v5;
      unk_1CF7C1C = this;
    }
  }
  if ( *(this + 155) )
    rf_ui_gadget_find_navigation_candidate_left((_DWORD *)*(this + 155), a2, a3);
  result = this;
  if ( *(this + 156) )
    return rf_ui_gadget_find_navigation_candidate_left((_DWORD *)*(this + 156), a2, a3);
  return result;
}

