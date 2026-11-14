// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528CC0 rf_light_get_active_entry_position_range_rgb_category
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): Cdecl activeIndex,outXYZ,UNUSED thirdDWORD,outRange,outR,outG,outB,outCategoryBYTE; eight stack args, plainRET. Load record pointer from global active array[index] WITHOUT activecount/validity/type checks. Copy originalpos12 if DWORD18CD388zero, alternatepos92 ifnonzero. Then write range60,R64,G68,B72 and raw categoryBYTE77 in that order. Return same rawcategory throughAL. Third argument never read; no light-type, direction/tube second-endpoint or inner-range output. No snapshot/alias/thread guards; each field read re-fetches activearray[index]. Does not invalidate/advance selection or write other record fields.
char __cdecl rf_light_get_active_entry_position_range_rgb_category(
        int a1,
        float *destination,
        int a3,
        float *a4,
        float *a5,
        float *a6,
        float *a7,
        _BYTE *a8)
{
  char result; // al
  float v9[3]; // [esp+0h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-Ch] BYREF

  if ( unk_18CD388 )
    rf_vector_copy(destination, v9, (const float *)(rf_light_active_world_records[a1] + 92));
  else
    rf_vector_copy(destination, copy_result, (const float *)(rf_light_active_world_records[a1] + 12));
  *a4 = *(float *)(rf_light_active_world_records[a1] + 60);
  *a5 = *(float *)(rf_light_active_world_records[a1] + 64);
  *a6 = *(float *)(rf_light_active_world_records[a1] + 68);
  *a7 = *(float *)(rf_light_active_world_records[a1] + 72);
  result = *(_BYTE *)(rf_light_active_world_records[a1] + 77);
  *a8 = result;
  return result;
}

