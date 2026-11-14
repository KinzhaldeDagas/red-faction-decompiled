// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005763A0 rf_bitmap_vbm_sequence_load
// UNREALRED VERIFIED [combat-particle-vbm-20261104]: Sequence loader returns firstdrawableVBM framehandle+1, writes unsigned-byte metadata framecount and ceil(float(storedFPSMillis*1000)) as integerFPS. Ordinary bitmap fallback writes framecount1,FPS0 and returns basehandle; no positive playback-lifetime fallback is evidenced. VBM billboard506E20 uses count/FPS; unsupported/nonfinite playback must be isolated in the Unreal adapter, not fabricated.
unsigned int __cdecl rf_bitmap_vbm_sequence_load(char *String2, _DWORD *a2, _DWORD *a3)
{
  float v4; // [esp+4h] [ebp-Ch]
  unsigned int v5; // [esp+8h] [ebp-8h]
  unsigned int v6; // [esp+Ch] [ebp-4h]

  v5 = rf_bitmap_load_or_register_metadata_and_slots(String2, (char *)0xFFFFFFFF);
  v6 = rf_bitmap_handle_to_slot_index(v5);
  if ( *(_DWORD *)(dword_1897344 + 108 * v6 + 56) == 1 )
  {
    *a2 = *(unsigned __int8 *)(dword_1897344 + 108 * v6 + 67);
    v4 = *(float *)(dword_1897344 + 108 * v6 + 76) * 1000.0;
    *a3 = (int)rf_math_ceil_float(v4);
    return v5 + 1;
  }
  else
  {
    *a2 = 1;
    *a3 = 0;
    return v5;
  }
}

