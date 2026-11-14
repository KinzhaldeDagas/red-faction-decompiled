// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474710 rf_item_is_fading
// UNREALRED VERIFIED [item-pickups-20261028]: Returns boolean(item flags+700 &4). Used by fade lifetime updater and render alpha. No null guard or timer check.
BOOL __cdecl rf_item_is_fading(int a1)
{
  return (*(_DWORD *)(a1 + 700) & 4) != 0;
}

