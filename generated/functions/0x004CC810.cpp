// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CC810 rf_particle_cross_face_portal
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Cdecl (particle120, face), AL success. Reads signed16 portal index from face metadata +12 (face+52). Negative index returns 0. Otherwise indexes portal pointer array at cached
// particle-world 0x8377D8 +180 without local bounds/null checks. Portal DWORD endpoints +0/+4 are compared with particle room +100; matching first writes second, otherwise matching
// second writes first, otherwise returns 0. First match wins when endpoints coincide; may return 1 without changing room. Does not resolve rf_world_solid, test room visibility, or
// relink any ownership list/bucket.
char __cdecl rf_particle_cross_face_portal(int a1, int a2)
{
  _DWORD *v3; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  v4 = rf_face_metadata_portal_index_signed16((__int16 *)(a2 + 40));
  if ( v4 <= -1 )
    return 0;
  v3 = *(_DWORD **)sub_552200((_DWORD *)(unk_8377D8 + 180), v4);
  if ( *v3 == *(_DWORD *)(a1 + 100) )
  {
    *(_DWORD *)(a1 + 100) = v3[1];
  }
  else
  {
    if ( v3[1] != *(_DWORD *)(a1 + 100) )
      return 0;
    *(_DWORD *)(a1 + 100) = *v3;
  }
  return 1;
}

