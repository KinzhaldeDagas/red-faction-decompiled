// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FBAC0 rf_scene_named_reference_list_read_binary
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args vfile,pool{used0,base4},scene owner. Reads NULname torecord0 with max64,then int32count136;entries140=pool.base+8*oldUsed,used+=count. Perentry reads int32kind into0,NULtarget name into260-byte local(max255). Kind0 searches scene collection base+72,count+76,stride292 bycase-sensitive name;kind1 searches base+88,count+92,stride220. Found setsentry pointer+4;unknown kind or unresolved name leaves pointer+4 UNTOUCHED,notNULL. No pool/negative-count/overflow/status guard or parent-name read. Return incidental count/loop index.
int __thiscall rf_scene_named_reference_list_read_binary(int this, int *a2, int *a3, _DWORD *a4)
{
  int result; // eax
  int int32_versioned; // eax
  int v6; // [esp+28h] [ebp-118h]
  char v8[260]; // [esp+30h] [ebp-110h] BYREF
  int j; // [esp+138h] [ebp-8h]
  int i; // [esp+13Ch] [ebp-4h]

  rf_binary_stream_read_nul_string_to_buffer(a2, (char *)this, 64, 0, nullptr);
  *(_DWORD *)(this + 136) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
  *(_DWORD *)(this + 140) = a3[1] + 8 * *a3;
  result = *(_DWORD *)(this + 136) + *a3;
  *a3 = result;
  for ( i = 0; i < *(_DWORD *)(this + 136); ++i )
  {
    int32_versioned = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    *(_DWORD *)(*(_DWORD *)(this + 140) + 8 * i) = int32_versioned;
    rf_binary_stream_read_nul_string_to_buffer(a2, v8, 255, 0, nullptr);
    v6 = *(_DWORD *)(*(_DWORD *)(this + 140) + 8 * i);
    if ( v6 )
    {
      if ( v6 == 1 )
      {
        for ( j = 0; j < a4[23] && strcmp(v8, (const char *)(a4[22] + 220 * j)); ++j )
          ;
        if ( j < a4[23] )
          *(_DWORD *)(*(_DWORD *)(this + 140) + 8 * i + 4) = a4[22] + 220 * j;
      }
    }
    else
    {
      for ( j = 0; j < a4[19] && strcmp(v8, (const char *)(a4[18] + 292 * j)); ++j )
        ;
      if ( j < a4[19] )
        *(_DWORD *)(*(_DWORD *)(this + 140) + 8 * i + 4) = a4[18] + 292 * j;
    }
    result = i + 1;
  }
  return result;
}

