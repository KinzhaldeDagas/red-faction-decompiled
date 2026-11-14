// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004836C0 rf_rfl_cutscene_sequences_load
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Cdecl stream, RFL section0x4000; corrected missing stream argument. Reads signed sequence count, allocates2144 bytes per sequence, invokes ctor483C80 if nonnull, then
// unconditionally reads into resulting pointer. Stores sequence id0, versioned bool(min143,default0) at BYTE2137, versioned float(min146,default90.0) at2140, signed segment count4.
// Loops j<segmentCount WITHOUT64-entry cap into32-byte slots at8+32*j. Each row: int32+0,three FLOATs+4/+8/+12,two int32+16/+20,RFString+24. Values are stored as authored; no
// duration/id/index/range/finite validation or resolution of segment ids here.
// Only first64 slots have RFString constructors from containing ctor. A count>64 can overwrite runtime fields and pass unconstructed string storage to reader; negative count stores
// negative but reads no segments. Appends sequence pointer to vector6FB264 after rows, no registry reset, allocation-NULL guard or all-row transaction rollback. Constructor-exception
// unwind deletes current raw allocation; source count is not a capacity constraint. Return EAX incidental row-loop result.
int __cdecl rf_rfl_cutscene_sequences_load(_DWORD *stream)
{
  int result; // eax
  char *v2; // [esp+8h] [ebp-2Ch]
  char *v3; // [esp+Ch] [ebp-28h]
  int v4; // [esp+14h] [ebp-20h]
  int j; // [esp+1Ch] [ebp-18h]
  int i; // [esp+20h] [ebp-14h]
  int v7; // [esp+24h] [ebp-10h]

  result = rf_binary_stream_read_int32_versioned(stream, 0, 0);
  v7 = result;
  for ( i = 0; i < v7; ++i )
  {
    v3 = (char *)operator new(0x860u);
    if ( v3 )
      v2 = rf_cutscene_sequence2144_construct(v3);
    else
      v2 = nullptr;
    *(_DWORD *)v2 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
    v2[2137] = rf_binary_stream_read_bool_versioned(stream, 143, 0);
    *((float *)v2 + 535) = rf_binary_stream_read_float_versioned(stream, 146, 90.0);
    *((_DWORD *)v2 + 1) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
    for ( j = 0; j < *((_DWORD *)v2 + 1); ++j )
    {
      v4 = (int)&v2[32 * j + 8];
      *(_DWORD *)v4 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *(float *)(v4 + 4) = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
      *(float *)(v4 + 8) = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
      *(float *)(v4 + 12) = rf_binary_stream_read_float_versioned(stream, 0, 0.0);
      *(_DWORD *)(v4 + 16) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *(_DWORD *)(v4 + 20) = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      rf_binary_stream_read_string_object_versioned(stream, &v2[32 * j + 32], 0, nullptr);
    }
    rf_pointer_array_append_dword(unk_6FB264, (int)v2);
    result = i + 1;
  }
  return result;
}

