// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CD1C _bsearch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Here invalid(E) means storing errno E, calling
// invalid_parameter(NULL,NULL,NULL,0,0), and returning the stated status only if that handler returns. Cdecl(key, base, unsigned count, unsigned width, comparator), returns matching
// element pointer or NULL. Computes high=base+width*(count-1) with unchecked wrap BEFORE validation. Reject NULL base with nonzero count, width0 or NULL comparator via invalid(22);
// key itself is not checked and can be NULL for caller comparator policy. Search while unsigned low<=high and count nonzero. For count>=2 use half=count>>1; choose middle index half
// for odd counts, half-1 for even counts (lower middle). comparator(key,middle)==0 returns that element; signed negative sets high=middle-width and count=half for odd or half-1 for
// even; positive sets low=middle+width,count=half. Last element compared once; miss/empty returns NULL without mutation. Count0 still validates width/comparator; no count*width
// overflow, storage-range or sortedness check. Duplicate match is whichever midpoint is reached, not guaranteed first.
void *__cdecl bsearch(
        const void *Key,
        const void *Base,
        size_t NumOfElements,
        size_t SizeOfElements,
        _CoreCrtNonSecureSearchSortCompareFunction CompareFunction)
{
  size_t v5; // eax
  char *v6; // esi
  size_t v8; // ebx
  bool v9; // zf
  size_t v10; // eax
  char *v11; // edi
  int v12; // eax
  size_t NumOfElementsa; // [esp+18h] [ebp+10h]

  v5 = NumOfElements;
  v6 = (char *)Base + SizeOfElements * (NumOfElements - 1);
  if ( !Base && NumOfElements || !SizeOfElements || !CompareFunction )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return nullptr;
  }
  if ( Base > v6 )
    return nullptr;
  while ( 1 )
  {
    v8 = v5 >> 1;
    if ( !(v5 >> 1) )
      break;
    v9 = (v5 & 1) == 0;
    NumOfElementsa = v5 & 1;
    v10 = v5 >> 1;
    if ( v9 )
      v10 = v8 - 1;
    v11 = (char *)Base + SizeOfElements * v10;
    v12 = CompareFunction(Key, v11);
    if ( !v12 )
      return v11;
    if ( v12 >= 0 )
    {
      Base = &v11[SizeOfElements];
LABEL_16:
      v5 = v8;
      goto LABEL_17;
    }
    v6 = &v11[-SizeOfElements];
    if ( NumOfElementsa )
      goto LABEL_16;
    v5 = v8 - 1;
LABEL_17:
    if ( Base > v6 )
      return nullptr;
  }
  if ( !v5 )
    return nullptr;
  return CompareFunction(Key, Base) == 0 ? (void *)Base : nullptr;
}

