// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1150 rf_ui_base_get_kind
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall returns DWORD+8 (base-kind selector set by UI initialization). Generic library name unknown_libname_61 was misleading in these UI call sites. Does not perform RTTI,vtable dispatch,allocation or pointer conversion.
int __thiscall rf_ui_base_get_kind(_DWORD *this)
{
  return *(this + 2);
}

