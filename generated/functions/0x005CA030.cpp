// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CA030 rf_scene_definition_construct_empty_pools
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Selectively initializes scene definition header/pools: DWORD68=0;counts at76,84,92,100,108,116,124,132=0;pointer128=0;all DWORDs72..300 zero (including those counts),and clears ONLY bit0 in flags304,preserving other flag bits. Bytes0..67 and flags otherbits are untouched. Returns receiver; does not release old allocations before zeroing. Observed writes define at least308-byte object,not a fully-zeroed C++ object.
_DWORD *__thiscall rf_scene_definition_construct_empty_pools(_DWORD *this)
{
  *(this + 17) = 0;
  *(this + 76) &= ~1u;
  *(this + 19) = 0;
  *(this + 21) = 0;
  *(this + 23) = 0;
  *(this + 33) = 0;
  *(this + 25) = 0;
  *(this + 27) = 0;
  *(this + 29) = 0;
  *(this + 31) = 0;
  *(this + 32) = 0;
  *(this + 18) = 0;
  *(this + 20) = 0;
  *(this + 22) = 0;
  *(this + 24) = 0;
  *(this + 26) = 0;
  *(this + 28) = 0;
  *(this + 30) = 0;
  *(this + 34) = 0;
  *(this + 35) = 0;
  *(this + 36) = 0;
  *(this + 37) = 0;
  *(this + 38) = 0;
  *(this + 39) = 0;
  *(this + 40) = 0;
  *(this + 41) = 0;
  *(this + 42) = 0;
  *(this + 43) = 0;
  *(this + 44) = 0;
  *(this + 45) = 0;
  *(this + 46) = 0;
  *(this + 47) = 0;
  *(this + 48) = 0;
  *(this + 49) = 0;
  *(this + 50) = 0;
  *(this + 51) = 0;
  *(this + 52) = 0;
  *(this + 53) = 0;
  *(this + 54) = 0;
  *(this + 55) = 0;
  *(this + 56) = 0;
  *(this + 57) = 0;
  *(this + 58) = 0;
  *(this + 59) = 0;
  *(this + 60) = 0;
  *(this + 61) = 0;
  *(this + 62) = 0;
  *(this + 63) = 0;
  *(this + 64) = 0;
  *(this + 65) = 0;
  *(this + 66) = 0;
  *(this + 67) = 0;
  *(this + 68) = 0;
  *(this + 69) = 0;
  *(this + 70) = 0;
  *(this + 71) = 0;
  *(this + 72) = 0;
  *(this + 73) = 0;
  *(this + 74) = 0;
  *(this + 75) = 0;
  return this;
}

