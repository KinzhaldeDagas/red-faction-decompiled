// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471A50 rf_ui_v_cycle_list_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, UI widget constructor/render/input chains, original keypad selectors and native object layouts and native
// signed/x87/stack/callback ABI): thiscall ECX=this. Constructs base v_control, installs v_cycle_list vtable, initializes16 bitmap handlesDWORD+40+4*i=-1, countDWORD+360=0,
// selectedDWORD+364=0, returns this. Parallel arrays xOffsets104/yOffsets168/widths232/heights296 are not initialized.
_DWORD *__thiscall rf_ui_v_cycle_list_construct(_DWORD *this)
{
  int i; // [esp+4h] [ebp-4h]

  rf_ui_control_construct(this);
  *this = &v_cycle_list::`vftable';
  for ( i = 0; i < 16; ++i )
    *(this + i + 10) = -1;
  *(this + 90) = 0;
  *(this + 91) = 0;
  return this;
}

