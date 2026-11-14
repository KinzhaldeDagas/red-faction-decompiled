// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1920 rf_ui_state_image_splice_after
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This record inserted after argument record in singly-linked circular ring: this.next24=other.next24;other.next24=this. Returns other pointer. No reset,ownership change,validation or existing-ring unlink.
int __thiscall rf_ui_state_image_splice_after(_DWORD *this, int a2)
{
  *(this + 6) = *(_DWORD *)(a2 + 24);
  *(_DWORD *)(a2 + 24) = this;
  return a2;
}

