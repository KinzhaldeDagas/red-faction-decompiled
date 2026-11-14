// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413630 rf_array24_reallocate_capacity_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): ECX header(count0,capacity4,base8) plus requested capacity DWORD,RET4. Storescapacity before allocation;allocates24*UNSIGNEDcapacity bytes,with MUL overflow saturating allocation request toUINT32_MAX;nonNULL construction iterator uses stride24 and no-op vector-prefix constructor (which writes NO record bytes). Publishes newbase8,copies FULL old signed count through413740 at24-byte strides,then deletes oldbase if nonNULL. Count unchanged;no clamp to smaller requested capacity,negative/NULL check or per-element ownership. Spare records uninitialized. This operation does not initialize radius or tail floats;constructor default only calls no-op vector prefix. Allocation/constructor
// exception cleanup exists but no restoration of changed capacity.
void __thiscall rf_array24_reallocate_capacity_unchecked(int *this, int a2)
{
  int v2; // [esp+4h] [ebp-2Ch]
  char *v4; // [esp+10h] [ebp-20h]
  int v5; // [esp+18h] [ebp-18h]
  int i; // [esp+1Ch] [ebp-14h]
  float *v7; // [esp+20h] [ebp-10h]

  v7 = (float *)*(this + 2);
  *(this + 1) = a2;
  v5 = *(this + 1);
  v4 = (char *)operator new(24 * v5);
  if ( v4 )
  {
    rf_vector_construct_no_unwind(v4, 0x18u, v5, rf_vector_prefix_construct_noop);
    v2 = (int)v4;
  }
  else
  {
    v2 = 0;
  }
  *(this + 2) = v2;
  for ( i = 0; i < *this; ++i )
    rf_record24_copy_six_floats((float *)(*(this + 2) + 24 * i), &v7[6 * i]);
  if ( v7 )
    operator delete(v7);
}

