// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565EC0 rf_model_handle_get_definition_pointer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Returns DWORD8 for every tag without validation. For tag1 initialized handles this field can remainNULL while cached V3M asset is in4. No runtime-instance or borrowed-record conversion.
int __cdecl rf_model_handle_get_definition_pointer(int a1)
{
  return *(_DWORD *)(a1 + 8);
}

