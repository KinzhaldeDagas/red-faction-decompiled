// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB7F0 rf_ui_gadget_construct
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall delegates0x5F0FC0 base constructor,installs ui_gadget vtable,returns this. Does not initialize owner,parent,child or sibling fields here;gadget initialization0x5AB1A0 supplies those.
char *__thiscall rf_ui_gadget_construct(char *this)
{
  rf_ui_base_construct(this);
  *(_DWORD *)this = &ui_gadget::`vftable';
  return this;
}

