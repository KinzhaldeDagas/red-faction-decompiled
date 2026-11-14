// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DEA50 rf_multiplayer_character_append_default_team_skin_profiles
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): Cdecl multiplayer-character record,entity. Class definition=global table+5396*character DWORD4, profile count3964,108-byte profiles at3968 (name RFString0,count8,twelve filename RFStrings12). Before checking model/mesh count, assigns default_red/default_blue names to initial count/count+1 records ONCE. Gets definition from entity model128, iterates signed mesh count6588,148-byte containers at6592, reference material rows200 bytes/name20. Cumulative material index T=0 initialized once before outer loop. Each filename: computes strlen L, unconditionally strips LAST FOUR CHARACTERS via strncpy(stem32,name,L-4), explicitly stem[L-4]=NUL, copies into separate32-byte red/blue buffers. Decompiler
// String2[L+28]=0 is the SAME stem terminator at EBP-16Ch+L-4, not an independent wrong-buffer store. Case-insensitive substring -mip OR _mip ANYWHERE in stem selects red suffix r.tga and blue b.tga; otherwise _red.tga/_blue.tga. Append scans begin buffer-1 and increment into buffer; Source[31]+adjacent byte is one32-byte blue buffer. No suffix-extension validation, L>=4/length/capacity checks. Constructs one VFile per material; resolver AL EXACT1 stores generated candidate in respective current profile filename[T], otherwise stores original material filename independently for red/blue; resolver does not open/decode/load bitmap. Increments T, destructs VFile including SEH cleanup. At END OF EACH MESH writes cumulative T into CURRENT red/blue counts, adds2 to class profile count, then next mesh uses new records and continuing T. Thus labels are assigned only for first pair; subsequent pairs
// have no label assignment here and start at cumulative slot index, not0. Even zero-material mesh commits another pair; no meshes leaves names written but count unchanged. No class/profile/twelve-slot/mesh/pointer bounds, rollback or deduplication. EAX is loop/helper residue, not number of valid profiles.
int __cdecl rf_multiplayer_character_append_default_team_skin_profiles(int a1, int a2)
{
  int result; // eax
  char *v4; // [esp+Ch] [ebp-1F8h]
  char *v6; // [esp+14h] [ebp-1F0h]
  char *v8; // [esp+1Ch] [ebp-1E8h]
  char *v10; // [esp+24h] [ebp-1E0h]
  char v11; // [esp+2Bh] [ebp-1D9h]
  char *v12; // [esp+30h] [ebp-1D4h]
  char *v13; // [esp+34h] [ebp-1D0h]
  char v14; // [esp+3Bh] [ebp-1C9h]
  char *v15; // [esp+40h] [ebp-1C4h]
  char *v16; // [esp+44h] [ebp-1C0h]
  const char *v17; // [esp+54h] [ebp-1B0h] BYREF
  char Source[31]; // [esp+58h] [ebp-1ACh] BYREF
  char v19; // [esp+77h] [ebp-18Dh] BYREF
  char String2[32]; // [esp+78h] [ebp-18Ch] BYREF
  char Destination[32]; // [esp+98h] [ebp-16Ch] BYREF
  int self[71]; // [esp+B8h] [ebp-14Ch] BYREF
  const char *v23; // [esp+1D8h] [ebp-2Ch]
  int j; // [esp+1DCh] [ebp-28h]
  int v25; // [esp+1E0h] [ebp-24h] BYREF
  int v26; // [esp+1E4h] [ebp-20h] BYREF
  int v27; // [esp+1E8h] [ebp-1Ch]
  int i; // [esp+1ECh] [ebp-18h]
  int definition_pointer; // [esp+1F0h] [ebp-14h]
  char *v30; // [esp+1F4h] [ebp-10h]
  int v31; // [esp+200h] [ebp-4h]

  v30 = &rf_entity_info_definitions[5396 * *(_DWORD *)(a1 + 4)];
  rf_string_assign_from_cstr(&v30[108 * *((_DWORD *)v30 + 991) + 3968], "default_red");
  rf_string_assign_from_cstr(&v30[108 * *((_DWORD *)v30 + 991) + 4076], "default_blue");
  definition_pointer = rf_model_handle_get_definition_pointer(*(_DWORD *)(a2 + 128));
  v27 = 0;
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= *(_DWORD *)(definition_pointer + 6588) )
      break;
    v25 = 0;
    v26 = 0;
    rf_model_container_get_reference_mesh_materials((_DWORD *)(definition_pointer + 148 * i + 6592), &v25, &v26);
    for ( j = 0; j < v25; ++j )
    {
      v17 = (const char *)(v26 + 200 * j + 20);
      v17 += strlen(v17);
      v23 = &(++v17)[-v26 - 21 + -200 * j];
      strncpy(Destination, (const char *)(v26 + 200 * j + 20), (size_t)(v23 - 4));
      String2[(_DWORD)v23 + 28] = 0;
      v16 = Destination;
      v15 = String2;
      do
      {
        v14 = *v16;
        *v15++ = *v16++;
      }
      while ( v14 );
      v13 = Destination;
      v12 = Source;
      do
      {
        v11 = *v13;
        *v12++ = *v13++;
      }
      while ( v11 );
      if ( rf_cstring_find_first_substring_case_insensitive(Destination, "-mip")
        || rf_cstring_find_first_substring_case_insensitive(Destination, "_mip") )
      {
        v6 = &v19;
        while ( *++v6 )
          ;
        strcpy(v6, "r.tga");
        v4 = (char *)&v17 + 3;
        while ( *++v4 )
          ;
        strcpy(v4, "b.tga");
      }
      else
      {
        v10 = &v19;
        while ( *++v10 )
          ;
        strcpy(v10, "_red.tga");
        v8 = (char *)&v17 + 3;
        while ( *++v8 )
          ;
        strcpy(v8, "_blue.tga");
      }
      rf_vfile_construct_unopened(self);
      v31 = 0;
      if ( rf_vfile_resolve_open_source((int)self, String2, (int)byte_98967F) == 1 )
        rf_string_assign_from_cstr(&v30[108 * *((_DWORD *)v30 + 991) + 3980 + 8 * v27], String2);
      else
        rf_string_assign_from_cstr(&v30[108 * *((_DWORD *)v30 + 991) + 3980 + 8 * v27], (char *)(v26 + 200 * j + 20));
      if ( rf_vfile_resolve_open_source((int)self, Source, (int)byte_98967F) == 1 )
        rf_string_assign_from_cstr(&v30[108 * *((_DWORD *)v30 + 991) + 4088 + 8 * v27], Source);
      else
        rf_string_assign_from_cstr(&v30[108 * *((_DWORD *)v30 + 991) + 4088 + 8 * v27], (char *)(v26 + 200 * j + 20));
      ++v27;
      v31 = -1;
      rf_vfile_destruct_close_if_open(self);
    }
    *(_DWORD *)&v30[108 * *((_DWORD *)v30 + 991) + 3976] = v27;
    *(_DWORD *)&v30[108 * *((_DWORD *)v30 + 991) + 4084] = v27;
    *((_DWORD *)v30 + 991) += 2;
  }
  return result;
}

