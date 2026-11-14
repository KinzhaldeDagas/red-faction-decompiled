// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471F10 rf_ui_meta_control_construct
// UNREALRED VERIFIED [cutscene-ui-20261028]: Calls base control constructor0x46FBF0, installs RTTI-backed v_meta_control vtable, zeroes32 child pointers at+40..+164 and child count+168. Returns this; does not allocate child controls.
_DWORD *__thiscall rf_ui_meta_control_construct(_DWORD *this)
{
  int i; // [esp+4h] [ebp-4h]

  rf_ui_control_construct(this);
  *this = &v_meta_control::`vftable';
  for ( i = 0; i < 32; ++i )
    *(this + i + 10) = 0;
  *(this + 42) = 0;
  return this;
}

