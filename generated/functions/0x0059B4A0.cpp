// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059B4A0 rf_network_classify_local_ipv4_addresses
// UNREALRED VERIFIED [reliable-connections-20261028]: Resolves local hostname through gethostname/gethostbyname,scans h_addr_list with h_length bytes per address. Detects10 first octet,172 with second16..31,192.168,and169.254; breaks byte construction early for these prefixes. Returns1 immediately for a fully constructed nonempty address outside those prefixes and not EXACT127.0.0.1. If no such address but any10/172.16..31/192.168 observed,returns2; otherwise0,including only loopback,only169.254 or lookup failure. Does not test internet reachability,routing,all127/8 loopback addresses or all reserved ranges. No hostent family/length validation; diagnostic string construction uses fixed locals.
int rf_network_classify_local_ipv4_addresses()
{
  bool v1; // [esp+1Ch] [ebp-8DCh]
  bool *v3; // [esp+24h] [ebp-8D4h]
  char *v4; // [esp+38h] [ebp-8C0h]
  bool v5; // [esp+3Ch] [ebp-8BCh]
  bool v6; // [esp+40h] [ebp-8B8h]
  bool v7; // [esp+44h] [ebp-8B4h]
  bool *v9; // [esp+4Ch] [ebp-8ACh]
  char Buffer[1028]; // [esp+50h] [ebp-8A8h] BYREF
  int j; // [esp+454h] [ebp-4A4h]
  struct hostent *v12; // [esp+458h] [ebp-4A0h]
  unsigned int v13; // [esp+45Ch] [ebp-49Ch]
  int i; // [esp+460h] [ebp-498h]
  bool v15; // [esp+467h] [ebp-491h] BYREF
  char v16[1029]; // [esp+468h] [ebp-490h] BYREF
  bool v17; // [esp+86Dh] [ebp-8Bh]
  bool v18; // [esp+86Eh] [ebp-8Ah]
  bool v19; // [esp+86Fh] [ebp-89h]
  char name[128]; // [esp+870h] [ebp-88h] BYREF
  bool v21; // [esp+8F7h] [ebp-1h]

  v17 = 0;
  v21 = 0;
  v15 = 0;
  v19 = 0;
  v18 = 0;
  if ( !gethostname(name, 128) )
  {
    v12 = gethostbyname(name);
    for ( i = 0; v12 && v12->h_addr_list[i]; ++i )
    {
      v16[0] = 0;
      v19 = 0;
      v15 = 0;
      v21 = 0;
      for ( j = 0; j < v12->h_length; ++j )
      {
        if ( j > 0 )
        {
          v9 = &v15;
          while ( *++v9 )
            ;
          *(_WORD *)v9 = 46;
        }
        v13 = (unsigned __int8)v12->h_addr_list[i][j];
        if ( j )
        {
          if ( j == 1 )
          {
            v7 = v15 && v13 >= 0x10 && v13 <= 0x1F;
            v15 = v7;
            if ( v7 )
              break;
            v6 = v19 && v13 == 168;
            v19 = v6;
            if ( v6 )
              break;
            v5 = v18 && v13 == 254;
            v18 = v5;
            if ( v5 )
              break;
          }
        }
        else
        {
          v21 = v13 == 10;
          if ( v13 == 10 )
            break;
          v15 = v13 == 172;
          v19 = v13 == 192;
          v18 = v13 == 169;
        }
        sprintf(Buffer, "%u", v13);
        v4 = &Buffer[strlen(Buffer) + 1];
        v3 = &v15;
        while ( *++v3 )
          ;
        qmemcpy(v3, Buffer, v4 - Buffer);
      }
      v1 = v17 || v21 || v15 || v19;
      v17 = v1;
      if ( !v21 && !v15 && !v19 && !v18 && strcmp(v16, "127.0.0.1") && v16[0] )
        return 1;
    }
  }
  if ( v17 )
    return 2;
  else
    return 0;
}

