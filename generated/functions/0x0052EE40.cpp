// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052EE40 rf_geomod_face_operand_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): ThiscallmetadataDWORDpointer(face+40),plainRET;normalizedEAX0/1 basedmask0x00800000 (bit23). IDA rendersimmediateasoffsetunk_800000;this isMASK,nopointerdereference. Operand0world/1cutterlabelssetbystage0. Otherbitsunchanged.
BOOL __thiscall rf_geomod_face_operand_get(_DWORD *this)
{
  return ((unsigned int)&unk_800000 & *this) != 0;
}

