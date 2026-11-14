// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059DC60 rf_registry_resolve_root_and_subkey
// UNREALRED VERIFIED [registry-config-20261028]: Arguments writable subkey output,optional section string. Default root HKCU0x80000001. Null section copies global base path0x1C0D1C8. Nonnull section without case-insensitive first4 bytes hkey appends backslash+section to base. hkey prefix branch copies root token up to backslash/NUL into zeroed256-byte local,parses0x59DF40,and copies remainder starting ONE BYTE AFTER stop into output. Missing backslash therefore reads beyond terminating NUL. No output capacity,root-token bound,base readiness or leading/trailing separator normalization.
int __cdecl rf_registry_resolve_root_and_subkey(char *a1, char *String1)
{
  char v3; // [esp+Bh] [ebp-151h]
  char *v4; // [esp+10h] [ebp-14Ch]
  char *v5; // [esp+14h] [ebp-148h]
  char v6; // [esp+3Fh] [ebp-11Dh]
  char *v7; // [esp+44h] [ebp-118h]
  char *v8; // [esp+48h] [ebp-114h]
  char *v9; // [esp+4Ch] [ebp-110h]
  char *v10; // [esp+4Ch] [ebp-110h]
  char *v11; // [esp+50h] [ebp-10Ch]
  char *v12; // [esp+50h] [ebp-10Ch]
  char v13[256]; // [esp+54h] [ebp-108h] BYREF
  int v14; // [esp+158h] [ebp-4h]

  v14 = -2147483647;
  if ( String1 )
  {
    if ( !_strnicmp(String1, "hkey", 4u) )
    {
      memset(v13, 0, sizeof(v13));
      v9 = String1;
      v11 = v13;
      while ( *v9 && *v9 != 92 )
        *v11++ = *v9++;
      v14 = rf_registry_parse_predefined_root(v13);
      v10 = v9 + 1;
      v12 = a1;
      while ( *v10 )
        *v12++ = *v10++;
      *v12 = 0;
    }
    else
    {
      v8 = (char *)&unk_1C0D1C8;
      v7 = a1;
      do
      {
        v6 = *v8;
        *v7++ = *v8++;
      }
      while ( v6 );
      *(_WORD *)&a1[strlen(a1)] = 92;
      strcat(a1, String1);
    }
  }
  else
  {
    v5 = (char *)&unk_1C0D1C8;
    v4 = a1;
    do
    {
      v3 = *v5;
      *v4++ = *v5++;
    }
    while ( v3 );
  }
  return v14;
}

