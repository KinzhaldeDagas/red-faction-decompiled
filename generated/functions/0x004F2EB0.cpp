// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F2EB0 rf_build_version_get_string_pointers
// UNREALRED VERIFIED [save-validation-20261028]: If nonnull, first output receives pointer0x88E788 and second receives pointer0x88E688. Returns pointers by assignment, does not copy strings; no boolean-success return contract established.
_DWORD *__cdecl rf_build_version_get_string_pointers(_DWORD *a1, _DWORD *a2)
{
  _DWORD *result; // eax

  if ( a1 )
  {
    result = a1;
    *a1 = unk_88E788;
  }
  if ( a2 )
    *a2 = &unk_88E688;
  return result;
}

