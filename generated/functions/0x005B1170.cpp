// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B1170 rf_ui_window_get_effective_hidden_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall compares generation DWORD588 to current global1CF75DC. Mismatch returnsAL1 regardless of receiver hidden byte. Match delegates base hidden getter BYTE29 without normalization. No disabled/modal/child traversal or writes.
char __thiscall rf_ui_window_get_effective_hidden_byte(_DWORD *this)
{
  if ( *(this + 147) == unk_1CF75DC )
    return rf_ui_base_get_hidden_byte(this);
  else
    return 1;
}

