// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C55F0 rf_geomod_segment_subtract_hit_fraction_or_fallback
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Cdecl(start,end,roomValue,fallbackAmount,inoutFloat). Reserves20B local result storage and calls NOOP intersection constructor, calls4C4460(start,end,&localRoomValue,hit,0) with
// FIVE arguments/pop20. Only AL exactly1 admits hit branch. If hit.face nonnull AND face metadata at+40 does NOT have flag8, subtracts hit FRACTION4 from *inoutFloat. Otherwise
// (liquid faceNULL, flag8 face, or miss/non1) subtracts fallbackAmount. Fraction is not multiplied by length or fallback; no output clamp/normalization or room propagation. Point
// copied by helper is unused here. EAX/AL incidental query result or output pointer bits on hit, not normalized collision status; no pointer/finite validation.
char __cdecl rf_geomod_segment_subtract_hit_fraction_or_fallback(float *start, float *end, int a3, float a4, float *a5)
{
  char result; // al
  float outResult[5]; // [esp+0h] [ebp-14h] BYREF

  rf_geomod_intersection24_construct_noop((char *)outResult);
  result = rf_geomod_segment_hit_or_liquid_crossing(start, end, (int)&a3, outResult, 0);
  if ( result == 1 )
  {
    if ( LODWORD(outResult[0]) && !rf_face_metadata_has_flag8((_DWORD *)(LODWORD(outResult[0]) + 40)) )
    {
      result = (char)a5;
      *a5 = *a5 - outResult[1];
    }
    else
    {
      result = (char)a5;
      *a5 = *a5 - a4;
    }
  }
  else
  {
    *a5 = *a5 - a4;
  }
  return result;
}

