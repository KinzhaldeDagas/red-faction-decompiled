// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052EF40 rf_geomod_face_set_portal_marker_one
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): ThiscallmetadataWORDpointer(face+40),plainRET. Store16-bit1 atreceiver+12(faceWORD52),returnEAX1. DoesnotORmetadataflags, allocateportal,linkroomneighborsorchangeadjacentlightmapWORD54. Noargumentorvalidation.
int __thiscall rf_geomod_face_set_portal_marker_one(_WORD *this)
{
  *(this + 6) = 1;
  return 1;
}

