// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041F240 rf_array24_append_record_by_value
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Thiscall header plus SIX DWORD by-value record payload,RET24; no source-pointer argument. Grows ONLY when count==capacity, choosing16 when capacity0 else unchecked doubled capacity; count>capacity does not grow. Captures old count then increments count BEFORE copying all24 bytes from caller stack via six-float copy helper to base+24*oldCount. Returns old index. Reallocator saturates allocation-size multiply overflow but append capacity doubling is unchecked. No count/capacity/base/null/sign validation or copy/exception rollback.
int __thiscall rf_array24_append_record_by_value(int *this, float a2, int a3, int a4, int a5, int a6, int a7)
{
  int v8; // [esp+0h] [ebp-Ch]
  int v10; // [esp+8h] [ebp-4h]

  if ( *this == *(this + 1) )
  {
    if ( *(this + 1) )
      v8 = 2 * *(this + 1);
    else
      v8 = 16;
    rf_array24_reallocate_capacity_unchecked(this, v8);
  }
  v10 = (*this)++;
  rf_record24_copy_six_floats((float *)(*(this + 2) + 24 * v10), &a2);
  return v10;
}

