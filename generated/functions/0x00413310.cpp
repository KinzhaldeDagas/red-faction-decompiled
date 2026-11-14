// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413310 rf_matrix_array36_append_by_value
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): ECX array header(count0,capacity4,base8),NINE consecutive stack DWORDs holding matrix9 floats BY VALUE,RET36. On EXACT count==capacity,grows to2*capacity or16 when capacity0,via4134E0;no >=/overflow guard. Saves oldindex,increments count BEFORE matrix-copy from first stack argument address into base+36*index. Returns old indexEAX. Not a matrix pointer argument. No validation of header,allocation result,orthonormality or finite values;copy failure can leave count incremented.
int __thiscall rf_matrix_array36_append_by_value(
        int *this,
        const float a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10)
{
  int v11; // [esp+0h] [ebp-Ch]
  int v13; // [esp+8h] [ebp-4h]

  if ( *this == *(this + 1) )
  {
    if ( *(this + 1) )
      v11 = 2 * *(this + 1);
    else
      v11 = 16;
    rf_matrix_array36_reallocate_capacity_unchecked(this, v11);
  }
  v13 = (*this)++;
  rf_matrix3_copy((float *)(*(this + 2) + 36 * v13), &a2);
  return v13;
}

