// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004835C0 rf_rfl_cutscene_bezier_paths_load
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Cdecl stream, RFL section0x6000; corrected missing stream argument. Reads signed path count, loops while i<count AND global count6FB250<32; uses100-byte record6FB670+100*count and
// increments count BEFORE reads. Reads RFString name0, signed control-reference count, then that many int32 ids; resolves each via cutscene_aux_record_find_by_id and stores raw
// pointer at record72+4*j. No per-path count<=7 storage bound, exactly-four validation or NULL-reference check. Nonpositive count still proceeds to Bezier construction using existing
// first four pointer slots.
// Calls cubic_bezier_set_embedded_controls on record+8 with FIRST FOUR resolved pointers' position+4, irrespective serialized reference count; extra references are stored but do not
// become extra Bezier controls. Missing/short references can supply NULL/stale pointers and counts>7 write beyond100-byte record. Does not clear records/global count or itself
// consume excess paths after32 cap. Normal return register is row-loop artifact, not stable load status. No input reordering or interpolation sampling here.
int __cdecl rf_rfl_cutscene_bezier_paths_load(_DWORD *stream)
{
  int result; // eax
  char *v2; // [esp+0h] [ebp-18h]
  int j; // [esp+4h] [ebp-14h]
  int v4; // [esp+8h] [ebp-10h]
  int v5; // [esp+Ch] [ebp-Ch]
  int i; // [esp+10h] [ebp-8h]
  int int32_versioned; // [esp+14h] [ebp-4h]

  result = rf_binary_stream_read_int32_versioned(stream, 0, 0);
  v5 = result;
  for ( i = 0; i < v5 && dword_6FB250 < 32; ++i )
  {
    v2 = &byte_6FB670[100 * dword_6FB250++];
    rf_binary_stream_read_string_object_versioned(stream, v2, 0, nullptr);
    int32_versioned = rf_binary_stream_read_int32_versioned(stream, 0, 0);
    for ( j = 0; j < int32_versioned; ++j )
    {
      v4 = rf_binary_stream_read_int32_versioned(stream, 0, 0);
      *(_DWORD *)&v2[4 * j + 72] = rf_cutscene_aux_record_find_by_id(v4);
    }
    rf_cubic_bezier_set_embedded_controls(
      (int)(v2 + 8),
      (float *)(*((_DWORD *)v2 + 18) + 4),
      (float *)(*((_DWORD *)v2 + 19) + 4),
      (float *)(*((_DWORD *)v2 + 20) + 4),
      (float *)(*((_DWORD *)v2 + 21) + 4));
    result = i + 1;
  }
  return result;
}

