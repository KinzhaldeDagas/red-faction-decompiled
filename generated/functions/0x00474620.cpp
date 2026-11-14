// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474620 rf_item_find_by_uid
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Authored item UID lookup: -1 returns null; scans item list rooted0x6FB1C4/0x6FAF38 via +0x28C and compares common UID+0x20. The mover-linked records at +0x2BC are items, corroborated by item spawn/respawn list consumers and pickup0x473940.
int __cdecl rf_item_find_by_uid(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  if ( a1 == -1 )
    return 0;
  for ( i = unk_6FB1C4; (_UNKNOWN *)i != &unk_6FAF38; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 32) == a1 )
      return i;
  }
  return 0;
}

