// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E330 rf_vpackfile_set_external_root_path
// UNREALRED VERIFIED [save-validation-20261028]: If input nonnull, copies entire C string to global0x1898C90 without capacity check. Null performs no copy. Return register is incidental, not a verified status contract. CD-root setter supplies drive root here.
char *__cdecl rf_vpackfile_set_external_root_path(char *a1)
{
  char v1; // dl
  char *result; // eax
  int *v3; // [esp+8h] [ebp-8h]
  char *v4; // [esp+Ch] [ebp-4h]

  if ( a1 )
  {
    v4 = a1;
    v3 = &dword_1898C90;
    do
    {
      v1 = *v4;
      *(_BYTE *)v3 = *v4;
      result = ++v4;
      v3 = (int *)((char *)v3 + 1);
    }
    while ( v1 );
  }
  return result;
}

