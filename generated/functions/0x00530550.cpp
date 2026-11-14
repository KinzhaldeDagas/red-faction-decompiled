// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00530550 rf_geomod_face_allocate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Cdecl pointer to SIX metadataDWORDs. Acquire raw96-byte face through global pool; NO NULL result check. Clear room-owner68 and spatial-owner72, copy sixDWORDs to40..63, clear decal-polygon head76 and corner-ring head64; return face pointer. Plane/bounds0..39, opaque80 and intrusive next links84/88/92 are NOT initialized by this body. Does not append to solid/room/node lists, construct corners, validate metadata or finalize geometry. Pool free-link may remain in first DWORD until later plane initialization.
_DWORD *__cdecl rf_geomod_face_allocate(_DWORD *a1)
{
  _DWORD *raw; // [esp+0h] [ebp-4h]

  raw = rf_geomod_face_pool_allocate_raw(rf_geomod_face_pool_descriptor);
  raw[17] = 0;
  raw[18] = 0;
  raw[10] = *a1;
  raw[11] = a1[1];
  raw[12] = a1[2];
  raw[13] = a1[3];
  raw[14] = a1[4];
  raw[15] = a1[5];
  raw[19] = 0;
  raw[16] = 0;
  return raw;
}

