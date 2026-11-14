// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FBF0 rf_ui_control_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): thiscall ECX=this v_control base constructor. Writes v_control vtable+0, parentDWORD+4=0, focusBYTE+8=0, enabled/stateBYTE+9=1, hotkeyDWORD+28=-1, press callbackDWORD+32=0,
// drag callbackDWORD+36=0, logicalX/Y DWORD+12/+16=10000 and width/height DWORD+20/+24=0. Bytes+10..11 are not written. Returns original this; no allocation or inherited object
// traversal.
_DWORD *__thiscall rf_ui_control_construct(_DWORD *this)
{
  *this = &v_control::`vftable';
  *(this + 1) = 0;
  *((_BYTE *)this + 8) = 0;
  *((_BYTE *)this + 9) = 1;
  *(this + 7) = -1;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 3) = 10000;
  *(this + 4) = 10000;
  *(this + 5) = 0;
  *(this + 6) = 0;
  return this;
}

