// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517D80 rf_geomod_face_metadata_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, embedded cutter literal geometry,all vertex/index/UV words and registry/procedural accessors,original ECX/stack flow and PE bytes): Thiscall24-byte metadata receiver,no stack args,return receiverEAX. Exactly initialize DWORD0=0x100,DWORD4=0,DWORD8=-1,WORD12=0,WORD14=0xFFFF,DWORD16=-1,DWORD20=0; all24 bytes covered, not whole96-byte face. No calls,allocation,geometry or ownership writes outside thisblock. WORD12 portal marker and WORD14 signed lightmap identifier are distinct halfwords within DWORD12. Embedded cutter53AD10 then writesDWORD8=-1 again before using metadata for every face.
_DWORD *__thiscall rf_geomod_face_metadata_init(_DWORD *this)
{
  *this = 256;
  *(this + 1) = 0;
  *(this + 2) = -1;
  *(this + 4) = -1;
  *(this + 5) = 0;
  *((_WORD *)this + 7) = -1;
  *((_WORD *)this + 6) = 0;
  return this;
}

