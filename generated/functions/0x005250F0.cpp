// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005250F0 rf_world_decal_get_active_head_and_count
// UNREALRED VERIFIED [decal-updates-20261028]: Writes circular active head0xA7051C to mandatory output1 and count0xA70624 to mandatory output2; returns count. No copying, filtering or output-pointer validation.
int __cdecl rf_world_decal_get_active_head_and_count(_DWORD *a1, _DWORD *a2)
{
  int result; // eax

  *a1 = unk_A7051C;
  result = unk_A70624;
  *a2 = unk_A70624;
  return result;
}

