// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB8D0 rf_ui_gadget_get_raw_flag_byte_584
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Returns raw BYTE at object+584 in AL; does not read disabled+28 or hidden+29. No normalization. Upper EAX bits incidental.
char __thiscall rf_ui_gadget_get_raw_flag_byte_584(_BYTE *this)
{
  return *(this + 584);
}

