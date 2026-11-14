// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005600E0 rf_string_concat_two_objects
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Cdecl output object, left object, right object. Reserves sum of stored extents. If sum nonzero, copies right directly when left extent<=0; otherwise copies left and appends right only when right extent>0. Copy-constructs output from temporary, destroys temporary, returns output pointer. Inputs unchanged. No extent-sum overflow/capacity/buffer validation; output stored extent is recomputed from resulting C string.
_DWORD *__cdecl rf_string_concat_two_objects(_DWORD *a1, int *a2, int a3)
{
  char v3; // dl
  char v4; // cl
  char *v6; // [esp+14h] [ebp-4Ch]
  char *v7; // [esp+18h] [ebp-48h]
  char *v8; // [esp+40h] [ebp-20h]
  char *v9; // [esp+44h] [ebp-1Ch]
  char *v10; // [esp+4Ch] [ebp-14h] BYREF
  char *v11; // [esp+50h] [ebp-10h]
  int v12; // [esp+5Ch] [ebp-4h]

  rf_string_construct_reserved_extent(&v10, *(_DWORD *)a3 + *a2);
  v12 = 1;
  if ( v10 )
  {
    if ( *a2 <= 0 )
    {
      v7 = *(char **)(a3 + 4);
      v6 = v11;
      do
      {
        v4 = *v7;
        *v6++ = *v7++;
      }
      while ( v4 );
    }
    else
    {
      v9 = (char *)a2[1];
      v8 = v11;
      do
      {
        v3 = *v9;
        *v8++ = *v9++;
      }
      while ( v3 );
      if ( *(int *)a3 > 0 )
        qmemcpy(
          &v11[strlen(v11)],
          *(const void **)(a3 + 4),
          *(_DWORD *)(a3 + 4) + strlen(*(const char **)(a3 + 4)) + 1 - *(_DWORD *)(a3 + 4));
    }
  }
  rf_string_copy_construct_from_object(a1, &v10);
  LOBYTE(v12) = 0;
  rf_string_destroy_buffer(&v10);
  return a1;
}

