// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CEC80 rf_scene_key_set_first_dword
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Thiscall receiver,inputDWORD; stores input at offset0 and returns receiver. No writes beyond4 bytes. Shared by scene key constructors with0 input; generic runtime name did not describe this simple field setter.
_DWORD *__thiscall rf_scene_key_set_first_dword(_DWORD *this, int a2)
{
  *this = a2;
  return this;
}

