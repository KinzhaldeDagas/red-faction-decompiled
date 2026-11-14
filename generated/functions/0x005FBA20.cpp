// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FBA20 rf_scene_two_dword_cursor_construct_zero
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VSFX header/version gates, pool ownership/cursors, FourCC dispatch, normal error cleanup and model postprocessing): Thiscall two-DWORD initializer: receiver0=0,receiver4=0, returns receiver. In VSFX reader used for SELS shared8-byte-reference pool cursor later bound to scene300. Does not allocate/free pool, check count or initialize records. No-op matching local destructor5FBA50; existing library flag retained.
_DWORD *__thiscall rf_scene_two_dword_cursor_construct_zero(_DWORD *this)
{
  *this = 0;
  *(this + 1) = 0;
  return this;
}

