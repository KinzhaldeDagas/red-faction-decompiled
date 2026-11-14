// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F2FC0 rf_ui_container_initialize
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Arguments owner,x,y,w,h,id,flags,unused finalDWORD;callee pops32. Initializes gadget type1,passing CURRENT raw BYTE584 as final base flag rather than supplied final argument. Stores flags884,label empty628,font896=-1,palette900=0x1CF7C00. Does not reset existing mask888/pixels892 or release prior mask. Returns this;no extent guard.
int __thiscall rf_ui_container_initialize(int this, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
  rf_ui_gadget_initialize(this, a2, 1, a3, a4, a5, a6, a7, *(_BYTE *)(this + 584));
  *(_DWORD *)(this + 884) = a8;
  *(_BYTE *)(this + 628) = 0;
  *(_DWORD *)(this + 896) = -1;
  *(_DWORD *)(this + 900) = byte_1CF7C00;
  return this;
}

