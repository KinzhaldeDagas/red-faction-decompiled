// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00577F50 rf_bitmap_get_source_record_name_pointer
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Returns pointer to ordinary source 108-byte bitmap record, whose first field is name. Ordinary subtype2 backs up by 108*byte+67. Animated path uses 0x187CD40[9*(handle & 0xBFFFFFFF)] as source index WITHOUT modulo3000, despite initially calling handle decoder. Assembly confirms raw stripped handle indexing. Does not resolve time/current frame or validate occupancy. Caller must supply an animation handle whose stripped value fits this direct indexing convention.
int __cdecl rf_bitmap_get_source_record_name_pointer(unsigned int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  unsigned int v3; // [esp+4h] [ebp-4h]

  v3 = rf_bitmap_handle_to_slot_index(a1);
  if ( (a1 & 0x40000000) != 0 )
    return dword_1897344 + 108 * unk_187CD40[9 * (a1 & 0xBFFFFFFF)];
  v2 = dword_1897344 + 108 * v3;
  if ( *(_DWORD *)(v2 + 56) == 2 )
    v2 -= 108 * *(unsigned __int8 *)(v2 + 67);
  return v2;
}

