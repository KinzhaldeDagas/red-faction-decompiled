// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BDDE0 rf_projectile_pool_release_to_free_list
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Pool projectile: 50 inline records of788 bytes; trailing header H=0x99E8. H+0 free head,H+4 opaque tag,H+8 heap-block count,H+12 free-list count,H+16 peak heap count,H+20 peak in-use,H+24 in-use. Thiscall(pool,block),RET4. Writes block.firstDWORD=oldHead then head=block, increments free count and decrements in-use, returns pool. Does NOT operator-delete heap spills or run block/member destructor, clear rest of payload, validate membership/alignment/null/double-free, or update peak/heap counters. LIFO recycling; free count may include returned heap blocks and exceed inline capacity.
_DWORD *__thiscall rf_projectile_pool_release_to_free_list(_DWORD *this, _DWORD *a2)
{
  *a2 = *(this + 9850);
  *(this + 9850) = a2;
  ++*(this + 9853);
  --*(this + 9856);
  return this;
}

