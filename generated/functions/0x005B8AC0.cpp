// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B8AC0 rf_v3c_asset_base_reset
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Writes name[0]=0 and all19 DWORDs at offsets68..140 to0, returning this. Does not release existing allocations or clear name bytes1..67; leaves extended selected-mesh pointer+144 untouched.
_DWORD *__thiscall rf_v3c_asset_base_reset(_DWORD *this)
{
  *(_BYTE *)this = 0;
  *(this + 17) = 0;
  *(this + 18) = 0;
  *(this + 19) = 0;
  *(this + 20) = 0;
  *(this + 21) = 0;
  *(this + 22) = 0;
  *(this + 23) = 0;
  *(this + 24) = 0;
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  *(this + 32) = 0;
  *(this + 33) = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
  return this;
}

