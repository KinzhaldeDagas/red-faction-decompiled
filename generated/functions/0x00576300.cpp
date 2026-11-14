// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00576300 rf_bitmap_load_and_query_animation_metadata
// UNREALRED VERIFIED [bitmap-loading-20261028]: Calls0x574EE0(name,source context), decodes returned handle directly. If resulting ordinary record subtype+56==1, outputs framecount byte+67 and ceil(ratefloat+76*1000); otherwise outputs1 and0. Returns loaded handle. Does not resolve current frame or check load failure/animation handle type; outputs are metadata, not duration.
unsigned int __cdecl rf_bitmap_load_and_query_animation_metadata(char *String2, _DWORD *a2, _DWORD *a3, char *a4)
{
  float v5; // [esp+4h] [ebp-Ch]
  unsigned int v6; // [esp+8h] [ebp-8h]
  unsigned int v7; // [esp+Ch] [ebp-4h]

  v6 = rf_bitmap_load_or_register_metadata_and_slots(String2, a4);
  v7 = rf_bitmap_handle_to_slot_index(v6);
  if ( *(_DWORD *)(dword_1897344 + 108 * v7 + 56) == 1 )
  {
    *a2 = *(unsigned __int8 *)(dword_1897344 + 108 * v7 + 67);
    v5 = *(float *)(dword_1897344 + 108 * v7 + 76) * 1000.0;
    *a3 = (int)rf_math_ceil_float(v5);
  }
  else
  {
    *a2 = 1;
    *a3 = 0;
  }
  return v6;
}

