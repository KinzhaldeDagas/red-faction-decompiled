// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005782B0 rf_bitmap_create_user_bitmap
// UNREALRED VERIFIED [resource-pools-20261028]: Allocates bitmap descriptor through0x575F20, copies name USERBMAP, sets fields+32=-1,+52=3,+56=0, stores width/height as low16 at+44/+46, byte+64=1,byte+68=0. Computes mip metadata+48 via0x573E80(truncated dimensions,1), stores format+60 and clears+72/+80/+93; byte size+96 uses ORIGINAL integer width*height*format bytes0x574990. Returns handle+36. No dimension/allocation validation in this body; generated name is not source filename.
int __cdecl rf_bitmap_create_user_bitmap(int a1, int a2, int a3)
{
  char *single_slot_from_free_list; // [esp+0h] [ebp-4h]

  single_slot_from_free_list = (char *)rf_bitmap_allocate_single_slot_from_free_list();
  strcpy(single_slot_from_free_list, "USERBMAP");
  *((_DWORD *)single_slot_from_free_list + 8) = -1;
  *((_DWORD *)single_slot_from_free_list + 13) = 3;
  *((_DWORD *)single_slot_from_free_list + 14) = 0;
  *((_WORD *)single_slot_from_free_list + 22) = a2;
  *((_WORD *)single_slot_from_free_list + 23) = a3;
  single_slot_from_free_list[64] = 1;
  single_slot_from_free_list[68] = 0;
  *((_DWORD *)single_slot_from_free_list + 12) = rf_bitmap_mip_chain_pixel_count(
                                                   *((unsigned __int16 *)single_slot_from_free_list + 22),
                                                   *((unsigned __int16 *)single_slot_from_free_list + 23),
                                                   (unsigned __int8)single_slot_from_free_list[64]);
  *((_DWORD *)single_slot_from_free_list + 15) = a1;
  *((_DWORD *)single_slot_from_free_list + 18) = 0;
  *((_DWORD *)single_slot_from_free_list + 20) = 0;
  single_slot_from_free_list[93] = 0;
  *((_DWORD *)single_slot_from_free_list + 24) = a3 * a2 * rf_bitmap_format_bytes_per_pixel(a1);
  return *((_DWORD *)single_slot_from_free_list + 9);
}

