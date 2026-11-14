// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABCA0 rf_ui_gadget_matches_bound_key
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Argument input code<=0 returnsfalse. Otherwise compares EXACT code against2 DWORD slots+588/+592,returns1 first match,else0. No modifier masking,state mutation or parent/window traversal.
char __thiscall rf_ui_gadget_matches_bound_key(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  if ( a2 <= 0 )
    return 0;
  for ( i = 0; i < 2; ++i )
  {
    if ( a2 == *(this + i + 147) )
      return 1;
  }
  return 0;
}

