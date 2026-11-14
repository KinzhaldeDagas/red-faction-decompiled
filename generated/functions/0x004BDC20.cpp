// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BDC20 rf_object_blocks_when_dead
// UNREALRED VERIFIED [mission-when-dead-20261013] Returns object != NULL AND common flags at object+0x7C contain 0x00400000. This is NOT a health or combat-dead predicate. Constructor 0x4B7E00 installs the bit on admitted common types; death marking does not clear it. In particular a dying type0 Entity blocks until handle retirement, while a type6 event is a present nonblocking target.
bool __cdecl rf_object_blocks_when_dead(int a1)
{
  return a1 && (*(_DWORD *)(a1 + 124) & 0x400000) != 0;
}

