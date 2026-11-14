// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F0140 rf_ui_button_get_label_buffer
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Returns borrowed mutable pointer this+636 to inline label. No copy or length check.
char *__thiscall rf_ui_button_get_label_buffer(char *this)
{
  return this + 636;
}

