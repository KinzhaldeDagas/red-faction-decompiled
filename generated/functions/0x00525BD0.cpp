// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525BD0 rf_inline_pointer_array_remove_first
// UNREALRED VERIFIED [decal-updates-20261028]: Inline container layout: count at+0, pointer elements at+4+4*i. Finds first exact pointer/value match, erases index through0x525E40; no match leaves unchanged. After erase executes empty loop across new count, so EAX is final count when nonempty, container pointer otherwise; not reliable boolean/pointer contract. No pointee destruction.
int *__thiscall rf_inline_pointer_array_remove_first(int *this, int a2)
{
  int *result; // eax
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]

  for ( i = 0; i < *this && *(this + i + 1) != a2; ++i )
    ;
  result = this;
  if ( i != *this )
  {
    result = rf_inline_pointer_array_erase_unchecked(this, i);
    for ( j = 0; j < *this; ++j )
      result = (int *)(j + 1);
  }
  return result;
}

