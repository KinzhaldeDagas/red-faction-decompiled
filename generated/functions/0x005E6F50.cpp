// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6F50 rf_string_pool_copy_c_string
// UNREALRED VERIFIED [string-pool-stream-20261028]: Thiscall pool,input C string. NULL input returns0 without mutation. Computes strlen,input destination=base+used bytes+12,copies through NUL,adds length+1 to used bytes and increments string count+16. Capacity+8 is NOT consulted; no reallocation,deduplication,overlap or base-pointer checks. Returns pointer into pool allocation,invalidated when pool released. Existing name retained; expanded layout verified from constructors and intern method.
int __thiscall rf_string_pool_copy_c_string(_DWORD *this, const char *a2)
{
  char v3; // al
  _BYTE *v4; // [esp+8h] [ebp-24h]
  const char *v5; // [esp+Ch] [ebp-20h]
  int v6; // [esp+24h] [ebp-8h]
  unsigned int v7; // [esp+28h] [ebp-4h]

  if ( !a2 )
    return 0;
  v7 = strlen(a2);
  v6 = *(this + 3) + *this;
  v5 = a2;
  v4 = (_BYTE *)v6;
  do
  {
    v3 = *v5;
    *v4++ = *v5++;
  }
  while ( v3 );
  *(this + 3) += v7 + 1;
  ++*(this + 4);
  return v6;
}

