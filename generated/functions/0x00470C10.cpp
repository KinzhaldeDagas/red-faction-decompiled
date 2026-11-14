// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00470C10 rf_ui_v_button_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): thiscall ECX=this. Calls v_control constructor46FBF0, replaces vtable with v_button, initializes DWORDs+40/+44/+48 to-1, and returns this. No derived texture loads/label
// construction or further field initialization; field meanings beyond these native writes are not asserted.
_DWORD *__thiscall rf_ui_v_button_construct(_DWORD *this)
{
  rf_ui_control_construct(this);
  *this = &v_button::`vftable';
  *(this + 10) = -1;
  *(this + 11) = -1;
  *(this + 12) = -1;
  return this;
}

