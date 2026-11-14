// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004712D0 rf_ui_v_checkbox_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall ECX=this. Constructs v_button via470C10, installs v_checkbox vtable, sets checked-overlay bitmapDWORD+68=-1. Returns this. DOES NOT
// initialize checked BYTE+72; relies on static zeroing/caller setup.
_DWORD *__thiscall rf_ui_v_checkbox_construct(_DWORD *this)
{
  rf_ui_v_button_construct(this);
  *this = &v_checkbox::`vftable';
  *(this + 17) = -1;
  return this;
}

