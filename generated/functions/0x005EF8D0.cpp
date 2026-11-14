// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EF8D0 rf_ui_button_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls gadget constructor,installs ui_button vtable; invokes existing deadline constructors at+892/+896. Constructs five32-byte image records at+916,+948,+980,+1012,+1044; label BYTE+636=0. Splices highlighted into normal image ring,pressed into highlighted,disabled into pressed via+24 links. Four-state ring is normal->highlighted->pressed->disabled->normal;drag image remains self ring. This constructor does not initialize button flags/state,font,palette or drag counters; initializers do. Returns this.
int __thiscall rf_ui_button_construct(int this)
{
  rf_ui_gadget_construct((char *)this);
  *(_DWORD *)this = &ui_button::`vftable';
  rf_clock_deadline_construct_invalid((int *)(this + 892));
  rf_clock_deadline_construct_invalid((int *)(this + 896));
  rf_ui_state_image_construct((_DWORD *)(this + 916));
  rf_ui_state_image_construct((_DWORD *)(this + 948));
  rf_ui_state_image_construct((_DWORD *)(this + 980));
  rf_ui_state_image_construct((_DWORD *)(this + 1012));
  rf_ui_state_image_construct((_DWORD *)(this + 1044));
  *(_BYTE *)(this + 636) = 0;
  rf_ui_state_image_splice_after((_DWORD *)(this + 948), this + 916);
  rf_ui_state_image_splice_after((_DWORD *)(this + 980), this + 948);
  rf_ui_state_image_splice_after((_DWORD *)(this + 1012), this + 980);
  return this;
}

