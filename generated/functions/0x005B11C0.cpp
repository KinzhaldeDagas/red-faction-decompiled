// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B11C0 rf_ui_gadget_scalar_deleting_destructor_5b11c0
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall gadget receiver,one stack flags DWORD whose low byte is tested,RET4. Always calls gadget base-chain destructorthrough the existing gadget base-chain destructor; if flags&1 scalar-deletes receiver. Returns original receiver even if freed. No vector cookie/count handling,window-specific cleanup,flag clearing or owning-pointer reset. Window child cleanup5B03D0 calls it after child virtual slot0 when raw child BYTE584 is nonzero.
_DWORD *__thiscall rf_ui_gadget_scalar_deleting_destructor_5b11c0(_DWORD *this, char a2)
{
  rf_ui_gadget_destruct_base_chain(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

