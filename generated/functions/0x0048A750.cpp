// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A750 rf_mover_is_rotating
// UNREALRED VERIFIED [mission-mover-layout-20261013] Rotating-mover predicate reads runtime flags +0x318 bit 4, installed from serialized group behavior boolean index1.
bool __cdecl rf_mover_is_rotating(int a1)
{
  return (*(_DWORD *)(a1 + 792) & 4) != 0;
}

