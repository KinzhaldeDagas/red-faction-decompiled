// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471A30 rf_ui_slider_value_get
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): ECX slider. Load floatDWORD52 to x87 ST0,return unchanged;no clamp,normalization,ratio/dimension arithmetic,state
// guard or side effects. Stored existing double-return prototype uses native x87 float-value ABI;data field itself is binary32. No integer EAX result promise.
double __thiscall rf_ui_slider_value_get(float *this)
{
  return *(this + 13);
}

