// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574E30 rf_bitmap_is_named_placeholder_or_global_missing_state
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl(unsigned handle),returnsBYTE. HandleFFFFFFFF returns raw global byte189744E directly without resolving. Other handles resolve current record and return1 iff file-type DWORD+52==3 AND name atrecord0 differs case-insensitively from USERBMAP. Thus known named missing-texture placeholders qualify,but ordinary USERBMAP-created records do not. No file probe or generation/resolver-minus-one guard;special global-byte result is not normalized.
unsigned __int8 __cdecl rf_bitmap_is_named_placeholder_or_global_missing_state(unsigned int handle)
{
  char *String1; // [esp+4h] [ebp-4h]

  if ( handle == -1 )
    return byte_189744E;
  String1 = (char *)(dword_1897344 + 108 * rf_bitmap_resolve_current_frame_slot(handle));
  return *((_DWORD *)String1 + 13) == 3 && _stricmp(String1, "USERBMAP");
}

