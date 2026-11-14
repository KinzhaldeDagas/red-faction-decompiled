// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB1A0 rf_ui_gadget_initialize
// UNREALRED VERIFIED [ui-properties-20261029]: Arguments owner window,gadget type,x,y,width,height,ID,byte option. Calls0x5F1080 with base kind0 and supplied rectangle/ID. Stores owner+604,registers in owner doubly linked gadget chain via this.next+608,this.prev+612,owner head+1200 and sentinel owner+592. Clears child+620,sibling+624,parent+616,then0x5ABA50(this,NULL) prepends to owner root-child chain+1220. Stores option BYTE+584,type DWORD+596,clears two key slots through0x5ABC60,sets DWORD+600=0. No owner null/membership validation,allocation or duplicate-registration guard. Return is key-slot loop result2,not this.
int __thiscall rf_ui_gadget_initialize(int this, int a2, int a3, int a4, int a5, int a6, int a7, int a8, char a9)
{
  int result; // eax

  rf_ui_base_initialize_rect(this, 0, a4, a5, a6, a7, a8);
  *(_DWORD *)(this + 604) = a2;
  *(_DWORD *)(this + 608) = *(_DWORD *)(*(_DWORD *)(this + 604) + 1200);
  *(_DWORD *)(this + 612) = *(_DWORD *)(this + 604) + 592;
  *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 604) + 1200) + 612) = this;
  *(_DWORD *)(*(_DWORD *)(this + 604) + 1200) = this;
  *(_DWORD *)(this + 620) = 0;
  *(_DWORD *)(this + 624) = 0;
  *(_DWORD *)(this + 616) = 0;
  rf_ui_gadget_set_parent((_DWORD *)this, 0);
  *(_BYTE *)(this + 584) = a9;
  *(_DWORD *)(this + 596) = a3;
  result = rf_ui_gadget_clear_two_key_slots((_DWORD *)this);
  *(_DWORD *)(this + 600) = 0;
  return result;
}

