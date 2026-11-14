// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E63F0 rf_fpgun_parse_type_record
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player configuration packing/file I/O, fpgun type records and parser ECX/stack ABI): Cdecl one parser pointer, corrected omitted argument: sole loader caller pushes local parser,pops4; body repeatedly reloads incoming arg into ECX for parser methods. Destination=87C798+52*current count. Require ordered case-insensitive prefixes $Name:,$Model:,$Hand Texture:,$Forearm Texture:,$Bicep Texture:, each followed by double-quote-delimited RFString read(open/close34). Store nameRFString0,modelRFString8; model path is not loaded here. For each hand/forearm/bicep texture: load original filename(-1,1), then strip last extension through path helper, append _blue.tga and load, repeat original strip then _red.tga/load. Store nine bitmap handles: default16/20/24,blue28/32/36,red40/44/48. Any returned handle including-1 is stored;
// count increments only after all fields/loads complete. Existing record strings must already be constructed; no per-record memset/capacity check (outer loader enforces256), filename append bounds check, fallback or rollback. Destroy temporary RFString normally/SEH. Shared parser receiver signatures corrected together so ECX ownership is retained in fresh pseudocode.
void __cdecl rf_fpgun_parse_type_record(void *parser)
{
  char *v1; // eax
  int v2; // eax
  char *v3; // eax
  int v4; // eax
  char *v5; // eax
  int v6; // eax
  char *v7; // eax
  int v8; // eax
  char *v9; // eax
  int v10; // eax
  char *v11; // eax
  int v12; // eax
  char *v13; // eax
  int v14; // eax
  char *v15; // eax
  int v16; // eax
  char *v17; // eax
  int v18; // eax
  char *v20; // [esp+Ch] [ebp-148h]
  char *v22; // [esp+14h] [ebp-140h]
  char *v24; // [esp+1Ch] [ebp-138h]
  char *v26; // [esp+24h] [ebp-130h]
  char *v28; // [esp+2Ch] [ebp-128h]
  char *v30; // [esp+34h] [ebp-120h]
  int v31; // [esp+38h] [ebp-11Ch] BYREF
  char v32; // [esp+3Fh] [ebp-115h] BYREF
  char v33[256]; // [esp+40h] [ebp-114h] BYREF
  void *destination; // [esp+144h] [ebp-10h]
  int v35; // [esp+150h] [ebp-4h]

  rf_string_construct_empty(&v31);
  v35 = 0;
  destination = &byte_87C798[52 * dword_87C6D8];
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Name:");
  rf_text_parser_read_delimited_rfstring(parser, destination, 34, 34);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Model:");
  rf_text_parser_read_delimited_rfstring(parser, (char *)destination + 8, 34, 34);
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Hand Texture:");
  rf_text_parser_read_delimited_rfstring(parser, &v31, 34, 34);
  v1 = (char *)rf_string_object_c_str_or_empty(&v31);
  v2 = rf_bitmap_load_with_optional_mipmap_generation(v1, (void *)0xFFFFFFFF, 1);
  *((_DWORD *)destination + 4) = v2;
  v3 = (char *)rf_string_object_c_str_or_empty(&v31);
  rf_path_copy_without_last_extension(v33, v3);
  v30 = &v32;
  while ( *++v30 )
    ;
  strcpy(v30, "_blue.tga");
  v4 = rf_bitmap_load_with_optional_mipmap_generation(v33, (void *)0xFFFFFFFF, 1);
  *((_DWORD *)destination + 7) = v4;
  v5 = (char *)rf_string_object_c_str_or_empty(&v31);
  rf_path_copy_without_last_extension(v33, v5);
  v28 = &v32;
  while ( *++v28 )
    ;
  strcpy(v28, "_red.tga");
  v6 = rf_bitmap_load_with_optional_mipmap_generation(v33, (void *)0xFFFFFFFF, 1);
  *((_DWORD *)destination + 10) = v6;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Forearm Texture:");
  rf_text_parser_read_delimited_rfstring(parser, &v31, 34, 34);
  v7 = (char *)rf_string_object_c_str_or_empty(&v31);
  v8 = rf_bitmap_load_with_optional_mipmap_generation(v7, (void *)0xFFFFFFFF, 1);
  *((_DWORD *)destination + 5) = v8;
  v9 = (char *)rf_string_object_c_str_or_empty(&v31);
  rf_path_copy_without_last_extension(v33, v9);
  v26 = &v32;
  while ( *++v26 )
    ;
  strcpy(v26, "_blue.tga");
  v10 = rf_bitmap_load_with_optional_mipmap_generation(v33, (void *)0xFFFFFFFF, 1);
  *((_DWORD *)destination + 8) = v10;
  v11 = (char *)rf_string_object_c_str_or_empty(&v31);
  rf_path_copy_without_last_extension(v33, v11);
  v24 = &v32;
  while ( *++v24 )
    ;
  strcpy(v24, "_red.tga");
  v12 = rf_bitmap_load_with_optional_mipmap_generation(v33, (void *)0xFFFFFFFF, 1);
  *((_DWORD *)destination + 11) = v12;
  rf_text_parser_require_case_insensitive_prefix_or_fatal(parser, "$Bicep Texture:");
  rf_text_parser_read_delimited_rfstring(parser, &v31, 34, 34);
  v13 = (char *)rf_string_object_c_str_or_empty(&v31);
  v14 = rf_bitmap_load_with_optional_mipmap_generation(v13, (void *)0xFFFFFFFF, 1);
  *((_DWORD *)destination + 6) = v14;
  v15 = (char *)rf_string_object_c_str_or_empty(&v31);
  rf_path_copy_without_last_extension(v33, v15);
  v22 = &v32;
  while ( *++v22 )
    ;
  strcpy(v22, "_blue.tga");
  v16 = rf_bitmap_load_with_optional_mipmap_generation(v33, (void *)0xFFFFFFFF, 1);
  *((_DWORD *)destination + 9) = v16;
  v17 = (char *)rf_string_object_c_str_or_empty(&v31);
  rf_path_copy_without_last_extension(v33, v17);
  v20 = &v32;
  while ( *++v20 )
    ;
  strcpy(v20, "_red.tga");
  v18 = rf_bitmap_load_with_optional_mipmap_generation(v33, (void *)0xFFFFFFFF, 1);
  *((_DWORD *)destination + 12) = v18;
  ++dword_87C6D8;
  v35 = -1;
  rf_string_destroy_buffer(&v31);
}

