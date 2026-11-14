// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00535F90 rf_geomod_face_ray_query_class_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Thiscall query, no stack args. If hitFaceDWORD40==0 returnEAX2 regardless of flag bytes. Otherwise coplanarBYTE49 nonzero selects class4 when orientationBYTE48 nonzero, class3 when zero; with coplanar0 return class1 for orientation nonzero, class2 for zero. Tests arbitrary nonzero bytes, not exact1. Read-only, does not consult distance44,source36,count52 or flag56 and performs no hit validation.
int __thiscall rf_geomod_face_ray_query_class_get(int this)
{
  if ( !*(_DWORD *)(this + 40) )
    return 2;
  if ( *(_BYTE *)(this + 49) )
  {
    if ( *(_BYTE *)(this + 48) )
      return 4;
    else
      return 3;
  }
  else if ( *(_BYTE *)(this + 48) )
  {
    return 1;
  }
  else
  {
    return 2;
  }
}

