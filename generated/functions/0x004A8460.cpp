// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A8460 rf_replication_get_entity_motion_snapshot
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): cdecl(entity,outPosition,outVectorA,outVectorB,outAnglesA,outAnglesB,outTimestampWORD), seven args. If entity.motion632==NULL leaves ALL outputs
// untouched. Local entity681E38: copies native vectors from offsets60,324,1812,2172,2148 respectively and stores LOW16 performanceClock(1000). Other entity: n=motion DWORD1332; uses
// unchecked index(n-1) for parallel vector arrays at buffer0,720,960,480,240, each stride12, and WORD timestamp from buffer1278+2*n (=1280+2*(n-1)). No n>0/capacity guard;
// zero/negative n indexes preceding entries. Copy helpers use destination ECX and an additional return-object scratch argument; these are actual data copies, not extra logical
// vectors. Return register incidental.
_WORD *__cdecl rf_replication_get_entity_motion_snapshot(
        int a1,
        float *destination,
        float *a3,
        float *a4,
        float *a5,
        float *a6,
        _WORD *a7)
{
  _WORD *result; // eax
  float v8[3]; // [esp+0h] [ebp-7Ch] BYREF
  float v9[3]; // [esp+Ch] [ebp-70h] BYREF
  float v10[3]; // [esp+18h] [ebp-64h] BYREF
  float v11[3]; // [esp+24h] [ebp-58h] BYREF
  float v12[3]; // [esp+30h] [ebp-4Ch] BYREF
  float v13[3]; // [esp+3Ch] [ebp-40h] BYREF
  float v14[3]; // [esp+48h] [ebp-34h] BYREF
  float v15[3]; // [esp+54h] [ebp-28h] BYREF
  float v16[3]; // [esp+60h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+6Ch] [ebp-10h] BYREF
  int v18; // [esp+78h] [ebp-4h]

  result = (_WORD *)a1;
  if ( *(_DWORD *)(a1 + 632) )
  {
    if ( a1 == dword_681E38 )
    {
      rf_vector_copy(destination, v12, (const float *)(a1 + 60));
      rf_vector_copy(a3, v11, (const float *)(a1 + 324));
      rf_vector_copy(a4, v10, (const float *)(a1 + 1812));
      rf_vector_copy(a5, v9, (const float *)(a1 + 2172));
      rf_vector_copy(a6, v8, (const float *)(a1 + 2148));
      result = (_WORD *)(unsigned __int16)rf_performance_clock_elapsed_scaled(1000);
      *a7 = (_WORD)result;
    }
    else
    {
      v18 = *(_DWORD *)(*(_DWORD *)(a1 + 632) + 1332);
      rf_vector_copy(destination, copy_result, (const float *)(*(_DWORD *)(a1 + 632) + 12 * (v18 - 1)));
      rf_vector_copy(a3, v16, (const float *)(*(_DWORD *)(a1 + 632) + 12 * (v18 - 1) + 720));
      rf_vector_copy(a4, v15, (const float *)(*(_DWORD *)(a1 + 632) + 12 * (v18 - 1) + 960));
      rf_vector_copy(a5, v14, (const float *)(*(_DWORD *)(a1 + 632) + 12 * (v18 - 1) + 480));
      rf_vector_copy(a6, v13, (const float *)(*(_DWORD *)(a1 + 632) + 12 * (v18 - 1) + 240));
      *a7 = *(_WORD *)(*(_DWORD *)(a1 + 632) + 2 * v18 + 1278);
      return a7;
    }
  }
  return result;
}

