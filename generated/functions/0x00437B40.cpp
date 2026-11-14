// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437B40 rf_entity_is_carrying_body
// UNREALRED VERIFIED [combat-panic-movement-20261111]: Entity+75C is retained carried-body handle: exactly !=-1 returns true.4344D0 forces slow speedmode0 on this same handle condition.43C0B0 clears it only after corpse resolution succeeds; the handle comparison does not require current resolution.
bool __cdecl rf_entity_is_carrying_body(int a1)
{
  return a1 && *(_DWORD *)(a1 + 1884) != -1;
}

