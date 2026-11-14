// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AFAA0 rf_ui_window_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Calls base constructor5F0FC0,installs ui_window vtable643BDC,constructs embedded gadget at592. Sets mask1232/background1236=-1,DWORD1240=0,disabled BYTE28=0,flat-list previous1200/next1204=embedded sentinel592,global-window next1252=0; returns receiver. Does NOT initialize window flags584,tree links1220/1224,selection1228,theme1248,generation588 or previous1256; initialize routine5AFBE0 supplies those. Constructor includes compiler EH cleanup,not a complete zero fill.
char *__thiscall rf_ui_window_construct(char *this)
{
  rf_ui_base_construct(this);
  *(_DWORD *)this = &ui_window::`vftable';
  rf_ui_gadget_construct(this + 592);
  *((_DWORD *)this + 308) = -1;
  *((_DWORD *)this + 309) = -1;
  *((_DWORD *)this + 310) = 0;
  *(this + 28) = 0;
  *((_DWORD *)this + 301) = this + 592;
  *((_DWORD *)this + 300) = this + 592;
  *((_DWORD *)this + 313) = 0;
  return this;
}

