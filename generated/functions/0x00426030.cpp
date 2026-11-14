// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00426030 rf_entity_definitions_clear_strings_and_action_arrays
// [UnrealRed physical spheres 2026-11-12; verified ASM] Iterates SIGNED live definition count681E14 over EntityInfo global683548 stride1514 (known capacity75; the loop is not fixed75), including source48count atB68 and standing/crouch40counts atCEC/E30. Current database has no direct callers; do not infer this runs every level/asset unload. Resource release561C30/588100/589B30/589D00 does not establish modelclass cache reset.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): No arguments, void. Iterates SIGNED i=0..<live global681E14, re-reading count each bound test, over683548+i*5396(0x1514);75 is known array
// capacity, NOT a hard-coded loop count in this body. For each definition assigns empty Cstrings to RFStrings+0,+8,+16,+24,+56,+1860,+48,+260; clears ONLY counts of backing-retaining
// arrays+444,+456,+468,+480,+496,+1804,+1692,+1656,+1728. If action52 pointer+1884 nonNULL, for23 fixed records pre-clears RFStrings+0,+8,+24,+36 of each52-byte record,
// then43C730(pointer,flags3) destroys/frees vector allocation and nulls+1884. Repeats this23-record pre-clear/delete for each64 pointer slots starting+2408. For pointer+1888 and
// each64 pointer slots+2664, pre-clears only+0/+8 in45 fixed records then same flags3 delete/null. Vector destructor uses its own allocation-header element count, distinct from
// pre-clear23/45 constants. Clears source48/standing40/crouch40 array counts at+2920,+3308,+3632, retaining their storage/content. For signed re-read count+3964 traverses108-byte
// entries at+3968, clears entry RFString0 and signed count atentry+8 RFStrings entry+12+8*j; does not zero those counts. Clears RFString+5068. After definition loop ALWAYS clears23
// global RFStrings683490+8*i and45 at683328+8*i, even if live definition count<=0. Every supplied source byte literal is verified empty. No definition-count reset, model/class-cache
// reset, full memset, capacity validation or rollback; partial changes survive delegate failure. No direct CALL xref in current database;423520 registers this address as data for
// atexit.
void __cdecl rf_entity_definitions_clear_strings_and_action_arrays()
{
  char *v0; // [esp+30h] [ebp-14h]
  int j; // [esp+34h] [ebp-10h]
  int m; // [esp+34h] [ebp-10h]
  int jj; // [esp+34h] [ebp-10h]
  int kk; // [esp+34h] [ebp-10h]
  int nn; // [esp+34h] [ebp-10h]
  int ii; // [esp+38h] [ebp-Ch]
  int k; // [esp+3Ch] [ebp-8h]
  int n; // [esp+3Ch] [ebp-8h]
  int mm; // [esp+3Ch] [ebp-8h]
  int i1; // [esp+3Ch] [ebp-8h]
  int i; // [esp+40h] [ebp-4h]
  int i2; // [esp+40h] [ebp-4h]
  int i3; // [esp+40h] [ebp-4h]

  for ( i = 0; i < dword_681E14; ++i )
  {
    v0 = &rf_entity_info_definitions[5396 * i];
    rf_string_assign_from_cstr(v0, (char *)&byte_6319AA);
    rf_string_assign_from_cstr((_DWORD *)v0 + 2, (char *)&byte_6319AB);
    rf_string_assign_from_cstr((_DWORD *)v0 + 4, (char *)&byte_6319B5);
    rf_string_assign_from_cstr((_DWORD *)v0 + 6, (char *)&byte_6319B6);
    rf_string_assign_from_cstr((_DWORD *)v0 + 14, (char *)&byte_6319B7);
    rf_string_assign_from_cstr((_DWORD *)v0 + 465, (char *)&byte_6319C1);
    rf_string_assign_from_cstr((_DWORD *)v0 + 12, (char *)&byte_6319C2);
    rf_string_assign_from_cstr((_DWORD *)v0 + 65, (char *)&byte_6319C3);
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v0 + 111);
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v0 + 114);
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v0 + 117);
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v0 + 120);
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v0 + 124);
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v0 + 451);
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v0 + 423);
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v0 + 414);
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v0 + 432);
    if ( *((_DWORD *)v0 + 471) )
    {
      for ( j = 0; j < 23; ++j )
      {
        rf_string_assign_from_cstr((_DWORD *)(*((_DWORD *)v0 + 471) + 52 * j), (char *)&byte_6319CF);
        rf_string_assign_from_cstr((_DWORD *)(*((_DWORD *)v0 + 471) + 52 * j + 8), (char *)&byte_6319E1);
        for ( k = 0; k < 2; ++k )
          rf_string_assign_from_cstr((_DWORD *)(52 * j + *((_DWORD *)v0 + 471) + 12 * k + 24), (char *)&byte_6319E2);
      }
      if ( *((_DWORD *)v0 + 471) )
        rf_record52_scalar_or_vector_deleting_destructor(*((char **)v0 + 471), 3);
      *((_DWORD *)v0 + 471) = 0;
    }
    for ( m = 0; m < 64; ++m )
    {
      if ( *(_DWORD *)&v0[4 * m + 2408] )
      {
        for ( n = 0; n < 23; ++n )
        {
          rf_string_assign_from_cstr((_DWORD *)(*(_DWORD *)&v0[4 * m + 2408] + 52 * n), (char *)&byte_6319E3);
          rf_string_assign_from_cstr((_DWORD *)(*(_DWORD *)&v0[4 * m + 2408] + 52 * n + 8), (char *)&byte_6319E9);
          for ( ii = 0; ii < 2; ++ii )
            rf_string_assign_from_cstr(
              (_DWORD *)(52 * n + *(_DWORD *)&v0[4 * m + 2408] + 12 * ii + 24),
              (char *)&byte_6319EA);
        }
        if ( *(_DWORD *)&v0[4 * m + 2408] )
          rf_record52_scalar_or_vector_deleting_destructor(*(char **)&v0[4 * m + 2408], 3);
        *(_DWORD *)&v0[4 * m + 2408] = 0;
      }
    }
    if ( *((_DWORD *)v0 + 472) )
    {
      for ( jj = 0; jj < 45; ++jj )
      {
        rf_string_assign_from_cstr((_DWORD *)(*((_DWORD *)v0 + 472) + 52 * jj), (char *)&byte_6319EB);
        rf_string_assign_from_cstr((_DWORD *)(*((_DWORD *)v0 + 472) + 52 * jj + 8), (char *)&byte_631A0B);
      }
      if ( *((_DWORD *)v0 + 472) )
        rf_record52_scalar_or_vector_deleting_destructor(*((char **)v0 + 472), 3);
      *((_DWORD *)v0 + 472) = 0;
    }
    for ( kk = 0; kk < 64; ++kk )
    {
      if ( *(_DWORD *)&v0[4 * kk + 2664] )
      {
        for ( mm = 0; mm < 45; ++mm )
        {
          rf_string_assign_from_cstr((_DWORD *)(*(_DWORD *)&v0[4 * kk + 2664] + 52 * mm), (char *)&byte_631A16);
          rf_string_assign_from_cstr((_DWORD *)(*(_DWORD *)&v0[4 * kk + 2664] + 52 * mm + 8), (char *)&byte_631A17);
        }
        if ( *(_DWORD *)&v0[4 * kk + 2664] )
          rf_record52_scalar_or_vector_deleting_destructor(*(char **)&v0[4 * kk + 2664], 3);
        *(_DWORD *)&v0[4 * kk + 2664] = 0;
      }
    }
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v0 + 730);
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v0 + 827);
    rf_pointer_array_clear_count_keep_storage((_DWORD *)v0 + 908);
    for ( nn = 0; nn < *((_DWORD *)v0 + 991); ++nn )
    {
      rf_string_assign_from_cstr(&v0[108 * nn + 3968], (char *)&byte_631A26);
      for ( i1 = 0; i1 < *(_DWORD *)&v0[108 * nn + 3976]; ++i1 )
        rf_string_assign_from_cstr(&v0[108 * nn + 3980 + 8 * i1], (char *)&byte_631A27);
    }
    rf_string_assign_from_cstr((_DWORD *)v0 + 1267, (char *)&byte_631A31);
  }
  for ( i2 = 0; i2 < 23; ++i2 )
    rf_string_assign_from_cstr((_DWORD *)(8 * i2 + 6829200), (char *)&byte_631A32);
  for ( i3 = 0; i3 < 45; ++i3 )
    rf_string_assign_from_cstr((_DWORD *)(8 * i3 + 6828840), (char *)&byte_631A33);
}

