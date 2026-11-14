// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C5670 rf_geomod_postcut_fragment_update
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original fragment spawn and bounded pool, eight-vertex twelve-triangle layout, fourteen-ray scoring, full room-pointer ABI and native glass branching): 
// Cdecl cutPosition,cutRadius. Computes radiusSquared F32 ONCE before loop. Walk active chunk next0. Only signed bounceCount100<=0 and STRICT ORDERED
// radiusSquared>distanceSquared(cutPosition,chunk.position8) ->age112=lifetime116. Equality/unordered do not admit; negative radius squares to positive. No mesh owner104 exclusion,
// room test, flags/velocity change, recycle/unlink or direct deletion. Reads next after iteration; separate render/expiry path handles actual recycling.
void __cdecl rf_geomod_postcut_fragment_update(float *a1, float a2)
{
  float v2; // [esp+0h] [ebp-8h]
  const float *i; // [esp+4h] [ebp-4h]

  for ( i = (const float *)rf_geomod_impact_chunk_active_head;
        i != (const float *)&rf_geomod_impact_chunk_active_head;
        i = *(const float **)i )
  {
    if ( *((int *)i + 25) <= 0 )
    {
      v2 = a2 * a2;
      if ( v2 > rf_vector_distance_squared(a1, i + 2) )
        *((float *)i + 28) = i[29];
    }
  }
}

