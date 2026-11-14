// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABC40 rf_ui_gadget_set_key_slot
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall gadget,keycode,signed slot index. Writes DWORD at this+588+4*index,returns index. NO index0..1 guard despite matcher only scanning2 slots. Does not normalize code,consume keyboard event or trigger callback.
int __thiscall rf_ui_gadget_set_key_slot(_DWORD *this, int a2, int a3)
{
  *(this + a3 + 147) = a2;
  return a3;
}

