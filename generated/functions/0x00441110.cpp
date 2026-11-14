// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00441110 sub_441110
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Entity-persona name lookup: empty input returns-1; otherwise scan current persona count in source order using case-insensitive RFString equality, return first matching index, else-1. Empty native string at633332 is zero byte. Persona named empty is a valid authored row distinct from the empty input sentinel.
int __cdecl sub_441110(int a1)
{
  int i; // [esp+10h] [ebp-10h]

  if ( !rf_string_equals_case_insensitive((int)&a1, (char *)byte_633332) )
  {
    for ( i = 0; i < unk_6E6728; ++i )
    {
      if ( rf_string_object_equals_case_insensitive((int)&byte_6E6730[56 * i], (int)&a1) )
      {
        rf_string_destroy_buffer(&a1);
        return i;
      }
    }
  }
  rf_string_destroy_buffer(&a1);
  return -1;
}

