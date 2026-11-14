// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00484780 rf_geomod_operation_begin
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl runtime operation100 pointer. Copies cutter id0->0x6FCCD8,position8->0x6FDD0C,matrix20->0x6FF808,flags56->0x6FCCE8,scale60->0x6FCCDC,impact
// normal64->0x6FF4FC,constraint76/88->0x6FDD00/0x6FDD44. Clears scalar0x6FCCEC and DWORD0x6FCCE0. Physical-debris byte=(flags bit1 clear); decal-enable byte0x662830=(flags bit4
// clear). Resolves cutter to0x6FCCF0 with no local NULL rejection; room id4 is not read here. Sets world generated-UV mode4, scale32, default/negativeY/positiveY bitmaps from
// global0x6FC338, or loads ice_ice01.tga(-1,1) if flags0x10. Bitmap setter helpers ignore negative handle according to their own contracts.
// Sets phase0 even if an earlier operation was active, no busy guard or detached-bounds reset. Only EXACT multiplayer mode1 AND authority1 appends100-byte network history then
// broadcasts packet0x29; other authority nonzero values do not take this branch. No terrain mutation occurs until step. Return AX/EAX is incidental last helper/network result, not
// uniform admission status.
__int16 __cdecl rf_geomod_operation_begin(int a1)
{
  __int16 result; // ax
  float v2[3]; // [esp+4h] [ebp-34h] BYREF
  float v3[3]; // [esp+10h] [ebp-28h] BYREF
  float v4[3]; // [esp+1Ch] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+28h] [ebp-10h] BYREF
  int v6; // [esp+34h] [ebp-4h]

  dword_6FCCD8 = *(_DWORD *)a1;
  rf_matrix3_copy(&flt_6FF808, (const float *)(a1 + 20));
  rf_vector_copy(&flt_6FDD0C, copy_result, (const float *)(a1 + 8));
  unk_6FCCE8 = *(_DWORD *)(a1 + 56);
  unk_6FCCEC = 0.0;
  rf_geomod_create_physical_debris = (*(_DWORD *)(a1 + 56) & 1) == 0;
  byte_662830 = (*(_DWORD *)(a1 + 56) & 4) == 0;
  unk_6FCCDC = *(float *)(a1 + 60);
  rf_vector_copy(&flt_6FF4FC, v4, (const float *)(a1 + 64));
  unk_6FCCF0 = rf_geomod_cutter_resolve(dword_6FCCD8);
  rf_vector_copy(&flt_6FDD00, v3, (const float *)(a1 + 76));
  rf_vector_copy(&flt_6FDD44, v2, (const float *)(a1 + 88));
  unk_6FCCE0 = 0;
  rf_generated_uv_set_mode(4);
  rf_generated_uv_set_world_scale(32.0);
  v6 = unk_6FC338;
  if ( (*(_DWORD *)(a1 + 56) & 0x10) != 0 )
    v6 = rf_bitmap_load_with_optional_mipmap_generation("ice_ice01.tga", (void *)0xFFFFFFFF, 1);
  rf_generated_uv_set_default_bitmap_if_nonnegative(v6);
  rf_generated_uv_set_negative_y_bitmap_if_nonnegative(v6);
  result = rf_generated_uv_set_positive_y_bitmap_if_nonnegative(v6);
  rf_geomod_operation_phase = 0;
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    rf_geomod_network_history_append((float *)a1);
    return rf_geomod_broadcast_live_boolean_packet41(a1);
  }
  return result;
}

