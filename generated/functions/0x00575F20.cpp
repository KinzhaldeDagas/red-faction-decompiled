// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00575F20 rf_bitmap_allocate_single_slot_from_free_list
// UNREALRED VERIFIED [bitmap-loading-20261028]: Takes head0x18973A4, unlinks next/previous+84/+88, inserts at active-list head0x1897434 with sentinel0x18973E0. Computes slot=(record-base0x1897344)/108 and handle=slot+slotcount0x663F14*next_generation0x575FD0; stores at+36, returns record pointer. No empty-free-list/sentinel check, allocation or payload reset. Caller sets record type and metadata.
_DWORD *rf_bitmap_allocate_single_slot_from_free_list()
{
  _DWORD *v1; // [esp+0h] [ebp-8h]
  int v2; // [esp+4h] [ebp-4h]

  v1 = (_DWORD *)unk_18973A4;
  *(_DWORD *)(*(_DWORD *)(unk_18973A4 + 88) + 84) = *(_DWORD *)(unk_18973A4 + 84);
  *(_DWORD *)(v1[21] + 88) = v1[22];
  v1[21] = 0;
  v1[22] = 0;
  v1[21] = dword_1897434;
  *(_DWORD *)(dword_1897434 + 88) = v1;
  dword_1897434 = (int)v1;
  v1[22] = &unk_18973E0;
  v2 = ((int)v1 - dword_1897344) / 108;
  v1[9] = v2 + dword_663F14 * rf_bitmap_next_handle_generation();
  return v1;
}

