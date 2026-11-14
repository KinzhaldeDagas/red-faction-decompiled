// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539860 rf_record16_array_reallocate_capacity_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Sets capacity4=requested EXACT value,allocates16*capacity bytes with32-bit arithmetic,stores new backing8,copies old count0 records as fourDWORDs each,then deletes old backing if nonNULL. Count unchanged,new unused slots uninitialized,no element ctor/dtor. No max(oldCount,capacity),NULL or multiplication-overflow guards;shrinking below count writes beyond new allocation. Capacity committed before allocation;throw leaves changed capacity with old pointer,nonthrow NULL leads copy toNULL for positive count.
void __thiscall rf_record16_array_reallocate_capacity_unchecked(_DWORD *this, int a2)
{
  char *v2; // edx
  _DWORD *v3; // ecx
  int i; // [esp+Ch] [ebp-8h]
  char *v6; // [esp+10h] [ebp-4h]

  v6 = (char *)*(this + 2);
  *(this + 1) = a2;
  *(this + 2) = operator new(16 * *(this + 1));
  for ( i = 0; i < *this; ++i )
  {
    v2 = &v6[16 * i];
    v3 = (_DWORD *)(16 * i + *(this + 2));
    *v3 = *(_DWORD *)v2;
    v3[1] = *((_DWORD *)v2 + 1);
    v3[2] = *((_DWORD *)v2 + 2);
    v3[3] = *((_DWORD *)v2 + 3);
  }
  if ( v6 )
    operator delete(v6);
}

