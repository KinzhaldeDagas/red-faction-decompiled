// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AFB70 rf_ui_window_destruct_members_and_base
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall required window receiver, no stack args, plain RET. Installs UI-window vtable643BDC at receiver0, arms C++ unwind state1, then calls verified5B03D0
// window destroy-or-defer on original receiver. Regardless of whether that delegate performs full child/window cleanup or only marks deferred deletion, this body NEXT destroys
// embedded gadget/base chain at+592 via5AB810, then destroys original base via5F1010. Does not stop merely because deferral was requested. State0 is set before embedded destruction
// and state-1 before final base destruction. PE unwind map65DC58/second chunk: a throw while state1 destroys embedded+592 then original base; state0 destroys original base only. No
// containing-window operator delete, raw deallocation, deferred-bit test, child-loop or NULL guard directly here; actual child teardown is delegated and final EAX is base-destructor
// residue, not a success boolean or returned receiver promise. UI-window vtable and established RF UI destructor chain prove inherited Concurrency call/std::function destructor
// identity and library classification are false.
int __thiscall rf_ui_window_destruct_members_and_base(_DWORD *this)
{
  *this = &ui_window::`vftable';
  rf_ui_window_destroy_or_defer(this);
  rf_ui_gadget_destruct_base_chain(this + 148);
  return rf_ui_base_destruct(this);
}

