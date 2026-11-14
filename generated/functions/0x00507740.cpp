// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507740 rf_vclip_effect_render_callback
// UNREALRED VERIFIED [impact-callbacks-20261028]: Builds default model-render params in80-byte local through0x561B70 then calls0x564BB0(instance descriptor record+8,position+12,orientation+24,params). Returns helper result. No lifetime advancement, room test or allocation in callback.
int __cdecl rf_vclip_effect_render_callback(int a1)
{
  char v2[80]; // [esp+4h] [ebp-50h] BYREF

  rf_model_render_options_construct(v2);
  return rf_model_handle_render_all_adapter(*(_DWORD *)(a1 + 8), a1 + 12, a1 + 24, (int)v2);
}

