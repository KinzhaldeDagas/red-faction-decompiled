// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578050 rf_bitmap_set_source_metadata_byte93
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Stores caller byte at source record+93 and returns0. Ordinary subtype2 targets parent; animated path uses raw stripped handle without modulo3000. Does not set dirty flags, update renderer or normalize byte. Full semantic role of field93 remains unproven.
int __cdecl rf_bitmap_set_source_metadata_byte93(unsigned int a1, char a2)
{
  int v3; // [esp+0h] [ebp-8h]
  unsigned int v4; // [esp+4h] [ebp-4h]

  v4 = rf_bitmap_handle_to_slot_index(a1);
  if ( (a1 & 0x40000000) != 0 )
  {
    *(_BYTE *)(dword_1897344 + 108 * unk_187CD40[9 * (a1 & 0xBFFFFFFF)] + 93) = a2;
  }
  else
  {
    v3 = dword_1897344 + 108 * v4;
    if ( *(_DWORD *)(v3 + 56) == 2 )
      v3 -= 108 * *(unsigned __int8 *)(v3 + 67);
    *(_BYTE *)(v3 + 93) = a2;
  }
  return 0;
}

