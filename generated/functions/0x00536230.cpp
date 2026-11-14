// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00536230 rf_geomod_face_pool_release_raw
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Thiscall facePool,record,RET4,return poolEAX. Overwrite record DWORD0 with freeHead at pool+2880000(2BF200), set freeHead=record, increment freeCount at+2880012 and decrement currentActive at+2880024. No pointer/range/double-free or counter bounds checks. Embedded and spill records both go to same chain; no operator delete, spillLive+2880008 adjustment or peak reset. Does not unlink face ownership/corners, release vertices, or clear the remaining92 record bytes; only first FOUR record bytes are overwritten.
_DWORD *__thiscall rf_geomod_face_pool_release_raw(_DWORD *this, _DWORD *a2)
{
  *a2 = *(this + 720000);
  *(this + 720000) = a2;
  ++*(this + 720003);
  --*(this + 720006);
  return this;
}

