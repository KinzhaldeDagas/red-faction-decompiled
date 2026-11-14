// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536520 rf_geomod_corner_pool_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Thiscall cornerPool,opaqueDWORD,RET4,return poolEAX. Embedded capacity150000 records of28bytes. H=4200000(401640): H+4=argument; clear headH,spillLiveH+8,freeCountH+12,spillPeakH+16,activePeakH+20,currentActiveH+24, then count150000/head=pool. Link DWORD0 of i0..149998 to next28-byte record and terminate last withNULL. Remaining24bytes per record untouched, no allocation/deletion or old-chain preservation. Disassembler loc_401640/644/654 are receiver-relative numeric OFFSETS, not executable targets or absolute writes.
_DWORD *__thiscall rf_geomod_corner_pool_construct(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  *(_DWORD *)((char *)&loc_401644 + (_DWORD)this) = a2;
  *(_DWORD *)((char *)&loc_401640 + (_DWORD)this) = 0;
  *(this + 1050002) = 0;
  *(this + 1050003) = 0;
  *(this + 1050004) = 0;
  *(this + 1050006) = 0;
  *(_DWORD *)((char *)&loc_401654 + (_DWORD)this) = 0;
  *(this + 1050003) = 150000;
  *(_DWORD *)((char *)&loc_401640 + (_DWORD)this) = this;
  for ( i = 0; i < 149999; ++i )
    *(this + 7 * i) = this + 7 * i + 7;
  *(this + 7 * i) = 0;
  return this;
}

