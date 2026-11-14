// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1200 rf_bolt_emitter_render_callback
// UNREALRED VERIFIED [impact-callbacks-20261028]: Fetches current player/view position through0x4118D0 using *(global0x87C640+196), passes emitter and view position to0x4C0E00. Returns renderer helper result. No emitter/view pointer validation, lifetime update or registry mutation in this wrapper.
int *__cdecl rf_bolt_emitter_render_callback(float *a1)
{
  float v2[3]; // [esp+0h] [ebp-10h] BYREF
  float *v3; // [esp+Ch] [ebp-4h]

  v3 = a1;
  rf_entity_view_copy_referenced_position(v2, *(_DWORD *)(unk_87C640 + 196));
  return rf_bolt_emitter_regenerate_points_and_render(v3, (int)v2);
}

