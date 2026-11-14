// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00494810 rf_scoreboard_string_trim_then_append_ellipsis
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Cdecl physical16-byte ABI(out RFString*,by-value RFString extent/buffer,maxWidth),returns out pointer. Copies by-value input into temporary RFString,measures text using font/length
// defaults-1. While signed measured width>maxWidth,writesNUL at decrementing index starting strlen-1 through byte-pointer-or-zero-sentinel helper,remeasures. After ANY trim appends
// literal '...' WITHOUT reserving its width or remeasuring final result; final string can exceed maxWidth. No nonnegative-width/negative-index guard or multibyte-character handling.
// Copy-constructs output,destroys temp AND by-value input on normal/unwind; output cleanup guarded if construction completes before throw. Does not consume caller's original source
// object outside by-value copy.
_DWORD *__cdecl rf_scoreboard_string_trim_then_append_ellipsis(_DWORD *a1, int a2, int a3, int a4)
{
  unsigned __int8 *v4; // eax
  unsigned __int8 *v5; // eax
  char v7; // [esp+1Bh] [ebp-21h]
  char *v8[2]; // [esp+1Ch] [ebp-20h] BYREF
  int v9; // [esp+24h] [ebp-18h]
  int v10; // [esp+28h] [ebp-14h] BYREF
  int v11; // [esp+2Ch] [ebp-10h] BYREF
  int v12; // [esp+38h] [ebp-4h]

  v12 = 1;
  v9 = strlen(rf_string_object_c_str_or_empty(&a2)) - 1;
  v7 = 0;
  rf_string_copy_construct_from_object(v8, (char **)&a2);
  LOBYTE(v12) = 2;
  v4 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v8);
  rf_font_measure_text_extent(&v11, &v10, v4, -1, -1);
  while ( v11 > a4 )
  {
    v7 = 1;
    *rf_string_byte_pointer_or_zero_sentinel((int *)v8, v9--) = 0;
    v5 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v8);
    rf_font_measure_text_extent(&v11, &v10, v5, -1, -1);
  }
  if ( v7 )
    rf_string_append_cstr_in_place(v8, (int)"...");
  rf_string_copy_construct_from_object(a1, v8);
  LOBYTE(v12) = 1;
  rf_string_destroy_buffer(v8);
  LOBYTE(v12) = 0;
  rf_string_destroy_buffer(&a2);
  return a1;
}

