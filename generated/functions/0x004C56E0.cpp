// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C56E0 rf_face_metadata_has_flag8
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX face-metadata pointer; returns byte boolean whether DWORD0 bit0x8 is set. No other flag/room/polygon checks; used by51A760 incident-face classification during optional clone vertex welding.
bool __thiscall rf_face_metadata_has_flag8(_DWORD *this)
{
  return (*this & 8) != 0;
}

