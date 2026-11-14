// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B9C50 rf_model_resource_classify_header_signature
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mesh initializers, binary reader stores, caller layouts and signature classification): Constructs local VFile, opens supplied path with mode1 and the existing extension/cache-control argument. Open failure returns0 after destructor. Otherwise reads first DWORD:0x52463344 returns1,0x5246434D returns2, all other values return0; closes then destructs stream before returning. No version/payload validation or further parsing; no explicit read-status test here. Includes compiler EH cleanup and stack-cookie checks. Literal little-endian bytes are D3FR and MCFR.
int __cdecl rf_model_resource_classify_header_signature(char *Str)
{
  int v2; // [esp+8h] [ebp-134h]
  int self[70]; // [esp+10h] [ebp-12Ch] BYREF
  int int32_versioned; // [esp+12Ch] [ebp-10h]
  int v5; // [esp+138h] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v5 = 0;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, Str, 1, byte_98967F) >= 0 )
  {
    int32_versioned = rf_binary_stream_read_int32_versioned(self, 0, 0);
    if ( int32_versioned == 1380332356 )
    {
      int32_versioned = 1;
    }
    else if ( int32_versioned == 1380336461 )
    {
      int32_versioned = 2;
    }
    else
    {
      int32_versioned = 0;
    }
    rf_vfile_close_stdio_or_vpp(self);
    v2 = int32_versioned;
    v5 = -1;
    rf_vfile_destruct_close_if_open(self);
    return v2;
  }
  else
  {
    v5 = -1;
    rf_vfile_destruct_close_if_open(self);
    return 0;
  }
}

