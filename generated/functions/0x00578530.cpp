// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578530 rf_bitmap_query_root_or_previous_root_animation_info
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl(handle,outFrameCount32,outRoundedFPS32),returns selected handle. Decodes handle as slot;kind DWORD+56==2 tries exactly FULL HANDLE-1 and decodes that once. If resulting record kind1,outputs BYTE frameCount+67 and int(ceil(float(rate76*1000))),returns candidate handle. Rate is frames/ms,so rounded value is FPS,NOT frame duration. Does NOT scan back through multiple kind2 frames;nonroot predecessor falls back to ORIGINAL handle,count1,FPS0. Root kind1 input returns same handle. No instance/source resolution,full-generation,output/rate/count guard;zero/negative rates not rejected.
unsigned int __cdecl rf_bitmap_query_root_or_previous_root_animation_info(unsigned int a1, _DWORD *a2, _DWORD *a3)
{
  float v4; // [esp+4h] [ebp-Ch]
  unsigned int v5; // [esp+8h] [ebp-8h]
  unsigned int v6; // [esp+Ch] [ebp-4h]

  v5 = rf_bitmap_handle_to_slot_index(a1);
  v6 = a1;
  if ( *(_DWORD *)(dword_1897344 + 108 * v5 + 56) == 2 )
  {
    v6 = a1 - 1;
    v5 = rf_bitmap_handle_to_slot_index(a1 - 1);
  }
  if ( *(_DWORD *)(dword_1897344 + 108 * v5 + 56) == 1 )
  {
    *a2 = *(unsigned __int8 *)(dword_1897344 + 108 * v5 + 67);
    v4 = *(float *)(dword_1897344 + 108 * v5 + 76) * 1000.0;
    *a3 = (int)rf_math_ceil_float(v4);
  }
  else
  {
    v6 = a1;
    *a2 = 1;
    *a3 = 0;
  }
  return v6;
}

