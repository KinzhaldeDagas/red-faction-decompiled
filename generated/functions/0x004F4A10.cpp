// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F4A10 rf_world_decal_snapshot_collect
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] Collect renderer decal-list state through0x5250F0 into100-byte records, maximum64 successful records. Skip node flags+0x50 mask1 or0x400, texture handle+0x3C<=0, and absent/empty texture filename. Store position+0,orientation+12,raw vector+48, filename+60, packed dword+92 (low byte node+0x4C; high24 from node flags+0x50), scalar node+0x58 at+96. Filename uses uncapped C-string copy in body; no full padding clear. Traverse next node+0xE0 until null/circular head, export BYTE count. This is decal state, not general common-object headers.
_BYTE *__cdecl rf_world_decal_snapshot_collect(int a1, _BYTE *a2)
{
  char v3; // [esp+3h] [ebp-3Dh]
  _BYTE *v4; // [esp+8h] [ebp-38h]
  char *v5; // [esp+Ch] [ebp-34h]
  float *v6; // [esp+10h] [ebp-30h]
  float v7[3]; // [esp+14h] [ebp-2Ch] BYREF
  float copy_result[3]; // [esp+20h] [ebp-20h] BYREF
  char *source_record_name_pointer; // [esp+2Ch] [ebp-14h]
  int v10; // [esp+30h] [ebp-10h] BYREF
  float *source; // [esp+34h] [ebp-Ch]
  int v12; // [esp+38h] [ebp-8h]
  float *v13; // [esp+3Ch] [ebp-4h] BYREF

  v12 = 0;
  rf_world_decal_get_active_head_and_count(&v13, &v10);
  for ( source = v13; source; source = v6 )
  {
    if ( ((_DWORD)source[20] & 1) == 0 && *((int *)source + 15) > 0 && ((_DWORD)source[20] & 0x400) == 0 && v12 < 64 )
    {
      rf_vector_copy((float *)(a1 + 100 * v12), copy_result, source);
      rf_matrix3_copy((float *)(a1 + 100 * v12 + 12), source + 3);
      rf_vector_copy((float *)(a1 + 100 * v12 + 48), v7, source + 12);
      *(_BYTE *)(a1 + 100 * v12 + 60) = 0;
      source_record_name_pointer = (char *)rf_bitmap_get_source_record_name_pointer(*((_DWORD *)source + 15));
      if ( source_record_name_pointer )
      {
        if ( *source_record_name_pointer )
        {
          v5 = source_record_name_pointer;
          v4 = (_BYTE *)(a1 + 100 * v12 + 60);
          do
          {
            v3 = *v5;
            *v4++ = *v5++;
          }
          while ( v3 );
          *(_DWORD *)(a1 + 100 * v12 + 92) = *((unsigned __int8 *)source + 76)
                                           | *(_DWORD *)(a1 + 100 * v12 + 92) & 0xFFFFFF00;
          *(_DWORD *)(a1 + 100 * v12 + 92) = (((unsigned int)&unk_FFFFFF & (_DWORD)source[20]) << 8)
                                           | (unsigned __int8)*(_DWORD *)(a1 + 100 * v12 + 92);
          *(float *)(a1 + 100 * v12++ + 96) = source[22];
        }
      }
    }
    if ( *((float **)source + 56) == v13 )
      v6 = nullptr;
    else
      v6 = *((float **)source + 56);
  }
  *a2 = v12;
  return a2;
}

