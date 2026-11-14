// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045E020 rf_rfstring_array8_reallocate_capacity
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Thiscall array{count0,capacity4,data8},raw requested capacityDWORD stack,RET4,existing SEH chunks retained. Save old data pointer;store capacity=request BEFORE
// allocation. Compute UNSIGNED request*8 with MUL overflow,then+4 header carry;either overflow saturates operator-new size toFFFFFFFF,not wrapped-small allocation. NonNULL allocation
// stores HEADER=request,EH vector-constructs ALL capacity slots as empty8-byte RFStrings with destructor callback,then data=base+4;NULL allocation sets new dataNULL. Publish data
// BEFORE copying;for signed i=0..<CURRENT live count,assign oldData[i] into newData[i]. No request>=count,positive-capacity,NULL-copy or shrink guard;count unchanged. After copies
// oldData nonNULL ->delete flags3,which destroys header-count old slots and frees old allocation. Shared SEH cleanup releases failed-construction raw allocation;no capacity rollback
// in body,capacity already changed if allocation/constructor throws. Does not use realloc/move pointers or skip equal capacities. EAX incidental new pointer/copy loop/old delete
// residue,not uniform success/capacity.
char *__thiscall rf_rfstring_array8_reallocate_capacity(_DWORD *this, int a2)
{
  int v2; // ecx
  char *result; // eax
  char *v4; // [esp+8h] [ebp-30h]
  char *v6; // [esp+18h] [ebp-20h]
  int v7; // [esp+20h] [ebp-18h]
  int i; // [esp+24h] [ebp-14h]
  char *v9; // [esp+28h] [ebp-10h]

  v9 = (char *)*(this + 2);
  *(this + 1) = a2;
  v7 = *(this + 1);
  v2 = (unsigned __int64)(unsigned int)v7 >> 29 != 0 ? -1 : 8 * v7;
  v6 = (char *)operator new(__CFADD__(v2, 4) ? -1 : v2 + 4);
  if ( v6 )
  {
    *(_DWORD *)v6 = v7;
    `eh vector constructor iterator'(
      v6 + 4,
      8u,
      v7,
      (void (__thiscall *)(void *))rf_string_construct_empty,
      rf_string_destroy_buffer);
    v4 = v6 + 4;
  }
  else
  {
    v4 = nullptr;
  }
  result = v4;
  *(this + 2) = v4;
  for ( i = 0; i < *this; ++i )
  {
    rf_string_assign_from_object((_DWORD *)(*(this + 2) + 8 * i), (int)&v9[8 * i]);
    result = (char *)(i + 1);
  }
  if ( v9 )
    return rf_rfstring_delete_with_scalar_or_vector_flags(v9, 3);
  return result;
}

