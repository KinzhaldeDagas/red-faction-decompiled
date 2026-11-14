// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AFBE0 rf_ui_window_initialize_and_link
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall6 stack args x,y,width,height,id,flags,RET24. Ensures default theme,initializes base rectangle kind1. If flags20h(modal) set,clears40h(modeless). Stores flags584,generation588=current1CF75DC; clears tree1220/1224 and selection1228; theme1248=1CF75F8. Modal path links window next1252=sentinel1CF7678,previous1256=global1CF7B60,updates previous.next and global1CF7B60=this. Other paths walk from1CF7B5C through next1252 to sentinel,calling flag getter5B0540 but DISCARDING result. Branch tests use NEW window input flags,not candidate getter value: modeless branch tests input20h(which is clear here),ordinary branch tests input20h/40h(both clear),so both scans run to sentinel in valid list.
// Then splice before reached node using its previous1256; ordinary path ends EAX0,others incidental receiver,so existing pointer return is not a uniform success result. No dimension validation,old-list unlink,duplicate insertion or cycle guard. Original raw instructions5AFCE2/5AFD5A confirm input flag reload after getter.
_DWORD *__thiscall rf_ui_window_initialize_and_link(_DWORD *this, int a2, int a3, int a4, int a5, int a6, int a7)
{
  _DWORD *i; // [esp+8h] [ebp-4h]
  _DWORD *j; // [esp+8h] [ebp-4h]

  rf_ui_initialize_default_theme_once();
  rf_ui_base_initialize_rect((int)this, 1, a2, a3, a4, a5, a6);
  if ( (a7 & 0x20) != 0 )
    a7 &= ~0x40u;
  *(this + 146) = a7;
  *(this + 147) = unk_1CF75DC;
  *(this + 305) = 0;
  *(this + 306) = 0;
  *(this + 307) = 0;
  *(this + 312) = byte_1CF75F8;
  if ( (a7 & 0x20) != 0 )
  {
    *(this + 314) = unk_1CF7B60;
    *(this + 313) = dword_1CF7678;
    *(_DWORD *)(unk_1CF7B60 + 1252) = this;
    unk_1CF7B60 = this;
    return this;
  }
  else if ( (a7 & 0x40) != 0 )
  {
    for ( i = (_DWORD *)unk_1CF7B5C; i != dword_1CF7678; i = (_DWORD *)i[313] )
    {
      rf_ui_window_get_flags(i);
      if ( (a7 & 0x20) != 0 )
        break;
    }
    *(_DWORD *)(i[314] + 1252) = this;
    *(this + 314) = i[314];
    i[314] = this;
    *(this + 313) = i;
    return this;
  }
  else
  {
    for ( j = (_DWORD *)unk_1CF7B5C; j != dword_1CF7678; j = (_DWORD *)j[313] )
    {
      rf_ui_window_get_flags(j);
      if ( (a7 & 0x20) != 0 || (a7 & 0x40) != 0 )
        break;
    }
    *(_DWORD *)(j[314] + 1252) = this;
    *(this + 314) = j[314];
    j[314] = this;
    *(this + 313) = j;
    return nullptr;
  }
}

