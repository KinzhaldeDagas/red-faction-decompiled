// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EF9F0 rf_ui_button_initialize_in_window
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Arguments owner,x,y,w,h,id,flags,raw base flag. Gadget initializer type2;state DWORD+632=0,label BYTE+636=0,flags+628=input,font+908=-1,deadline+896 offset0,press offsets+900/+904=0,palette+912=0x1CF7B64. Drag metadata DWORDs+1076=0,+1080=0,+1084=0,+1088=0,+1092=1,+1096=255,+1100=this. Does not reset state-image records;returns this.
int __thiscall rf_ui_button_initialize_in_window(
        int this,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        char a9)
{
  rf_ui_gadget_initialize(this, a2, 2, a3, a4, a5, a6, a7, a9);
  *(_DWORD *)(this + 632) = 0;
  *(_BYTE *)(this + 636) = 0;
  *(_DWORD *)(this + 628) = a8;
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
  return this;
}

