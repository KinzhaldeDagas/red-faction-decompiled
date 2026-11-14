// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00549FD0 rf_dword_array_reallocate_capacity_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Saves old backing8,sets capacity4=requested EXACT value,allocates4*capacity bytes,stores new backing,copies old count0 DWORDs,then deletes old backing if nonNULL. Count unchanged,unused slots uninitialized. No shrink/count,negative,32-bit multiplication-overflow or NULL guard;capacity<count overflows destination. Allocation exception leaves capacity changed with old pointer;used by append helper under its normal count==capacity growth invariant.
void __thiscall rf_dword_array_reallocate_capacity_unchecked(_DWORD *this, int a2)
{
  int i; // [esp+10h] [ebp-8h]
  _DWORD *v4; // [esp+14h] [ebp-4h]

  v4 = (_DWORD *)*(this + 2);
  *(this + 1) = a2;
  *(this + 2) = operator new(4 * *(this + 1));
  for ( i = 0; i < *this; ++i )
    *(_DWORD *)(*(this + 2) + 4 * i) = v4[i];
  if ( v4 )
    operator delete(v4);
}

