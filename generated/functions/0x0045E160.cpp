// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045E160 rf_two_rfstring_array16_reallocate_capacity
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Thiscall array{count0,capacity4,data8},raw requested capacityDWORD stack,RET4. Save oldData;store requested capacity BEFORE allocation. UNSIGNED MUL16 overflow or+4
// header carry ->new sizeFFFFFFFF;otherwise16*request+4. NonNULL block header=request,EH vector constructor for ALL capacity slots,stride16,using native two-RFString
// constructor/destructor;newData=base+4. NULL result ->newDataNULL. Publish newData BEFORE copying signed current live-count records using pair assign45DFF0;does not reduce count or
// check request>=count,positive capacity,NULL data or shrink safety. Then oldData nonNULL ->pair delete45DF80(flags3),destroying HEADER count not used count. Same original SEH
// cleanup chunk as8-byte variant,raw block released on failed construction;no transaction/capacity rollback. Return EAX incidental,not reliable success/newdata. Does not merely grow
// or skip equal sizes.
char *__thiscall rf_two_rfstring_array16_reallocate_capacity(_DWORD *this, int a2)
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
  v2 = (unsigned __int64)(unsigned int)v7 >> 28 != 0 ? -1 : 16 * v7;
  v6 = (char *)operator new(__CFADD__(v2, 4) ? -1 : v2 + 4);
  if ( v6 )
  {
    *(_DWORD *)v6 = v7;
    `eh vector constructor iterator'(
      v6 + 4,
      0x10u,
      v7,
      (void (__thiscall *)(void *))rf_two_rfstring_prefix_construct,
      (void (__thiscall *)(void *))rf_two_rfstring_prefix_destroy);
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
    rf_two_rfstring_assign_from_object((_DWORD *)(*(this + 2) + 16 * i), (int)&v9[16 * i]);
    result = (char *)(i + 1);
  }
  if ( v9 )
    return rf_two_rfstring_delete_with_scalar_or_vector_flags(v9, 3);
  return result;
}

