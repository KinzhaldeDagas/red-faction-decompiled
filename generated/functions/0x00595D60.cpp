// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00595D60 rf_scene_point_track_update_pool_record
// UNREALRED VERIFIED [transfer-scene-20261028]: Runtime pointer in ECX; logical stack inputs fractional sample,optional offset vector,optional3x3 rotation. If signed runtime flags DWORD+8 negative, does nothing. Else interpolates0x595E80, optionally replaces stored offset+24, copies position+12, optionally rotates that copy, then adds stored offset. For signed pool index+56>=0, writes position to pool+20, runtime scalar+52 to pool+68, scalar+36 to pool+44 and scalars+40,+44,+48 to pool+32,+36,+40. No pool upper-bound or active-sentinel check. Rotation affects pool output position, not the stored interpolated position. Return is incidental helper/offset result.
int __fastcall rf_scene_point_track_update_pool_record(int a1, int a2, float a3, float *source, float *a5)
{
  int result; // eax
  float v7[3]; // [esp+8h] [ebp-24h] BYREF
  float copy_result[3]; // [esp+14h] [ebp-18h] BYREF
  float v9[3]; // [esp+20h] [ebp-Ch] BYREF

  result = a1;
  if ( *(int *)(a1 + 8) >= 0 )
  {
    rf_scene_point_track_interpolate_sample((float *)a1, a3);
    if ( source )
      rf_vector_copy((float *)(a1 + 24), copy_result, source);
    rf_vector3_copy_return_destination(v9, (float *)(a1 + 12));
    if ( a5 )
      rf_vector_rotate_by_matrix3(v9, a5);
    result = (int)rf_vector_accumulate(v9, (float *)(a1 + 24));
    if ( *(int *)(a1 + 56) >= 0 )
    {
      rf_vector_copy((float *)&unk_1BC2174 + 35 * *(_DWORD *)(a1 + 56), v7, v9);
      unk_1BC21A4[35 * *(_DWORD *)(a1 + 56)] = *(float *)(a1 + 52);
      *((float *)&unk_1BC218C + 35 * *(_DWORD *)(a1 + 56)) = *(float *)(a1 + 36);
      *((float *)&unk_1BC2180 + 35 * *(_DWORD *)(a1 + 56)) = *(float *)(a1 + 40);
      *((float *)&unk_1BC2184 + 35 * *(_DWORD *)(a1 + 56)) = *(float *)(a1 + 44);
      result = 140 * *(_DWORD *)(a1 + 56);
      *(float *)((char *)&unk_1BC2188 + result) = *(float *)(a1 + 48);
    }
  }
  return result;
}

