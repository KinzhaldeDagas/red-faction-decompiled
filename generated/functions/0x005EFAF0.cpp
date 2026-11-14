// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EFAF0 rf_ui_button_initialize_as_child
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Arguments parent gadget,x,y,w,h,id,flags,raw base flag. Gets parent owner,initializes gadget type2,stores flags|2 (repeat mode),state0,label empty,font-1,deadline+896 offset0,press offsets0,palette0x1CF7B64. Drag fields1076/1080/1084/1088=0,1092=1,1096=255,1100=this. Finally reparents via0x5ABA50;returns parent setter result. No image-record reset.
_DWORD *__thiscall rf_ui_button_initialize_as_child(
        int this,
        _DWORD *a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        char a9)
{
  int owner_window; // eax

  owner_window = rf_ui_gadget_get_owner_window(a2);
  rf_ui_gadget_initialize(this, owner_window, 2, a3, a4, a5, a6, a7, a9);
  *(_DWORD *)(this + 632) = 0;
  *(_BYTE *)(this + 636) = 0;
  *(_DWORD *)(this + 628) = a8 | 2;
  *(_DWORD *)(this + 908) = -1;
  rf_clock_deadline_set_wrapped_offset((int *)(this + 896), 0);
  *(_DWORD *)(this + 900) = 0;
  *(_DWORD *)(this + 904) = 0;
  *(_DWORD *)(this + 912) = byte_1CF7B64;
  *(_DWORD *)(this + 1076) = 0;
  *(_DWORD *)(this + 1080) = 0;
  *(_DWORD *)(this + 1084) = 0;
  *(_DWORD *)(this + 1088) = 0;
  *(_DWORD *)(this + 1092) = 1;
  *(_DWORD *)(this + 1096) = 255;
  *(_DWORD *)(this + 1100) = this;
  return rf_ui_gadget_set_parent((_DWORD *)this, (int)a2);
}

