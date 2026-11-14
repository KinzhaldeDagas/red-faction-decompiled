// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A96A0 rf_ui_scrollbar_construct
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall scrollbar. Delegates base constructor0x5EE4C0,installs ui_scrollbar vtable,returns this. Does not initialize dimensions,range or child buttons explicitly in this body; creation helper performs later setup.
_DWORD *__thiscall rf_ui_scrollbar_construct(_DWORD *this)
{
  rf_ui_slider_construct(this);
  *this = &ui_scrollbar::`vftable';
  return this;
}

