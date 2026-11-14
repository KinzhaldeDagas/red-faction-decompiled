// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004133D0 rf_vector_array12_reallocate_capacity_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): ECX array header plus requested capacity DWORD,RET4,SEH construction cleanup. Saves oldbase;stores NEW capacity4 BEFORE allocation. Computes UNSIGNED12*capacity with MUL;on overflow passes UINT32_MAX bytes to operator-new,otherwise exact product,invokes constructor iterator stride12/requestedcount with NO-OP vector ctor if pointer nonNULL,publishes newbase8,then copies FULL signed oldcount records using vector-copy and frees oldbase via operator-delete if nonNULL. Count0 unchanged;no min(count,newCapacity),shrink truncation,negative-capacity or copy/NULL guard;allocation-size overflow saturation does not validate requested capacity/count. Thus shrinking below count still copies
// too many records;NULL allocation with positive count reaches copy throughNULL,while count<=0 can publishNULL and deleteold. Spare elements remain uninitialized. Allocation/constructor exceptions have native cleanup but capacity was already changed;no strong state rollback promised. No per-element old destructors or pointer ownership.
void __thiscall rf_vector_array12_reallocate_capacity_unchecked(int *this, int a2)
{
  void *v2; // [esp+4h] [ebp-38h]
  float copy_result[3]; // [esp+10h] [ebp-2Ch] BYREF
  void *v5; // [esp+1Ch] [ebp-20h]
  void *v6; // [esp+20h] [ebp-1Ch]
  int v7; // [esp+24h] [ebp-18h]
  int i; // [esp+28h] [ebp-14h]
  float *v9; // [esp+2Ch] [ebp-10h]
  int v10; // [esp+38h] [ebp-4h]

  v9 = (float *)*(this + 2);
  *(this + 1) = a2;
  v7 = *(this + 1);
  v5 = operator new(12 * v7);
  v10 = 0;
  if ( v5 )
  {
    rf_vector_construct_no_unwind((char *)v5, 0xCu, v7, rf_vector3_default_construct_noop);
    v2 = v5;
  }
  else
  {
    v2 = nullptr;
  }
  v6 = v2;
  v10 = -1;
  *(this + 2) = (int)v2;
  for ( i = 0; i < *this; ++i )
    rf_vector_copy((float *)(*(this + 2) + 12 * i), copy_result, &v9[3 * i]);
  if ( v9 )
    operator delete(v9);
}

