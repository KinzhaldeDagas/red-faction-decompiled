// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FE40 rf_ui_v_label_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall ECX=this. Constructs base v_control, installs v_label vtable, calls default RGBA constructor on inline+40, sets text bitmap DWORD+44=-1,
// returns this. Does not initialize text offsets/extents or create a bitmap; RGBA default delegate is named no-op in existing database.
_DWORD *__thiscall rf_ui_v_label_construct(_DWORD *this)
{
  rf_ui_control_construct(this);
  *this = &v_label::`vftable';
  rf_rgba8_default_construct_noop(this + 10);
  *(this + 11) = -1;
  return this;
}

