// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00535B40 rf_geomod_face_ray_query_begin
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Thiscall query receiver plus sourceFaceDWORD,start*,direction*,F32scalar,lowBYTEflag; RET20, returns receiverEAX. Store flag at56 and sourceFace at36, copy start0..11 and direction12..23, then compute F32 endpoint24..35=start+direction*scalar through vector helpers. Does not normalize direction or preserve scalar separately. Reset hitFace40=0,distance44=+0,orientationBYTE48=0,coplanarBYTE49=0,candidateCount52=0. Padding50/51 and57..59 is untouched. No finite/length/NULL input checks. Accumulator535BF0 subsequently overwrites endpoint24 with accepted hit position, so later bounds tests use that shortened current endpoint.
int __thiscall rf_geomod_face_ray_query_begin(int this, int a2, float *source, float *a4, float scalar, char a6)
{
  float *v6; // eax
  float *v7; // eax
  float v10[3]; // [esp+8h] [ebp-3Ch] BYREF
  float sum_result[3]; // [esp+14h] [ebp-30h] BYREF
  float scaled_result[3]; // [esp+20h] [ebp-24h] BYREF
  float v13[3]; // [esp+2Ch] [ebp-18h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-Ch] BYREF

  *(_BYTE *)(this + 56) = a6;
  *(_DWORD *)(this + 36) = a2;
  rf_vector_copy((float *)this, copy_result, source);
  rf_vector_copy((float *)(this + 12), v13, a4);
  v6 = rf_vector_multiply_scalar((const float *)(this + 12), scaled_result, scalar);
  v7 = rf_vector_add((const float *)this, sum_result, v6);
  rf_vector_copy((float *)(this + 24), v10, v7);
  *(_DWORD *)(this + 40) = 0;
  *(float *)(this + 44) = 0.0;
  *(_BYTE *)(this + 48) = 0;
  *(_BYTE *)(this + 49) = 0;
  *(_DWORD *)(this + 52) = 0;
  return this;
}

