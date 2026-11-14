// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E520 rf_bitset_fill_all_storage_bytes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Thiscall(receiver,valueByte),memset(backing,valueByte!=0?FF:00,storedByteCount),returns backing pointer from memset. Includes all padding bits in rounded final byte. No ownership,logical bit count or NULL validation;does not allocate.
void *__thiscall rf_bitset_fill_all_storage_bytes(int this, char a2)
{
  return memset(*(void **)this, (unsigned __int8)-(a2 != 0), *(_DWORD *)(this + 4));
}

