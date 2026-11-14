// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057D920 rf_stream_adapter_read_vector3_versioned
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 ignores caller minimum/default and invokes file vector3 reader with minimum0 and global default1C8FBDC. Memory mode checks signed cursor+12<=length BEFORE version gating; failure sets integer error+84=-1 and leaves output/cursor unchanged. Accepted version reads three floats with unaligned temporary or aligned per-component path, advances12, returns output. Older-version path copies supplied default into output via rf_vector_copy and a local12-byte result object, whose address is returned; no bytes consumed. Return register on failure/default is not uniformly output. No normalization, endian conversion or negative-cursor guard.
float *__thiscall rf_stream_adapter_read_vector3_versioned(void *this, float *destination, int a3, const float *a4)
{
  float *result; // eax
  float *v5; // ecx
  float copy_result[3]; // [esp+4h] [ebp-18h] BYREF
  float v8; // [esp+10h] [ebp-Ch] BYREF
  float v9; // [esp+14h] [ebp-8h]
  float v10; // [esp+18h] [ebp-4h]

  if ( !*(_DWORD *)this )
    return (float *)rf_binary_stream_read_vector3_versioned(*((void **)this + 1), destination, 0, unk_1C8FBDC);
  result = (float *)this;
  if ( *((_DWORD *)this + 3) + 12 <= *((_DWORD *)this + 4) )
  {
    if ( *((_DWORD *)this + 20) < a3 )
    {
      return rf_vector_copy(destination, copy_result, a4);
    }
    else
    {
      if ( (*((_DWORD *)this + 3) & 3) != 0 )
      {
        rf_vector3_default_construct_noop(&v8);
        v5 = (float *)(*((_DWORD *)this + 3) + *((_DWORD *)this + 2));
        v8 = *v5;
        v9 = v5[1];
        v10 = v5[2];
        *destination = v8;
        destination[1] = v9;
        destination[2] = v10;
        *((_DWORD *)this + 3) += 12;
      }
      else
      {
        *destination = *(float *)(*((_DWORD *)this + 2) + *((_DWORD *)this + 3));
        *((_DWORD *)this + 3) += 4;
        destination[1] = *(float *)(*((_DWORD *)this + 2) + *((_DWORD *)this + 3));
        *((_DWORD *)this + 3) += 4;
        destination[2] = *(float *)(*((_DWORD *)this + 2) + *((_DWORD *)this + 3));
        *((_DWORD *)this + 3) += 4;
      }
      *destination = *destination;
      destination[1] = destination[1];
      destination[2] = destination[2];
      return destination;
    }
  }
  else
  {
    *((_DWORD *)this + 21) = -1;
  }
  return result;
}

