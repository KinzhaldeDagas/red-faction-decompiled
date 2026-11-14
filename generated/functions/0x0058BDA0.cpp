// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058BDA0 rf_font_release_all_loaded_records
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Walks count193BB98 records at193B688, stride108. For each nonzero header/loaded DWORD+32, clears filename[0], deletes and NULLs kerning+68, glyph records+72, source pixels+76, palette+80, atlas X/Y arrays+96/+100 and CPU atlas pixels+104, then clears+32. Does not recycle GPU atlas bitmap handle+84, reset font count, or clear default/current font pointers. EAX incidental loop count; records and remaining scalar fields stay allocated in static storage.
int rf_font_release_all_loaded_records()
{
  int result; // eax
  void **v1; // [esp+1Ch] [ebp-Ch]
  int i; // [esp+20h] [ebp-8h]

  v1 = (void **)&unk_193B688;
  for ( i = 0; i < unk_193BB98; ++i )
  {
    if ( v1[8] )
    {
      *(_BYTE *)v1 = 0;
      if ( v1[17] )
      {
        operator delete(v1[17]);
        v1[17] = nullptr;
      }
      if ( v1[18] )
      {
        operator delete(v1[18]);
        v1[18] = nullptr;
      }
      if ( v1[19] )
      {
        operator delete(v1[19]);
        v1[19] = nullptr;
      }
      if ( v1[20] )
      {
        operator delete(v1[20]);
        v1[20] = nullptr;
      }
      if ( v1[24] )
      {
        operator delete(v1[24]);
        v1[24] = nullptr;
      }
      if ( v1[25] )
      {
        operator delete(v1[25]);
        v1[25] = nullptr;
      }
      if ( v1[26] )
      {
        operator delete(v1[26]);
        v1[26] = nullptr;
      }
      v1[8] = nullptr;
    }
    v1 += 27;
    result = i + 1;
  }
  return result;
}

