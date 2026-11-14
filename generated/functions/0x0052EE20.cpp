// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052EE20 rf_geomod_face_boolean_class_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): ThiscallmetadataDWORDpointer(face+40),plainRET. Return(*flags&0x70000000)>>28, range0..7;notclampedtooperationtableclass0..4. No facepointeroffsetinsidehelper,nootherfieldreadsorwrites.
unsigned int __thiscall rf_geomod_face_boolean_class_get(_DWORD *this)
{
  return (*this & 0x70000000u) >> 28;
}

