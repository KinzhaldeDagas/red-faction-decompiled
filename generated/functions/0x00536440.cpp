// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536440 rf_geomod_face_pool_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Thiscall facePool,opaqueDWORD,RET4,return poolEAX. Embedded capacity30000 records of96bytes. Metadata base H=2880000: H+4=argument; initialize freeHeadH,spillLiveH+8,freeCountH+12,spillPeakH+16,activePeakH+20,currentActiveH+24 to0, then freeCount=30000 and head=pool. Link record i DWORD0 to pool+(i+1)*96 for i0..29998, last DWORD0=NULL. Does not initialize other92bytes of any record, allocate/free heap storage, validate previous live records or set global spill-enable flag. Reinvoking discards any prior free/spill chain.
_DWORD *__thiscall rf_geomod_face_pool_construct(_DWORD *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  *(this + 720001) = a2;
  *(this + 720000) = 0;
  *(this + 720002) = 0;
  *(this + 720003) = 0;
  *(this + 720004) = 0;
  *(this + 720006) = 0;
  *(this + 720005) = 0;
  *(this + 720003) = 30000;
  *(this + 720000) = this;
  for ( i = 0; i < 29999; ++i )
    *(this + 24 * i) = this + 24 * i + 24;
  *(this + 24 * i) = 0;
  return this;
}

