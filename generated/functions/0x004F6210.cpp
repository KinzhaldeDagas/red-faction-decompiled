// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6210 rf_geomod_saved_position_encode_u16
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): Cdecl(bounds-context pointer,world float[3],output WORD[3]); corrected misleading pointer return to void: all8 native callers pass3DWORDs,pop12 and discard EAX. Shared by GeoMod AND object/entity/clutter/trigger/blood snapshots. Bounds minXYZ at context+72,maxXYZ+84. Six native x87 gates reject only ORDERED point<min or point>max; UNORDERED comparisons PASS, so NaN is admitted unlike apparent ordered pseudocode conjunction. Any rejected axis zeros ALL three output words in Z,Y,X order (not per-axis saturation); decoding that tuple yields bounds minimum, not necessarily world origin. On admitted point compute F32 spanX/Y/Z=(max-min), F32 factor=DOUBLE65536/span. Per axis
// load point-min in x87, multiply stored F32 factor, FTOL2SSE BEFORE any final F32 store, write LOW16 to output in X,Y,Z order. No65535 clamp: exact unit bounds point1 converts65536 then wraps to0, same packed value as point0. F32 reciprocal error can alter other-boundary cases; do not assume every upper bound maps identically. Zero spans/NaN/infinity reach division/conversion without explicit guards or defined host recovery policy. Sequential reads/stores, no NULL/overlap validation. Native EAX is quantized-Z residue on success, output pointer on rejection, not success/result pointer.
void __cdecl rf_geomod_saved_position_encode_u16(
        const float *bounds_context,
        const float *world_position,
        unsigned __int16 *packed_position)
{
  float v3; // [esp+0h] [ebp-18h]
  float v4; // [esp+4h] [ebp-14h]
  float v5; // [esp+8h] [ebp-10h]
  float v6; // [esp+Ch] [ebp-Ch]
  float v7; // [esp+10h] [ebp-8h]
  float v8; // [esp+14h] [ebp-4h]

  if ( bounds_context[18] <= (double)*world_position
    && bounds_context[21] >= (double)*world_position
    && bounds_context[19] <= (double)world_position[1]
    && bounds_context[22] >= (double)world_position[1]
    && bounds_context[20] <= (double)world_position[2]
    && bounds_context[23] >= (double)world_position[2] )
  {
    v3 = bounds_context[21] - bounds_context[18];
    v5 = bounds_context[22] - bounds_context[19];
    v6 = bounds_context[23] - bounds_context[20];
    v4 = 65536.0 / v3;
    v7 = 65536.0 / v5;
    v8 = 65536.0 / v6;
    *packed_position = (int)((*world_position - bounds_context[18]) * v4);
    packed_position[1] = (int)((world_position[1] - bounds_context[19]) * v7);
    packed_position[2] = (int)((world_position[2] - bounds_context[20]) * v8);
  }
  else
  {
    packed_position[2] = 0;
    packed_position[1] = 0;
    *packed_position = 0;
  }
}

