// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004171A0 rf_clutter_skin_array_reallocate_capacity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Thiscall header plus requestedcapacity,RET4. Saves oldbase;storesnewcapacity4 BEFORE allocation. Computes108*UNSIGNEDcapacity with MUL overflow saturation toUINT32_MAX,then adds4-byte cookie with carry saturation as well. Allocates totalbytes;nonNULL storesrequestedcapacity cookie at rawbase,EH-constructs ALL capacity records with416D40,sets usablebase=raw+4. Publishes headerbase8;assigns FULL signed oldcount records via417140 (no min with newcapacity),then if oldbase nonNULL calls4170D0(oldbase,3),destroying ALL OLD COOKIE capacity records and freeing rawbase-4. Logicalcount unchanged. No shrink/count/negative/NULL copy guard;spare records have emptystrings but UNINITIALIZED
// count8. Exceptions have construction cleanup but changedcapacity is not restored;returnEAX incidental branch value,not capacity/success.
char *__thiscall rf_clutter_skin_array_reallocate_capacity(_DWORD *this, int a2)
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
  v2 = (108 * (unsigned __int64)(unsigned int)v7) >> 32 != 0 ? -1 : 108 * v7;
  v6 = (char *)operator new(__CFADD__(v2, 4) ? -1 : v2 + 4);
  if ( v6 )
  {
    *(_DWORD *)v6 = v7;
    `eh vector constructor iterator'(
      v6 + 4,
      0x6Cu,
      v7,
      (void (__thiscall *)(void *))rf_clutter_skin108_construct_strings,
      (void (__thiscall *)(void *))rf_clutter_skin108_destroy_strings);
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
    rf_clutter_skin108_assign((_DWORD *)(*(this + 2) + 108 * i), (int)&v9[108 * i]);
    result = (char *)(i + 1);
  }
  if ( v9 )
    return rf_clutter_skin108_deleting_destructor(v9, 3);
  return result;
}

