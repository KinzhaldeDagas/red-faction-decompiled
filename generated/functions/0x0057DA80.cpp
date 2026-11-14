// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057DA80 rf_stream_adapter_read_float4_versioned
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 ignores caller minimum/default and invokes file float4 reader with minimum0 and global default1C8FC3C. Memory mode requires signed cursor+16<=length BEFORE checking version. Bounds failure writes error+84=-1, leaves output/cursor; older version copies supplied default into output without consuming. Accepted read copies four floats and advances16. Unaligned temporary and aligned paths are equivalent. Return register on bounds failure is not a valid output/status guarantee.
float *__thiscall rf_stream_adapter_read_float4_versioned(void *this, float *a2, int a3, const float *a4)
{
  float *result; // eax
  float *v5; // ecx
  float v7; // [esp+4h] [ebp-10h] BYREF
  float v8; // [esp+8h] [ebp-Ch]
  float v9; // [esp+Ch] [ebp-8h]
  float v10; // [esp+10h] [ebp-4h]

  if ( !*(_DWORD *)this )
    return rf_binary_stream_read_float4_versioned(*((int **)this + 1), a2, 0, unk_1C8FC3C);
  result = (float *)this;
  if ( *((_DWORD *)this + 3) + 16 <= *((_DWORD *)this + 4) )
  {
    if ( *((_DWORD *)this + 20) < a3 )
    {
      return rf_float4_copy_return_destination(a2, (float *)a4);
    }
    else
    {
      if ( (*((_DWORD *)this + 3) & 3) != 0 )
      {
        rf_float4_construct_zero_zero_zero_one(&v7);
        v5 = (float *)(*((_DWORD *)this + 3) + *((_DWORD *)this + 2));
        v7 = *v5;
        v8 = v5[1];
        v9 = v5[2];
        v10 = v5[3];
        *a2 = v7;
        a2[1] = v8;
        a2[2] = v9;
        a2[3] = v10;
        *((_DWORD *)this + 3) += 16;
      }
      else
      {
        *a2 = *(float *)(*((_DWORD *)this + 2) + *((_DWORD *)this + 3));
        *((_DWORD *)this + 3) += 4;
        a2[1] = *(float *)(*((_DWORD *)this + 2) + *((_DWORD *)this + 3));
        *((_DWORD *)this + 3) += 4;
        a2[2] = *(float *)(*((_DWORD *)this + 2) + *((_DWORD *)this + 3));
        *((_DWORD *)this + 3) += 4;
        a2[3] = *(float *)(*((_DWORD *)this + 2) + *((_DWORD *)this + 3));
        *((_DWORD *)this + 3) += 4;
      }
      *a2 = *a2;
      a2[1] = a2[1];
      a2[2] = a2[2];
      a2[3] = a2[3];
      return a2;
    }
  }
  else
  {
    *((_DWORD *)this + 21) = -1;
  }
  return result;
}

