// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486850 rf_bitmap_prefix_to_material_index
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl NUL-terminated bitmap name. strchr finds FIRST underscore; absent underscore returns0, even when complete name equals a configured prefix. Copies exactly bytes before
// underscore into stack char[260] with strncpy and explicit NUL; no local length<=259 guard, no path/basename/extension stripping or input NULL check. Empty prefix before a leading
// underscore can match an authored empty prefix. Walks registry0x70046C in insertion order, dereferences12-byte entries, obtains their RFString C strings, compares exact
// case-insensitive prefix with _stricmp; first match returns unsigned BYTE entry+8. Unmatched0. Does not mutate cache itself or choose longest prefix.
int __cdecl rf_bitmap_prefix_to_material_index(const char *bitmap_name)
{
  const void **v2; // eax
  const char *v3; // eax
  int i; // [esp+0h] [ebp-114h]
  char *v5; // [esp+4h] [ebp-110h]
  char Destination[260]; // [esp+Ch] [ebp-108h] BYREF

  v5 = strchr(bitmap_name, 95);
  if ( !v5 )
    return 0;
  strncpy(Destination, bitmap_name, v5 - bitmap_name);
  Destination[v5 - bitmap_name] = 0;
  for ( i = 0; i < rf_receiver_get_first_dword(rf_material_bitmap_prefix_registry); ++i )
  {
    v2 = (const void **)sub_552200(rf_material_bitmap_prefix_registry, i);
    v3 = rf_string_object_c_str_or_empty(*v2);
    if ( !_stricmp(Destination, v3) )
      return *(unsigned __int8 *)(*(_DWORD *)sub_552200(rf_material_bitmap_prefix_registry, i) + 8);
  }
  return 0;
}

