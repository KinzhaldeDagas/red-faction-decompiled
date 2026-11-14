// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058D7C0 rf_font_extract_wrapped_prefix_if_too_wide
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Arguments output RF string object, in/out RF string object, maximum pixel width, font ID. If full text fits, constructs EMPTY output and leaves input unchanged. Otherwise measures prefix lengths until width exceeds limit, tracking first byte of the latest whitespace run. LF encountered before overflow extracts bytes before LF and consumes it from input. Normal wrap extracts prefix before saved separator, skips that separator then following space/tab and at most one LF, assigns remaining input and copy-constructs output. NO-WHITESPACE fallback uses current prefix length i (already too wide), then unconditionally increments split index, so it can return an over-wide prefix and drop the following nonseparator byte. Return EAX always output pointer. Source string layout
// is two DWORDs (stored extent, buffer pointer), not std::exception; corrected that false prototype. No negative-width or object-alias guard.
void *__cdecl rf_font_extract_wrapped_prefix_if_too_wide(void *a1, void *a2, int a3, int a4)
{
  unsigned __int8 *v4; // eax
  unsigned __int8 *v6; // eax
  char *v7; // eax
  char *v8; // eax
  int v9; // [esp-8h] [ebp-7Ch]
  _DWORD *v10; // [esp+4h] [ebp-70h]
  _DWORD *v11; // [esp+Ch] [ebp-68h]
  _DWORD *v12; // [esp+14h] [ebp-60h]
  _DWORD *v13; // [esp+1Ch] [ebp-58h]
  _DWORD v14[2]; // [esp+28h] [ebp-4Ch] BYREF
  _DWORD v15[2]; // [esp+30h] [ebp-44h] BYREF
  _DWORD v16[2]; // [esp+38h] [ebp-3Ch] BYREF
  _DWORD v17[2]; // [esp+40h] [ebp-34h] BYREF
  char *v18[2]; // [esp+48h] [ebp-2Ch] BYREF
  signed int v19; // [esp+50h] [ebp-24h]
  int i; // [esp+54h] [ebp-20h]
  char v21; // [esp+5Bh] [ebp-19h]
  int v22; // [esp+5Ch] [ebp-18h] BYREF
  int v23; // [esp+60h] [ebp-14h] BYREF
  int v24; // [esp+64h] [ebp-10h]
  int v25; // [esp+70h] [ebp-4h]

  v21 = 0;
  v24 = -1;
  rf_string_construct_empty(v18);
  v25 = 1;
  v4 = (unsigned __int8 *)rf_string_object_c_str_or_empty(a2);
  rf_font_measure_text_extent(&v23, &v22, v4, -1, a4);
  if ( v23 > a3 )
  {
    v19 = rf_string_length_from_cstr((const char **)a2);
    for ( i = 0; i < v19; ++i )
    {
      v9 = i;
      v6 = (unsigned __int8 *)rf_string_object_c_str_or_empty(a2);
      rf_font_measure_text_extent(&v23, &v22, v6, v9, a4);
      if ( v23 > a3 )
        break;
      if ( *rf_string_byte_pointer_or_zero_sentinel((int *)a2, i) == 10 )
      {
        v13 = rf_string_left_count((char **)a2, v17, i);
        LOBYTE(v25) = 2;
        rf_string_assign_from_object(v18, (int)v13);
        LOBYTE(v25) = 1;
        rf_string_destroy_buffer(v17);
        v12 = rf_string_substring_inclusive(a2, v16, i + 1, -1);
        LOBYTE(v25) = 3;
        rf_string_assign_from_object(a2, (int)v12);
        LOBYTE(v25) = 1;
        rf_string_destroy_buffer(v16);
        rf_string_copy_construct_from_object(a1, v18);
        LOBYTE(v25) = 0;
        rf_string_destroy_buffer(v18);
        return a1;
      }
      v7 = rf_string_byte_pointer_or_zero_sentinel((int *)a2, i);
      if ( rf_text_byte_is_space_tab_lf(*v7) )
      {
        if ( !v21 )
          v24 = i;
        v21 = 1;
      }
      else
      {
        v21 = 0;
      }
    }
    if ( v24 < 0 )
      v24 = i;
    v11 = rf_string_left_count((char **)a2, v15, v24);
    LOBYTE(v25) = 4;
    rf_string_assign_from_object(v18, (int)v11);
    LOBYTE(v25) = 1;
    rf_string_destroy_buffer(v15);
    ++v24;
    while ( v24 < v19 )
    {
      v8 = rf_string_byte_pointer_or_zero_sentinel((int *)a2, v24);
      if ( !rf_text_byte_is_space_or_tab(*v8) )
        break;
      ++v24;
    }
    if ( v24 < v19 && *rf_string_byte_pointer_or_zero_sentinel((int *)a2, v24) == 10 )
      ++v24;
    if ( v24 == v19 )
    {
      rf_string_assign_from_cstr(a2, (char *)&byte_641B97);
    }
    else
    {
      v10 = rf_string_substring_inclusive(a2, v14, v24, -1);
      LOBYTE(v25) = 5;
      rf_string_assign_from_object(a2, (int)v10);
      LOBYTE(v25) = 1;
      rf_string_destroy_buffer(v14);
    }
    rf_string_copy_construct_from_object(a1, v18);
    LOBYTE(v25) = 0;
    rf_string_destroy_buffer(v18);
    return a1;
  }
  else
  {
    rf_string_construct_from_cstr(a1, (char *)&byte_641B96);
    LOBYTE(v25) = 0;
    rf_string_destroy_buffer(v18);
    return a1;
  }
}

