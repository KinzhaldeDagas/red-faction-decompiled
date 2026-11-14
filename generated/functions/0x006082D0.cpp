// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006082D0 _qsort
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Here invalid(E) means storing errno E, calling
// invalid_parameter(NULL,NULL,NULL,0,0), and returning the stated status only if that handler returns. Cdecl(base, unsigned count, unsigned width, comparator), void in-place
// ascending sort. Reject NULL base with nonzero count, zero width, or NULL comparator via invalid(22), including width/comparator checks when count<2. Admitted count0/1 does no
// sorting. Compute inclusive high=base+width*(count-1) with unchecked 32-bit wrap. Intervals of <=8 elements call shortsort(high EAX, low, width, comparator). Larger intervals
// median-order low/middle/high via comparator and byte swap; scan inward against movable middle pivot, swap crossed candidates and update pivot when it occupied swapped high
// candidate. After crossing, skip equal-pivot tail before choosing partitions. Store deferred larger interval bounds in two 30-entry local pointer arrays, continue smaller interval;
// native signed comparison chooses partition byte-span order while address bounds are unsigned. Pop deferred intervals until stack index becomes negative. No heap allocation,
// recursion, callback exception catch, stable-order promise, product-overflow check or explicit local-stack-depth guard.
void __cdecl qsort(
        void *Base,
        size_t NumOfElements,
        size_t SizeOfElements,
        _CoreCrtNonSecureSearchSortCompareFunction CompareFunction)
{
  char *v4; // ebx
  size_t v5; // edi
  char *v6; // esi
  unsigned int v7; // eax
  char *v8; // edi
  size_t v9; // edx
  char *v10; // eax
  int v11; // ecx
  unsigned int v12; // eax
  unsigned int v13; // edx
  int v14; // ecx
  int v15; // ecx
  int v16; // eax
  char *v17; // edx
  char *v18; // eax
  _DWORD v19[60]; // [esp+8h] [ebp-100h]
  size_t v20; // [esp+F8h] [ebp-10h]
  int v21; // [esp+FCh] [ebp-Ch]
  char *v22; // [esp+100h] [ebp-8h]
  char *v23; // [esp+104h] [ebp-4h]
  char Base_3; // [esp+113h] [ebp+Bh]

  v4 = (char *)Base;
  if ( !Base && NumOfElements )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return;
  }
  v5 = SizeOfElements;
  if ( !SizeOfElements || !CompareFunction )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return;
  }
  if ( NumOfElements >= 2 )
  {
    v6 = (char *)Base + SizeOfElements * (NumOfElements - 1);
    v21 = 0;
    v23 = (char *)Base;
    v22 = v6;
    while ( 1 )
    {
      v7 = (v6 - v4) / v5 + 1;
      if ( v7 <= 8 )
      {
        shortsort(v6, (unsigned int)v4, v5, (int (__cdecl *)(unsigned int, unsigned int))CompareFunction);
        goto LABEL_49;
      }
      v8 = &v4[v5 * (v7 >> 1)];
      if ( CompareFunction(v4, v8) > 0 )
        swap(v4, SizeOfElements, v8);
      if ( CompareFunction(v4, v6) > 0 )
        swap(v4, SizeOfElements, v6);
      if ( CompareFunction(v8, v6) > 0 )
        swap(v8, SizeOfElements, v6);
      while ( 1 )
      {
        if ( v8 > v4 )
        {
          while ( 1 )
          {
            v4 += SizeOfElements;
            if ( v4 >= v8 )
              break;
            if ( CompareFunction(v4, v8) > 0 )
            {
              if ( v8 > v4 )
                goto LABEL_24;
              goto LABEL_22;
            }
          }
        }
        do
LABEL_22:
          v4 += SizeOfElements;
        while ( v4 <= v22 && CompareFunction(v4, v8) <= 0 );
        do
LABEL_24:
          v6 -= SizeOfElements;
        while ( v6 > v8 && CompareFunction(v6, v8) > 0 );
        if ( v4 > v6 )
          break;
        v9 = SizeOfElements;
        v10 = v6;
        if ( v4 != v6 )
        {
          v11 = v4 - v6;
          do
          {
            v20 = v9 - 1;
            Base_3 = v10[v11];
            v10[v11] = *v10;
            *v10 = Base_3;
            v9 = v20;
            ++v10;
          }
          while ( v20 );
        }
        if ( v8 == v6 )
          v8 = v4;
      }
      v6 += SizeOfElements;
      if ( v8 >= v6 )
        goto LABEL_36;
      do
      {
        v6 -= SizeOfElements;
        if ( v6 <= v8 )
          goto LABEL_36;
      }
      while ( !CompareFunction(v6, v8) );
      if ( v8 < v6 )
      {
LABEL_38:
        v12 = (unsigned int)v23;
      }
      else
      {
LABEL_36:
        while ( 1 )
        {
          v6 -= SizeOfElements;
          v12 = (unsigned int)v23;
          if ( v6 <= v23 )
            break;
          if ( CompareFunction(v6, v8) )
            goto LABEL_38;
        }
      }
      v13 = (unsigned int)v22;
      if ( (int)&v6[-v12] < v22 - v4 )
      {
        if ( v4 < v22 )
        {
          v15 = v21;
          v19[v21 + 30] = v4;
          v19[v15] = v13;
          v21 = v15 + 1;
        }
        if ( v12 >= (unsigned int)v6 )
          goto LABEL_48;
        v4 = v23;
        v5 = SizeOfElements;
        v22 = v6;
      }
      else
      {
        if ( v12 < (unsigned int)v6 )
        {
          v14 = v21;
          v19[v21 + 30] = v12;
          v19[v14] = v6;
          v21 = v14 + 1;
        }
        if ( (unsigned int)v4 >= v13 )
        {
LABEL_48:
          v5 = SizeOfElements;
LABEL_49:
          v16 = --v21;
          if ( v21 < 0 )
            return;
          v17 = (char *)v19[v16 + 30];
          v18 = (char *)v19[v16];
          v23 = v17;
          v22 = v18;
          v4 = v17;
          v6 = v18;
        }
        else
        {
          v6 = v22;
          v5 = SizeOfElements;
          v23 = v4;
        }
      }
    }
  }
}

