// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005363B0 rf_geomod_corner_pool_release_raw
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Thiscall pool,corner RET4 returns poolEAX. Set record.firstDWORD=freeHead4200000, freeHead=record, ++freeCount4200012, --active4200024. Does not change spillLive/peak counters, delete spill blocks, clear attributes/ring links, validate ownership or prevent double release. Both embedded and heap records return to same chain; payload firstDWORD overwritten.
_DWORD *__thiscall rf_geomod_corner_pool_release_raw(_DWORD *this, _DWORD *a2)
{
  *a2 = *(_DWORD *)((char *)&loc_401640 + (_DWORD)this);
  *(_DWORD *)((char *)&loc_401640 + (_DWORD)this) = a2;
  ++*(this + 1050003);
  --*(this + 1050006);
  return this;
}

