// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517CC0 rf_geomod_terrain_component_face_eligible
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shared-edge insertion,component classification/extraction,finite epsilon tests,original ECX/stack flow and PE bytes): Thiscall receiver points to face metadata at byte40, not whole face. Return bool true iff receiver DWORD0 bits8 and4 are BOTH clear and SIGNED WORD12<=0 (face portal marker byte52). Bit tests short-circuit; negative and zero marker admitted, positive rejected. No room, label, normal or shell check.
bool __thiscall rf_geomod_terrain_component_face_eligible(__int16 *this)
{
  return (*(_DWORD *)this & 8) == 0 && (*(_DWORD *)this & 4) == 0 && *(this + 6) <= 0;
}

