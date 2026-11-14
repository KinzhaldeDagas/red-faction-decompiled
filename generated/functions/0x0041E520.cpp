// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041E520 rf_corpse_serialize_animation_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Cdecl(outputRows,outCountByte). Scans list order, skips common flags124 mask0x800, emits at most32 records of532 bytes. Common60 pack may CLAMP LIVE health/armor; this is not mutation-free serialization. Explicit row map: mass60,radius64,sphere count68,record24 payload72;class index384,creation float388,fade392,flags436=(corpse668|8),timer remaining440,scalar444,state/action IDs448/452/456/460/464 from corpse692/696/700/704/708. Special model712 filename at468 and main model128 filename at500 are copied with UNBOUNDED NUL loops into nominal32-byte slots; absent model writes first byte0 only. Sphere loop uses live count without13-record bound, so excess records overwrite
// class and following fields. No explicit writes of reserved396..435 except possible unchecked-copy overflow. Copies all six record floats through x87 helper. No buffer-size/filename/array-count validation or zeroing of padding/unused row bytes. ALWAYS writes authoritative emitted count BYTE0..32; nominal EAX is incidental last traversal/accepted-count value, not reliable count or success.
int __cdecl rf_corpse_serialize_animation_state(int a1, _BYTE *a2)
{
  int result; // eax
  char v3; // dl
  char v4; // al
  float *element_address_unchecked; // eax
  _BYTE *v6; // [esp+8h] [ebp-2Ch]
  char *v7; // [esp+Ch] [ebp-28h]
  _BYTE *v8; // [esp+18h] [ebp-1Ch]
  char *v9; // [esp+1Ch] [ebp-18h]
  int j; // [esp+28h] [ebp-Ch]
  int i; // [esp+2Ch] [ebp-8h]
  int v12; // [esp+30h] [ebp-4h]

  v12 = 0;
  result = rf_corpse_list_head;
  for ( i = rf_corpse_list_head; (_UNKNOWN *)i != &unk_681AF8; i = *(_DWORD *)(i + 652) )
  {
    result = i;
    if ( (*(_DWORD *)(i + 124) & 0x800) == 0 && v12 < 32 )
    {
      rf_object_snapshot_pack_common60(i, a1 + 532 * v12);
      *(float *)(a1 + 532 * v12 + 388) = *(float *)(i + 660);
      *(float *)(a1 + 532 * v12 + 392) = *(float *)(i + 664);
      *(_DWORD *)(a1 + 532 * v12 + 436) = *(_DWORD *)(i + 668) | 8;
      rf_snapshot_pack_replicator_remaining((int *)(i + 684), (int *)(a1 + 532 * v12 + 440));
      *(float *)(a1 + 532 * v12 + 444) = *(float *)(i + 688);
      *(_DWORD *)(a1 + 532 * v12 + 448) = *(_DWORD *)(i + 692);
      *(_DWORD *)(a1 + 532 * v12 + 452) = *(_DWORD *)(i + 696);
      *(_DWORD *)(a1 + 532 * v12 + 456) = *(_DWORD *)(i + 700);
      *(_DWORD *)(a1 + 532 * v12 + 460) = *(_DWORD *)(i + 704);
      *(_DWORD *)(a1 + 532 * v12 + 464) = *(_DWORD *)(i + 708);
      *(_DWORD *)(a1 + 532 * v12 + 384) = *(_DWORD *)(i + 672);
      if ( *(_DWORD *)(i + 712) )
      {
        v9 = (char *)rf_model_descriptor_filename_pointer(*(_DWORD *)(i + 712));
        v8 = (_BYTE *)(a1 + 532 * v12 + 468);
        do
        {
          v3 = *v9;
          *v8++ = *v9++;
        }
        while ( v3 );
      }
      else
      {
        *(_BYTE *)(a1 + 532 * v12 + 468) = 0;
      }
      if ( *(_DWORD *)(i + 128) )
      {
        v7 = (char *)rf_model_descriptor_filename_pointer(*(_DWORD *)(i + 128));
        v6 = (_BYTE *)(a1 + 532 * v12 + 500);
        do
        {
          v4 = *v7;
          *v6++ = *v7++;
        }
        while ( v4 );
      }
      else
      {
        *(_BYTE *)(a1 + 532 * v12 + 500) = 0;
      }
      *(_DWORD *)(a1 + 532 * v12 + 68) = rf_receiver_get_first_dword((void *)(i + 388));
      for ( j = 0; j < *(_DWORD *)(a1 + 532 * v12 + 68); ++j )
      {
        element_address_unchecked = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(i + 388), j);
        rf_record24_copy_six_floats((float *)(a1 + 532 * v12 + 24 * j + 72), element_address_unchecked);
      }
      *(float *)(a1 + 532 * v12 + 60) = *(float *)(i + 152);
      *(float *)(a1 + 532 * v12 + 64) = *(float *)(i + 384);
      result = ++v12;
    }
  }
  *a2 = v12;
  return result;
}

