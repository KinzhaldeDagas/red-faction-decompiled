// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00535F50 rf_geomod_face_query_segment_bounds_overlap
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Thiscall query,boundsMin*,boundsMax*,RET8. Calls56C450(min,max,query+0,query+24,scratchVector) and forwards its AL. Uses supplied AABB literally; NO epsilon expansion here (face bounds are expanded by finalization elsewhere). Scratch vector default constructor does not initialize bytes, output is discarded. Does not inspect face metadata or direction12; uses CURRENT endpoint24 which becomes nearest accepted hit position after535BF0, rather than recomputing original endpoint. Does not write query or caller bounds.
bool __thiscall rf_geomod_face_query_segment_bounds_overlap(float *this, float *a2, float *a3)
{
  float v5[3]; // [esp+4h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v5);
  return rf_segment_intersects_aabb(a2, a3, this, this + 6, v5);
}

