// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00535B10 rf_geomod_face_clear_decal_polygon_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Thiscall face plainRET returns same receiver EAX. Write DWORD76=0 and AND metadataDWORD40 with0xFFCFFFFF, clearing ONLY bits20/21 (0x100000/0x200000). No traversal, polygon release, node/room unlink or update of spatial-owner72. Called after decal polygon replacement/removal, even when protected owner0x400 polygons were skipped. Prior spatial-leaf wording corrected.
_DWORD *__thiscall rf_geomod_face_clear_decal_polygon_state(_DWORD *this)
{
  *(this + 19) = 0;
  *(this + 10) &= 0xFFCFFFFF;
  return this;
}

