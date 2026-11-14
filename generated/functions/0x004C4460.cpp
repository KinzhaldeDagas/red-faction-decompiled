// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C4460 rf_geomod_segment_hit_or_liquid_crossing
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Cdecl(start,end,roomPointerAddress,outResult,unusedFifth); verified native caller4C4187 pushes5 args/pop20, body consumes only first4. Queries world segment solid
// hit(start,end,publicMask1,local40). ALWAYS copies local face36 ->out0, fraction4 ->out4, point8 ->out8/12/16 BEFORE testing hit result. Local constructorNOOP; query/backend
// initialize fraction1,faceNULL on miss, but point has no full initialization guarantee, so false return can copy indeterminate/candidate point. Only first20B of output are written;
// no storage beyond those20B is required by this body.
// On solid hit returns true with these values. On miss, dereferences *roomPointerAddress, tests room liquid BYTE388 ANY nonzero, sets signed integer
// H=trunc_toward_zero(room.float12+room.float392+DOUBLE.5) through __ftol2_sse, low EAX; not general floor/round for negative heights. Requires STRICT ORDERED end.y<H AND start.y>H
// (equality/NaN fails). Computes F32t=(start.y-H)/(start.y-end.y), sets faceNULL,fraction=t, and point=F32(start+(start-end)*t) componentwise. Native sign is PLUS start-end, NOT
// usual start+(end-start)*t, so returned point extends backward and its Y is above start for valid downward crossing. Return1. No upward crossing, bounds/finite/overflow or roomNULL
// guard, no room mutation. Fifth caller argument0 ignored; worldSolidNULL guard belongs caller, not here.
bool __cdecl rf_geomod_segment_hit_or_liquid_crossing(
        float *start,
        float *end,
        int roomPointerAddress,
        float *outResult,
        int unusedFifth)
{
  float v6; // [esp+Ch] [ebp-4Ch]
  float v7; // [esp+10h] [ebp-48h]
  float v8; // [esp+14h] [ebp-44h]
  float copy_result[3]; // [esp+18h] [ebp-40h] BYREF
  float v10; // [esp+24h] [ebp-34h]
  int v11; // [esp+28h] [ebp-30h]
  _BYTE v12[4]; // [esp+2Ch] [ebp-2Ch] BYREF
  float v13; // [esp+30h] [ebp-28h]
  float source[8]; // [esp+34h] [ebp-24h] BYREF
  bool into_solid_hit; // [esp+57h] [ebp-1h]

  rf_solid_collision_result_construct_noop((int)v12);
  into_solid_hit = rf_world_segment_query_into_solid_hit(start, (int)end, 1, (int)v12);
  *outResult = source[7];
  outResult[1] = v13;
  rf_vector_copy(outResult + 2, copy_result, source);
  if ( !into_solid_hit )
  {
    if ( *(_BYTE *)(*(_DWORD *)roomPointerAddress + 388) )
    {
      v11 = (int)(*(float *)(*(_DWORD *)roomPointerAddress + 12) + *(float *)(*(_DWORD *)roomPointerAddress + 392) + 0.5);
      if ( end[1] < (double)v11 && start[1] > (double)v11 )
      {
        v10 = (start[1] - (double)v11) / (start[1] - end[1]);
        *outResult = 0.0;
        outResult[1] = v10;
        v8 = (start[2] - end[2]) * v10 + start[2];
        v7 = (start[1] - end[1]) * v10 + start[1];
        v6 = (*start - *end) * v10 + *start;
        rf_vector3_set_components_thiscall(outResult + 2, v6, v7, v8);
        return 1;
      }
    }
  }
  return into_solid_hit;
}

