// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F2F70 rf_ui_container_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Calls gadget constructor,installs ui_container vtable,mask bitmap888=-1,CPU pixels892=NULL,label BYTE628=0. Flags884,font896,palette900 initialized later;returns this.
int __thiscall rf_ui_container_construct(int this)
{
  rf_ui_gadget_construct((char *)this);
  *(_DWORD *)this = &ui_container::`vftable';
  *(_DWORD *)(this + 888) = -1;
  *(_DWORD *)(this + 892) = 0;
  *(_BYTE *)(this + 628) = 0;
  return this;
}

