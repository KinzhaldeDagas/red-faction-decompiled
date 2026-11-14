// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004715E0 rf_ui_v_slider_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall ECX=this. Constructs base v_control, installs v_slider vtable, initializes selected handleDWORD+60 and normal handle+56 to-1, returns this.
// Does not initialize orientationBYTE40, handle dimensions44/48, current float52 or bounds64/68.
_DWORD *__thiscall rf_ui_v_slider_construct(_DWORD *this)
{
  rf_ui_control_construct(this);
  *this = &v_slider::`vftable';
  *(this + 15) = -1;
  *(this + 14) = -1;
  return this;
}

