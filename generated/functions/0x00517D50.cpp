// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517D50 rf_geomod_face_flags_eligible
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, room destruction/reconstruction,shared-vertex portal-side voting,detail references and intrusive list edge cases,original ECX/stack flow and PE bytes): Thiscall pointer to face metadata40,not wholeface,no stack args. Normalized AL1 iff flagsDWORD0 bits0x8 AND0x4 are BOTH clear; short-circuit onbit8,thenbit4. All other bits ignored. Unlike517CC0 there is NO signed portal WORD12 test; positive portal marker may pass here. No room/spatial owner,plane or material reads,writes orNULLreceiver guard.
bool __thiscall rf_geomod_face_flags_eligible(_DWORD *this)
{
  return (*this & 8) == 0 && (*this & 4) == 0;
}

