// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00478670 rf_geomod_georegion_contains_point
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl(point3f*,region), result AL Boolean; corrected saved phantom ST0 argument and typed two stack pointers; preserves Boolean return. Native reads no incoming x87 value as an
// argument. Native sole caller pushes2/pop8 and tests AL. Shape DWORD0==2: computes Euclidean distance(point,center+16), explicit F32 store, returns1 only ORDERED radius FLOAT+64 >
// distance. Equality/unordered rejected, no squared-radius substitute. Shape4: calls oriented-box helper with FOUR native arguments point,center+16,matrix+28,full dimensions+68;
// helper inversely rotates and uses inclusive half-dimension tests. Other shape values return0. No hardness/ice/directional-byte filter, region-enable state, pointer/finite/radius
// guard here. Return is initialized0 and normalized1 only for admitted shape helper result.
bool __cdecl rf_geomod_georegion_contains_point(const float *point, const void *region)
{
  float v3; // [esp+4h] [ebp-8h]
  bool v4; // [esp+Bh] [ebp-1h]

  v4 = 0;
  if ( *(_DWORD *)region == 2 )
  {
    v3 = rf_vector_distance(point, (const float *)region + 4);
    return *((float *)region + 16) > (double)v3;
  }
  else if ( *(_DWORD *)region == 4 )
  {
    return rf_oriented_box_contains_point(
             point,
             (const float *)region + 4,
             (const float *)region + 7,
             (const float *)region + 17);
  }
  return v4;
}

