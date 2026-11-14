// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FA520 rf_bluebeard_sound_metadata_load
// UNREALRED VERIFIED [mission-mover-effects-20261013] Loads auxiliary sound metadata from bluebeard.bty, up to4096 records of180 bytes. +Looping Sound sets record+0xA8 bit0x40000000; +Loop Start occupies low27 bits. +Music Track is separate record+0xAC bit0x20000000. Records are sorted with0x5FA4A0. These flags are authored sound metadata, not VPP streaming options.
// UNREALRED VERIFIED [combat-native-pickup-source-20261111] Missing bluebeard open returns-1 BEFORE5FACE0 clears the metadata registry. Successful open enters reset/parse. Therefore source-local absence can use the default metadata record only in a known registry state; unreadable/invalid/index-unavailable is not a proved missing-file result. Host source-epoch rebind/cache lifecycle is an explicit adapter; do not claim native reload/partial-parse retention parity.
int rf_bluebeard_sound_metadata_load()
{
  unsigned int v1; // ecx
  char v2; // [esp+13h] [ebp-2FDh]
  _BYTE *v3; // [esp+18h] [ebp-2F8h]
  char *v4; // [esp+1Ch] [ebp-2F4h]
  char v5; // [esp+23h] [ebp-2EDh]
  char *v6; // [esp+28h] [ebp-2E8h]
  char *v7; // [esp+2Ch] [ebp-2E4h]
  char *first_free_slot; // [esp+70h] [ebp-2A0h]
  char v9[40]; // [esp+74h] [ebp-29Ch] BYREF
  char Destination[80]; // [esp+9Ch] [ebp-274h] BYREF
  char String2[256]; // [esp+ECh] [ebp-224h] BYREF
  void *self[69]; // [esp+1ECh] [ebp-124h] BYREF
  int v13; // [esp+30Ch] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v13 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "bluebeard.bty", byte_98967F, 0) )
  {
    v13 = -1;
    rf_memory_text_parser_destroy_buffer_adapter(self);
    return -1;
  }
  else
  {
    rf_bluebeard_metadata_clear_tables();
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Sound Root:");
    rf_text_parser_read_delimited_cstring((int)self, unk_1F6D250, 219, 34, 34);
    if ( *(_BYTE *)(&unk_1F6D250[strlen(unk_1F6D250) + 1] - (char *)&unk_1F6D251 + 32952911) != 92 )
      *(_WORD *)&unk_1F6D250[strlen(unk_1F6D250)] = 92;
    rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$PS2 Sound Root:");
    rf_text_parser_read_delimited_cstring((int)self, unk_1F6D170, 219, 34, 34);
    if ( *(_BYTE *)(&unk_1F6D170[strlen(unk_1F6D170) + 1] - (char *)&unk_1F6D171 + 32952687) != 92 )
      *(_WORD *)&unk_1F6D170[strlen(unk_1F6D170)] = 92;
    unk_1F6D168 = rf_text_parser_try_consume_case_insensitive_prefix(
                    (const char **)self,
                    "+Use Flat Directory Layout for PS2 Sounds");
    while ( rf_text_parser_peek_case_insensitive_prefix((int)self, "$Folder:") )
    {
      rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Folder:");
      rf_text_parser_read_delimited_cstring((int)self, String2, 256, 34, 34);
      if ( rf_bluebeard_metadata_add_group_name(String2) < 0 )
      {
        v13 = -1;
        rf_memory_text_parser_destroy_buffer_adapter(self);
        return -1;
      }
    }
    while ( rf_text_parser_peek_case_insensitive_prefix((int)self, "$Sound:") )
    {
      rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Sound:");
      rf_text_parser_read_delimited_cstring((int)self, Destination, 80, 34, 34);
      rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Folder:");
      rf_text_parser_read_delimited_cstring((int)self, v9, 40, 34, 34);
      first_free_slot = rf_bluebeard_metadata_find_first_free_slot();
      if ( !first_free_slot )
      {
        v13 = -1;
        rf_memory_text_parser_destroy_buffer_adapter(self);
        return -1;
      }
      memset(first_free_slot, 0, 0xB4u);
      v7 = Destination;
      v6 = first_free_slot;
      do
      {
        v5 = *v7;
        *v6++ = *v7++;
      }
      while ( v5 );
      v4 = v9;
      v3 = first_free_slot + 120;
      do
      {
        v2 = *v4;
        *v3++ = *v4++;
      }
      while ( v2 );
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Time:") )
        *((_DWORD *)first_free_slot + 41) = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self);
      else
        *((_DWORD *)first_free_slot + 41) = rf_time64_forward(nullptr);
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Music Track") )
      {
        *((_DWORD *)first_free_slot + 43) |= 0x20000000u;
      }
      else
      {
        *((_DWORD *)first_free_slot + 43) &= ~0x20000000u;
        if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Ambient Sound") )
          *((_DWORD *)first_free_slot + 42) = *((_DWORD *)first_free_slot + 42) & 0x7FFFFFFF | 0x80000000;
        rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Envelope:");
        *((_DWORD *)first_free_slot + 40) = rf_text_parser_read_unsigned_decimal_or_hex_integer((char **)self);
        rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "$Keyoff Time:");
        *((_DWORD *)first_free_slot + 43) = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self) & 0xFFFFFFF
                                          | *((_DWORD *)first_free_slot + 43) & 0xF0000000;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Looping Sound") )
      {
        *((_DWORD *)first_free_slot + 42) |= 0x40000000u;
        rf_text_parser_require_case_insensitive_prefix_or_fatal(self, "+Loop Start:");
        *((_DWORD *)first_free_slot + 42) = rf_text_parser_read_signed_decimal_or_hex_integer((char **)self) & 0x7FFFFFF
                                          | *((_DWORD *)first_free_slot + 42) & 0xF8000000;
      }
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Preload") )
        v1 = *((_DWORD *)first_free_slot + 43) & 0x7FFFFFFF | 0x80000000;
      else
        v1 = *((_DWORD *)first_free_slot + 43) & 0x7FFFFFFF;
      *((_DWORD *)first_free_slot + 43) = v1;
      first_free_slot[176] = rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Incidental");
      if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Preserve Low Frequencies") )
      {
        *((_DWORD *)first_free_slot + 42) = *((_DWORD *)first_free_slot + 42) & 0xC7FFFFFF | 0x10000000;
      }
      else if ( rf_text_parser_try_consume_case_insensitive_prefix((const char **)self, "+Preserve Medium Frequencies") )
      {
        *((_DWORD *)first_free_slot + 42) = *((_DWORD *)first_free_slot + 42) & 0xC7FFFFFF | 0x8000000;
      }
      *((_DWORD *)first_free_slot + 43) |= 0x10000000u;
    }
    qsort(&unk_1F6D330, 0x1000u, 0xB4u, (_CoreCrtNonSecureSearchSortCompareFunction)rf_bluebeard_sound_basename_compare);
    unk_1F6D24B = 1;
    v13 = -1;
    rf_memory_text_parser_destroy_buffer_adapter(self);
    return 0;
  }
}

