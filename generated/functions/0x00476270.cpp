// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476270 rf_cutscene_named_segment_record_find
// UNREALRED VERIFIED [cutscene-ui-20261028]: Scans signed count0x6FB250 of100-byte records at0x6FB670, compares RF string at record start to caller C string case-insensitively, returns first pointer or0. Does not allocate or play the named record.
char *__cdecl rf_cutscene_named_segment_record_find(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < unk_6FB250; ++i )
  {
    if ( rf_string_equals_case_insensitive((int)&byte_6FB670[100 * i], String2) )
      return &byte_6FB670[100 * i];
  }
  return nullptr;
}

