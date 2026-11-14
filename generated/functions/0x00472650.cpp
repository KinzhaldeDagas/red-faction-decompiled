// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00472650 rf_item_has_retention_flag10
// UNREALRED VERIFIED [item-pickups-20261028]: Returns boolean(item flags+700 &0x10). No null guard. Dropped-item limiter excludes matching items; fade-start helper refuses them. Name preserves verified flag behavior without assuming authored/dropped provenance.
bool __cdecl rf_item_has_retention_flag10(int a1)
{
  return (*(_DWORD *)(a1 + 700) & 0x10) != 0;
}

