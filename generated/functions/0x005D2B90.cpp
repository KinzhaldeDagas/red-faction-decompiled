// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D2B90 rf_renderer_filter_rgb_from_channel_sum
// UNREALRED VERIFIED [renderer-helpers-20261028]: Captures original signed integer sum(*red+*green+*blue) as float,then independently assigns each channel integer-converted sum*globalweight0x187CD08/0C/10 and clamps0..255. Uses original sum for all three despite overwriting inputs. No alpha contribution or normalization by3. Returns third clamp helper result,not packed color.
_DWORD *__cdecl rf_renderer_filter_rgb_from_channel_sum(_DWORD *a1, _DWORD *a2, _DWORD *a3)
{
  float v4; // [esp+4h] [ebp-4h]

  v4 = (float)(*a3 + *a2 + *a1);
  *a1 = (int)(v4 * flt_187CD08);
  rf_integer_clamp_in_place(a1, 0, 255);
  *a2 = (int)(v4 * flt_187CD0C);
  rf_integer_clamp_in_place(a2, 0, 255);
  *a3 = (int)(v4 * flt_187CD10);
  return rf_integer_clamp_in_place(a3, 0, 255);
}

