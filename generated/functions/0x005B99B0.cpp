// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B99B0 rf_mesh_find_named_sphere_prefix
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): ECX mesh record plus name, RET4. NULL name returns-1; loops sphere count96 over44byte records from100, comparing _strnicmp(recordStart,name,strlen(name)). Returns first prefix match, so empty name matches first existing record. No full-equality/case-sensitive requirement or pointer validation.
// UNREALRED VERIFIED [combat-named-sphere-binding-20261112]: ECX meshcount+60/records+64 stride2C; loops ascending, __strnicmp(recordName,authoredName,strlen(authoredName)) at5B9A20. NULLname returns-1; emptyname matches first existing sphere. Locale-dependent nonASCII CRT comparison has not been proved equivalent to host Unicode comparison.
int __thiscall rf_mesh_find_named_sphere_prefix(_DWORD *this, char *String2)
{
  int i; // [esp+14h] [ebp-4h]

  if ( !String2 )
    return -1;
  for ( i = 0; i < *(this + 24); ++i )
  {
    if ( !_strnicmp((const char *)(*(this + 25) + 44 * i), String2, strlen(String2)) )
      return i;
  }
  return -1;
}

