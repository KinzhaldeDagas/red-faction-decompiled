// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004134E0 rf_matrix_array36_reallocate_capacity_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): ECX array header plus requested capacity DWORD,RET4,SEH cleanup. Saves oldbase;setscapacity4 before allocating36*UNSIGNEDcapacity bytes;MUL overflow saturates allocation request toUINT32_MAX instead of wrapping to a small size. On nonNULL pointer runs constructor iterator stride36/count using matrix constructor that writes NO matrix bytes. Publishes newbase8,copies FULL signed oldcount matrices with matrix-copy,then operator-deletes oldbase when nonNULL. Count unchanged;shrinking below count does not truncate or bound copies;no NULL allocation,negative count/capacity or matrix validity guard. Spare matrix storage remains uninitialized. Exception cleanup may free newly allocated
// storage;capacity mutation is not rolled back here. No element destructors or external pointee ownership.
void __thiscall rf_matrix_array36_reallocate_capacity_unchecked(int *this, int a2)
{
  int v2; // [esp+4h] [ebp-2Ch]
  char *v4; // [esp+10h] [ebp-20h]
  int v5; // [esp+18h] [ebp-18h]
  int i; // [esp+1Ch] [ebp-14h]
  float *v7; // [esp+20h] [ebp-10h]

  v7 = (float *)*(this + 2);
  *(this + 1) = a2;
  v5 = *(this + 1);
  v4 = (char *)operator new(36 * v5);
  if ( v4 )
  {
    rf_vector_construct_no_unwind(v4, 0x24u, v5, (void *(__thiscall *)(void *))rf_matrix3_construct);
    v2 = (int)v4;
  }
  else
  {
    v2 = 0;
  }
  *(this + 2) = v2;
  for ( i = 0; i < *this; ++i )
    rf_matrix3_copy((float *)(*(this + 2) + 36 * i), &v7[9 * i]);
  if ( v7 )
    operator delete(v7);
}

