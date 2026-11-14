// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413790 rf_two_dword_construct_zero_413790
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VSFX header/version gates, pool ownership/cursors, FourCC dispatch, normal error cleanup and model postprocessing): Thiscall two-DWORD initializer, sets receiver0 and4 to0, returns receiver. Used as empty counter/pool cursor pairs by VSFX loader among other callers; no allocation, links, vtable or full containing-object initialization. Prior generic library label replaced with observed behavior; library flag retained.
_DWORD *__thiscall rf_two_dword_construct_zero_413790(_DWORD *this)
{
  *this = 0;
  *(this + 1) = 0;
  return this;
}

