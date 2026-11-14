// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB750 rf_ui_gadget_process_children_input
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall gadget,input code. Interaction-blocked predicate0x5AB8F0 true returns code unchanged. Otherwise iterates child+620,next sibling+624,calling child virtual+20 and feeding returned code into next child. Does NOT stop when code becomes0. No independent input dequeue,focus selection or pointer-cycle validation;returns final code.
int __thiscall rf_ui_gadget_process_children_input(_DWORD *this, int a2)
{
  _DWORD *i; // [esp+4h] [ebp-4h]

  if ( rf_ui_gadget_is_interaction_blocked(this) )
    return a2;
  for ( i = (_DWORD *)*(this + 155); i; i = (_DWORD *)i[156] )
    a2 = (*(int (__thiscall **)(_DWORD *, int))(*i + 20))(i, a2);
  return a2;
}

