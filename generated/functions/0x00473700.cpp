// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00473700 rf_item_unlink_and_clear_instance_name
// UNREALRED VERIFIED [item-pickups-20261028]: Assigns constant string0x6380A7 to RF string at item+668, unlinks doubly-linked item list (next+652,prev+656), then clears both links. Does not operator-delete item or destroy all common members. Returns item pointer.
_DWORD *__cdecl rf_item_unlink_and_clear_instance_name(_DWORD *a1)
{
  rf_string_assign_from_cstr(a1 + 167, (char *)&byte_6380A7);
  *(_DWORD *)(a1[164] + 652) = a1[163];
  *(_DWORD *)(a1[163] + 656) = a1[164];
  a1[163] = 0;
  a1[164] = 0;
  return a1;
}

