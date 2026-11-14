// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578390 rf_bitmap_animation_instance_allocate_from_free_head
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl(sourceHandle,rateMultiplier,initialFrameByte,loopMode),returns tagged handle. Decodes source index with574350,then UNCONDITIONALLY removes global free-list head18973C0 (entry prev+4,next+8) and appends to active tail1897324/sentinel1897320. No empty-list check. Handle=((SIGNED(entry-base187CD40)/36)+3000*578490_generation) OR40000000. Stores sourceIndex+0,handle+12,rate+16=float(sourceRecord.rate76*multiplier),mode+20,initialFrame BYTE+24,status+28=0. Start-clock+32 and padding bytes not initialized here;574B80 initializes clock on status0. Stored rate is FRAMES PER MILLISECOND,so multiplier scales playback speed. No source-kind/generation,capacity/rate/count/mode validation,allocation or lock;tagged
// source input is not converted through its source record.
unsigned int __cdecl rf_bitmap_animation_instance_allocate_from_free_head(
        unsigned int source_handle,
        float rate_multiplier,
        unsigned __int8 initial_frame,
        int loop_mode)
{
  int v5; // [esp+0h] [ebp-10h]
  int v6; // [esp+4h] [ebp-Ch]
  unsigned int v7; // [esp+Ch] [ebp-4h]

  v7 = rf_bitmap_handle_to_slot_index(source_handle);
  v6 = dword_1897344 + 108 * v7;
  v5 = dword_18973C0;
  *(_DWORD *)(*(_DWORD *)(dword_18973C0 + 8) + 4) = *(_DWORD *)(dword_18973C0 + 4);
  *(_DWORD *)(*(_DWORD *)(v5 + 4) + 8) = *(_DWORD *)(v5 + 8);
  *(_DWORD *)(v5 + 4) = 0;
  *(_DWORD *)(v5 + 8) = 0;
  *(_DWORD *)(v5 + 4) = dword_1897324;
  *(_DWORD *)(dword_1897324 + 8) = v5;
  dword_1897324 = v5;
  *(_DWORD *)(v5 + 8) = &unk_1897320;
  *(_DWORD *)(v5 + 12) = ((v5 - (int)unk_187CD40) / 36 + 3000 * rf_bitmap_animation_next_generation_wrapped())
                       | 0x40000000;
  *(_DWORD *)(v5 + 28) = 0;
  *(_BYTE *)(v5 + 24) = initial_frame;
  *(_DWORD *)v5 = v7;
  *(float *)(v5 + 16) = *(float *)(v6 + 76) * rate_multiplier;
  *(_DWORD *)(v5 + 20) = loop_mode;
  return *(_DWORD *)(v5 + 12);
}

