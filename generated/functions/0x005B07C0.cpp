// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B07C0 rf_ui_window_find_flat_child_by_name
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall window,name,RET4. Traverses flat-list next1204 to embedded gadget sentinel592 via child next612. Case-insensitive stricmp at child name+30; returns FIRST matching child pointer in EAX,else0. Searches flat registry rather than child tree; no enabled/hidden/name-NULL/cycle check.
int __thiscall rf_ui_window_find_flat_child_by_name(_DWORD *this, char *String2)
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = *(this + 301); (_DWORD *)i != this + 148; i = *(_DWORD *)(i + 612) )
  {
    if ( !_stricmp((const char *)(i + 30), String2) )
      return i;
  }
  return 0;
}

