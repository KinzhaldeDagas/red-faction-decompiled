// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046F930 rf_ui_button_construct_wrapper
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): thiscall ECX=this wrapper: calls470C10 on same object and returns original this in EAX. Native callee constructs base v_control via46FBF0, installs v_button vtable, sets
// DWORDs+40/+44/+48=-1. Wrapper performs no further initialization. Existing stored type retained.
_DWORD *__thiscall rf_ui_button_construct_wrapper(_DWORD *this)
{
  rf_ui_v_button_construct(this);
  return this;
}

