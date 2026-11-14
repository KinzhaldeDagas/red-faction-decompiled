// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E070 rf_stream_adapter_read_packed4bytes_versioned
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 forwards output,minimum,default to file packed4-byte reader and returns output. Memory older-version branch copies defaultDWORD without consuming. Accepted branch calls versioned byte reader four times with minimum0/default0, packs results into output DWORD. No aggregate4-byte bounds check: short input partially advances, failed bytes become0 and set error+84. No normalization/channel transformation.
_DWORD *__thiscall rf_stream_adapter_read_packed4bytes_versioned(_DWORD *this, _DWORD *a2, int a3, _DWORD *a4)
{
  int v6; // [esp+4h] [ebp-4h] BYREF

  if ( *this )
  {
    if ( *(this + 20) < a3 )
    {
      *a2 = *a4;
    }
    else
    {
      rf_rgba8_default_construct_noop(&v6);
      LOBYTE(v6) = rf_stream_adapter_read_byte_versioned(this, 0, 0);
      BYTE1(v6) = rf_stream_adapter_read_byte_versioned(this, 0, 0);
      BYTE2(v6) = rf_stream_adapter_read_byte_versioned(this, 0, 0);
      HIBYTE(v6) = rf_stream_adapter_read_byte_versioned(this, 0, 0);
      *a2 = v6;
    }
    return a2;
  }
  else
  {
    rf_binary_stream_read_packed4bytes_versioned((_DWORD *)*(this + 1), a2, a3, a4);
    return a2;
  }
}

