// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B0540 rf_ui_window_get_flags
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall returns DWORD at window+584 in EAX,without normalization or side effects. No stack args. Initialize/link caller5AFBE0 currently discards return and tests its own input flags instead.
int __thiscall rf_ui_window_get_flags(_DWORD *this)
{
  return *(this + 146);
}

