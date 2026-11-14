// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059BA10 rf_network_format_endpoint_text
// UNREALRED VERIFIED [reliable-connections-20261028]: Arguments destination,IGNORED capacity,endpoint. Reads endpoint DWORD IPv4 and WORD port+4,byte-swaps IPv4 with ntohl for inet_ntoa,formats IP: dotted.address:port into68-byte local,then copies including NUL to destination without capacity check. No allocation,null checks or required-length return. EAX is incidental copy-loop value,not a reliable string pointer despite decompiler prototype.
char *__cdecl rf_network_format_endpoint_text(_BYTE *a1, int a2, u_long *a3)
{
  u_long v3; // edx
  char *v4; // eax
  char *result; // eax
  int v6; // [esp-4h] [ebp-68h]
  char *v8; // [esp+Ch] [ebp-58h]
  char Buffer[68]; // [esp+14h] [ebp-50h] BYREF
  u_long netlong; // [esp+5Ch] [ebp-8h]
  u_long v11; // [esp+60h] [ebp-4h]

  v3 = a3[1];
  netlong = *a3;
  v11 = v3;
  netlong = ntohl(netlong);
  v6 = *((unsigned __int16 *)a3 + 2);
  v4 = inet_ntoa((struct in_addr)netlong);
  sprintf(Buffer, "IP: %s:%d", v4, v6);
  v8 = Buffer;
  do
  {
    result = v8;
    LOBYTE(result) = *v8;
    *a1++ = *v8++;
  }
  while ( (_BYTE)result );
  return result;
}

