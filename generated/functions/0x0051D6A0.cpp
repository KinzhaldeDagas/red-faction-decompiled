// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051D6A0 rf_geomod_face_uv_area_density_scale
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mass sampling and inverse inertia,recentering,UV cuts and density,finite epsilon tests,original ECX/stack flow and PE bytes): Recovered original code51D6A0..51D86F, cdecl face pointer plainRET, x87 float-rounded result. Use first face corner64 as fan anchor; begin third corner and walk to last. For each fan triangle compute three primaryUV(+4/+8) edge distances via51D870, storeF32, semiperimeterF32, Heron productF32; clamp ORDERED negative product to0, unordered remainsNaN; add sqrt(product) toF32 UVarea. Get physical face area via rf_geomod_face_area, roundF32. If ORDERED area>0 return sqrt(F32(UVarea/area)), otherwise0 (NaN area returns0). No signed UV orientation or overlapping-fan correction; concave fan can overcount. Empty/one-corner loop dereferences NULL next during initial fan setup; no validation. Correct x87
// return of51D870 is essential; old void declaration created phantom x87 operands in this caller. No baseline code xrefs to this range.
double __cdecl rf_geomod_face_uv_area_density_scale(void *face)
{
  float v2; // [esp+10h] [ebp-34h]
  int v3; // [esp+14h] [ebp-30h]
  int v4; // [esp+18h] [ebp-2Ch]
  int v5; // [esp+1Ch] [ebp-28h]
  float v6; // [esp+20h] [ebp-24h]
  float v7; // [esp+24h] [ebp-20h]
  float v8; // [esp+28h] [ebp-1Ch]
  float v9; // [esp+2Ch] [ebp-18h]
  float v10; // [esp+30h] [ebp-14h]
  int i; // [esp+34h] [ebp-10h]
  float v12; // [esp+38h] [ebp-Ch]
  float v13; // [esp+3Ch] [ebp-8h]
  int v14; // [esp+40h] [ebp-4h]

  v13 = 0.0;
  v14 = *((_DWORD *)face + 16);
  if ( *(_DWORD *)(v14 + 20) == v14 )
    v5 = 0;
  else
    v5 = *(_DWORD *)(v14 + 20);
  if ( *(_DWORD *)(v5 + 20) == *((_DWORD *)face + 16) )
    v4 = 0;
  else
    v4 = *(_DWORD *)(v5 + 20);
  for ( i = v4; i; i = v3 )
  {
    v10 = rf_uv_distance_xyxy(
            *(float *)(v14 + 4),
            *(float *)(v14 + 8),
            *(float *)(*(_DWORD *)(i + 24) + 4),
            *(float *)(*(_DWORD *)(i + 24) + 8));
    v8 = rf_uv_distance_xyxy(*(float *)(v14 + 4), *(float *)(v14 + 8), *(float *)(i + 4), *(float *)(i + 8));
    v6 = rf_uv_distance_xyxy(
           *(float *)(i + 4),
           *(float *)(i + 8),
           *(float *)(*(_DWORD *)(i + 24) + 4),
           *(float *)(*(_DWORD *)(i + 24) + 8));
    v9 = (v10 + v8 + v6) / 2.0;
    v7 = (v9 - v10) * v9 * (v9 - v8) * (v9 - v6);
    if ( v7 < 0.0 )
      v7 = 0.0;
    v13 = rf_sqrt_float(v7) + v13;
    if ( *(_DWORD *)(i + 20) == *((_DWORD *)face + 16) )
      v3 = 0;
    else
      v3 = *(_DWORD *)(i + 20);
  }
  v12 = rf_geomod_face_area(face);
  if ( v12 <= 0.0 )
    return 0.0;
  v2 = v13 / v12;
  return rf_sqrt_float(v2);
}

