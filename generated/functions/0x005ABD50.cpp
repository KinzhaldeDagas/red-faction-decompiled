// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABD50 rf_ui_gadget_hit_test_tree
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall gadget,screen X,Y. Recurses all children first,keeps LAST nonnull child hit and returns it before testing self. Self virtual hidden predicate+16 true rejects;otherwise requires point in absolute half-open rectangle. Calls own virtual region hit-test+24. Gadget type1:nonnegative region returns this only when region!=0;negative region falls back parent/window region0x5ABCF0. Other types use region directly. Final negative region accepts this,else requires region==DWORD+600. No explicit disabled/owner-modal check,cycle detection or clipping to parent rectangle in this body.
_DWORD *__thiscall rf_ui_gadget_hit_test_tree(_DWORD *this, int a2, int a3)
{
  _DWORD *v5; // [esp+4h] [ebp-18h]
  _DWORD *v6; // [esp+8h] [ebp-14h]
  int v7; // [esp+Ch] [ebp-10h]
  _DWORD *i; // [esp+10h] [ebp-Ch]
  int parent_region; // [esp+14h] [ebp-8h]
  int v10; // [esp+18h] [ebp-4h]

  v6 = nullptr;
  for ( i = (_DWORD *)*(this + 155); i; i = (_DWORD *)i[156] )
  {
    v5 = rf_ui_gadget_hit_test_tree(i, a2, a3);
    if ( v5 )
      v6 = v5;
  }
  if ( v6 )
    return v6;
  if ( (*(unsigned __int8 (__thiscall **)(_DWORD *))(*this + 16))(this) )
    return nullptr;
  v7 = a2 - rf_ui_gadget_absolute_x(this, 0);
  v10 = a3 - rf_ui_gadget_absolute_y(this, 0);
  if ( v7 < 0 || v10 < 0 || v7 >= *(this + 5) || v10 >= *(this + 6) )
    return nullptr;
  parent_region = (*(int (__thiscall **)(_DWORD *, int, int))(*this + 24))(this, a2, a3);
  if ( *(this + 149) == 1 )
  {
    if ( parent_region >= 0 )
    {
      if ( parent_region )
        return this;
      else
        return nullptr;
    }
    parent_region = rf_ui_gadget_query_parent_region((_DWORD **)this, a2, a3);
  }
  if ( parent_region < 0 || *(this + 150) == parent_region )
    return this;
  else
    return nullptr;
}

