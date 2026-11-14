// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F7D80 rf_model_geometry_read_lod_descriptor
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl(vfile,destination16bytes). Reads int32flags to0,int32auxiliary count to4,uint16batch count to8,int32raw byte size to12. Leaves padding10/11 untouched;return last int32raw size. No output NULL/status/bounds validation;version threshold arguments passed0 to scalar readers.
int __cdecl rf_model_geometry_read_lod_descriptor(int *a1, int a2)
{
  int result; // eax

  *(_DWORD *)a2 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  *(_DWORD *)(a2 + 4) = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  *(_WORD *)(a2 + 8) = rf_binary_stream_read_uint16_versioned(a1, 0, 0);
  result = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  *(_DWORD *)(a2 + 12) = result;
  return result;
}

