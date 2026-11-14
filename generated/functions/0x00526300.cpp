// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00526300 rf_geometry_set_current_context
// UNREALRED VERIFIED [level-lifecycle-20261028]: Stores supplied pointers/values into globals0xD035EC and0xD035F0, returns first argument. Level setup passes world solid and0x704600; teardown passes0,0. No allocations or validation.
int __cdecl rf_geometry_set_current_context(int a1, int a2)
{
  unk_D035EC = a1;
  unk_D035F0 = a2;
  return a1;
}

