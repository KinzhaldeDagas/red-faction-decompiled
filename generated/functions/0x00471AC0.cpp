// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471AC0 rf_ui_cycle_list_set_geometry
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall(parent,x,y,width,height), RET20. Stores parent+4, X/Y+12/+16, logicalWH+20/+24. Does not reset count/selection, recompute existing text
// centering, allocate/release images or change callbacks/state. EAX incidentally contains height.
int __thiscall rf_ui_cycle_list_set_geometry(_DWORD *this, int a2, int a3, int a4, int a5, int a6)
{
  *(this + 1) = a2;
  *(this + 3) = a3;
  *(this + 4) = a4;
  *(this + 5) = a5;
  *(this + 6) = a6;
  return a6;
}

