// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F990 rf_string_left_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Thiscall(source object, output object, count). Builds empty temporary. If count>=source stored extent, copies complete source C string; if0<count<extent, takes inclusive substring[0,count-1]; count<=0 yields empty. Copy-constructs output and destroys temporary, returns output pointer. Does not mutate source except possible output aliasing; stored extent can differ from strlen after reserve operations.
_DWORD *__thiscall rf_string_left_count(char **this, _DWORD *a2, int a3)
{
  _DWORD *v4; // [esp+4h] [ebp-2Ch]
  _DWORD v6[2]; // [esp+14h] [ebp-1Ch] BYREF
  char *v7[2]; // [esp+1Ch] [ebp-14h] BYREF
  int v8; // [esp+2Ch] [ebp-4h]

  rf_string_construct_empty(v7);
  v8 = 1;
  if ( a3 < (int)*this )
  {
    if ( a3 > 0 )
    {
      v4 = rf_string_substring_inclusive(this, v6, 0, a3 - 1);
      LOBYTE(v8) = 2;
      rf_string_assign_from_object(v7, (int)v4);
      LOBYTE(v8) = 1;
      rf_string_destroy_buffer(v6);
    }
  }
  else
  {
    rf_string_assign_cstr_bounded((int)v7, *(this + 1), -1);
  }
  rf_string_copy_construct_from_object(a2, v7);
  LOBYTE(v8) = 0;
  rf_string_destroy_buffer(v7);
  return a2;
}

