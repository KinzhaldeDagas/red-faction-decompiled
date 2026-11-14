// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413270 rf_vector_array12_append_by_value
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): ECX array header(count0,capacity4,base8),THREE consecutive stack DWORDs holding vectorXYZ BY VALUE,RET12. If count==capacity EXACTLY,grows capacity to2*oldCapacity when nonzero,otherwise16,using4133D0;no signed/full>= or overflow guard. Saves oldcount asindex,increments count BEFORE copying vector from stack argument area into base+12*index via vector-copy helper. Returns old indexEAX. Does not take source vector pointer,check allocation success,clamp invalid count/capacity or protect an already oversized header;failed copy can leave count incremented.
int __thiscall rf_vector_array12_append_by_value(_DWORD *this, float source, int a3, int a4)
{
  int v5; // [esp+0h] [ebp-18h]
  float copy_result[3]; // [esp+8h] [ebp-10h] BYREF
  int v8; // [esp+14h] [ebp-4h]

  if ( *this == *(this + 1) )
  {
    if ( *(this + 1) )
      v5 = 2 * *(this + 1);
    else
      v5 = 16;
    rf_vector_array12_reallocate_capacity_unchecked(this, v5);
  }
  v8 = (*this)++;
  rf_vector_copy((float *)(*(this + 2) + 12 * v8), copy_result, &source);
  return v8;
}

