// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00521910 rf_impact_decal_world_submit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, plane splits,intrusive face lists,room/portal visibility,clip apertures and decal submission,original ECX/stack flow and PE bytes): Cdecl input impact descriptor. Take maximum raw floats48,52,56 via ordered two-value max helper; multiply PE double0.8660249710083008 and roundF32. Build cube bounds positionXYZ0 plus/minus that scalar; no orientation rotation or per-axis size here. Scan context pointer80 array180 in order; for each candidate record test inclusive AABB overlap at8/20. If owner descriptor64 equals endpointDWORD0 choose endpoint4, else if equals endpoint4 choose endpoint0; FIRST overlap+owner match stops search, not nearest or all owners. Secondaryowner remains0 if no match. Call521AF0 EXACTLY ONCE
// with(context80,primaryowner64,secondaryowner,position0,orientation12,dimensions48,bitmap60,alphaBYTE68,flagsDWORD72,extra-1,scalar84), return allocated-decal pointer orNULL unchanged. Descriptor fields are source layout, distinct from projected record offsets. Wrapper does not allocate impact descriptor, mutate its fields or check capacity; called projection routine handles admission/eviction. Bound factor is on raw dimension values; prior half-extent wording is replaced to avoid an extra factor-of-two interpretation.
_DWORD *__cdecl rf_impact_decal_world_submit(int a1)
{
  int first_dword; // eax
  int v2; // eax
  float *v4; // [esp-4h] [ebp-34h]
  int v5[3]; // [esp+8h] [ebp-28h] BYREF
  float v6; // [esp+14h] [ebp-1Ch]
  int v7; // [esp+18h] [ebp-18h]
  int v8[3]; // [esp+20h] [ebp-10h] BYREF
  int i; // [esp+2Ch] [ebp-4h]

  v6 = rf_float_maximum_two_values(*(float *)(a1 + 48), *(float *)(a1 + 52));
  v6 = rf_float_maximum_two_values(v6, *(float *)(a1 + 56));
  v6 = v6 * 0.8660249710083008;
  rf_vector3_add_scalar_to_components((float *)a1, (float *)v8, v6);
  rf_vector3_subtract_scalar_from_components((float *)a1, (float *)v5, v6);
  v7 = 0;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((void *)(*(_DWORD *)(a1 + 80) + 180));
    if ( i >= first_dword )
      break;
    v4 = (float *)(*(_DWORD *)sub_552200((_DWORD *)(*(_DWORD *)(a1 + 80) + 180), i) + 20);
    v2 = sub_552200((_DWORD *)(*(_DWORD *)(a1 + 80) + 180), i);
    if ( rf_aabb_overlap_inclusive((float *)(*(_DWORD *)v2 + 8), v4, (float *)v5, (float *)v8) )
    {
      if ( *(_DWORD *)(a1 + 64) == **(_DWORD **)sub_552200((_DWORD *)(*(_DWORD *)(a1 + 80) + 180), i) )
      {
        v7 = *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(*(_DWORD *)(a1 + 80) + 180), i) + 4);
        return rf_world_decal_create_volume_and_project(
                 *(_DWORD *)(a1 + 80),
                 *(_DWORD *)(a1 + 64),
                 v7,
                 a1,
                 a1 + 12,
                 (float *)(a1 + 48),
                 *(_DWORD *)(a1 + 60),
                 *(_BYTE *)(a1 + 68),
                 *(_DWORD *)(a1 + 72),
                 -1,
                 *(float *)(a1 + 84));
      }
      if ( *(_DWORD *)(a1 + 64) == *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(*(_DWORD *)(a1 + 80) + 180), i) + 4) )
      {
        v7 = **(_DWORD **)sub_552200((_DWORD *)(*(_DWORD *)(a1 + 80) + 180), i);
        return rf_world_decal_create_volume_and_project(
                 *(_DWORD *)(a1 + 80),
                 *(_DWORD *)(a1 + 64),
                 v7,
                 a1,
                 a1 + 12,
                 (float *)(a1 + 48),
                 *(_DWORD *)(a1 + 60),
                 *(_BYTE *)(a1 + 68),
                 *(_DWORD *)(a1 + 72),
                 -1,
                 *(float *)(a1 + 84));
      }
    }
  }
  return rf_world_decal_create_volume_and_project(
           *(_DWORD *)(a1 + 80),
           *(_DWORD *)(a1 + 64),
           v7,
           a1,
           a1 + 12,
           (float *)(a1 + 48),
           *(_DWORD *)(a1 + 60),
           *(_BYTE *)(a1 + 68),
           *(_DWORD *)(a1 + 72),
           -1,
           *(float *)(a1 + 84));
}

