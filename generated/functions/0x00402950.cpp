// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402950 sub_402950
// UNREALRED VERIFIED [ai-health-goals-20261028] Scans named waypoint-list storage at0x700480, stride0x20C, count0x700478. Compares the case-insensitive prefix of each list name of length strlen(request), using0x55F990. Thus literal health admits health-prefixed list names, not only exact health. Collects at most32 matching list indices, selects rand()%count, passes chosen index and flags0 to0x4028C0. Only success requests numericmode4 and ownerflags0x800008. This is not nearest-health-pickup enumeration.
void __cdecl sub_402950(int *a1, char *String2)
{
  void *v2; // [esp+4h] [ebp-C8h]
  _BYTE v3[11]; // [esp+1Ch] [ebp-B0h] BYREF
  bool v4; // [esp+27h] [ebp-A5h]
  int v5; // [esp+2Ch] [ebp-A0h]
  int v6; // [esp+30h] [ebp-9Ch]
  char **v7; // [esp+34h] [ebp-98h]
  _DWORD v8[32]; // [esp+38h] [ebp-94h]
  int i; // [esp+B8h] [ebp-14h]
  int v10; // [esp+BCh] [ebp-10h]
  int v11; // [esp+C8h] [ebp-4h]

  v10 = 0;
  for ( i = 0; i < unk_700478; ++i )
  {
    v7 = (char **)&unk_700480[131 * i];
    v2 = rf_string_left_count(v7, v3, strlen(String2));
    v11 = 0;
    v4 = rf_string_equals_case_insensitive((int)v2, String2);
    v11 = -1;
    rf_string_destroy_buffer(v3);
    if ( v4 )
    {
      v8[v10++] = i;
      if ( v10 == 32 )
        break;
    }
  }
  if ( v10 )
  {
    v5 = rand() % v10;
    v6 = v8[v5];
    if ( sub_4028C0(a1, v6, 0) )
    {
      rf_ai_numeric_mode_write(a1, 4, -1, -1);
      a1[332] |= (unsigned int)&unk_800008;
    }
  }
}

