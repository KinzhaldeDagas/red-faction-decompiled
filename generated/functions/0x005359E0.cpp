// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005359E0 rf_geomod_face_owner_type1_flag152_clear
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Cdecl face pointer; AL0 on NULL face or NULL face.room68. Otherwise normalized AL1 exactly when owner raw BYTE0==1 AND owner BYTE152==0, else0. Getter4CA7F0 reads only raw first byte; type value2/nonzero is not sufficient. No face flags, spatial owner, material or geometry tests; no writes. Reused by collision, projectile impact and glass callers; this contract does not assign an unproven semantic name to owner BYTE152.
bool __cdecl rf_geomod_face_owner_type1_flag152_clear(int a1)
{
  _BYTE *v2; // [esp+0h] [ebp-4h]

  if ( !a1 )
    return 0;
  v2 = *(_BYTE **)(a1 + 68);
  if ( !v2 )
    return 0;
  return unknown_libname_11(v2) == 1 && !v2[152];
}

