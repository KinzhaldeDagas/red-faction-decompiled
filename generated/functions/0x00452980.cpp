// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00452980 rf_credits_append_localized_table_wrapped_lines
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): No arguments. Construct272-byte stack memory parser578780; open 'credits.tbl'
// via578EA0(this,path,raw0x0098967F decimal9999999,unused0). SIGNED open result<0 calls fatal5708E0(credits.cpp,line185,'Could not open credits.tbl!'); hypothetical return repeats
// fatal call, no recoverable status. Only successful open queries4EFC60 language: EXACT0 searches/consumes '#English',1 '#German',2 '#French' via578D00(target,NULL); other language
// values perform NO section search. Caller ignores section-locator AL0, so a missing section is not itself a caller fatal branch. Search/consumer trivia, case and failure cursor
// effects remain native.  Repeatedly579460(parser,stackLine,256); ANYnonzero AL admits line, AL0 ends normally (EOF and oversized-line failure not distinguished). Exact
// CASE-SENSITIVE full-string '#End' ends; no marker requirement at EOF. For other lines, capture current fontDWORD663048 BEFORE querying current viewport width571C00.
// Call58DC50(lengths*,offsets*,line,signed32_wrap(width-64),32,ignoredMarkerBYTE0,capturedFont). Its native raw ranges/sentinel/leading-whitespace rules remain unchanged; no
// independent width validation. Let n=returned signed count. If n==0, increment retained global budgetDWORD6EFEB8 by1; ANYnonzero n instead adds strlen(ORIGINAL full line)+n,
// all32-bit wrap. This counter is not recomputed actual output length. SIGNED updated counter>5696(0x1640) breaks AFTER counter/line cursor changes but BEFORE appending this line;
// equality5696 is admitted.  If n==0, find NUL of retained global text6EFEC0 and overwrite it with PE WORD0x000A (LF thenNUL). Otherwise signed i0..<n appends
// strncat(text,line+offset[i],length[i]) then sameLF/NUL word after EVERY emitted range. No own count/offset/source/buffer-capacity validation; native lengths32/offset scratch and
// helper sentinel effects are retained. This function NEVER clears text6EFEC0 or counter6EFEB8, so repeated calls append and accumulate old budget, including an already-overbudget
// value. Full original line length, not sum of copied ranges, drives admission. On normal termination explicitly579190 closes parser buffer, then578830 destructor adapter closes it
// AGAIN and returns stack parser receiver POINTER inEAX; normal605EE4 cookie check preserves EAX. Return is dangling stack receiver residue, not bool/byte count. Compiler SEH cleanup
// also calls destructor, no application-state rollback. No panel request, text measurement, bitmap/music operation or pause/runtime gate.
void **rf_credits_append_localized_table_wrapped_lines()
{
  int viewport_width; // eax
  int v2; // [esp-4h] [ebp-37Ch]
  size_t Count[33]; // [esp+44h] [ebp-334h] BYREF
  int v4; // [esp+C8h] [ebp-2B0h]
  int line_offsets[32]; // [esp+CCh] [ebp-2ACh] BYREF
  int i; // [esp+14Ch] [ebp-22Ch]
  int language; // [esp+150h] [ebp-228h]
  void *self[68]; // [esp+154h] [ebp-224h] BYREF
  char Destination; // [esp+264h] [ebp-114h] BYREF
  _BYTE v10[3]; // [esp+265h] [ebp-113h] BYREF
  int v11; // [esp+374h] [ebp-4h]

  rf_memory_text_parser_construct_empty(self);
  v11 = 0;
  if ( rf_memory_text_parser_open_file_to_owned_buffer(self, "credits.tbl", byte_98967F, 0) < 0 )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\gamesrc\\interface\\credits.cpp",
      185,
      "Could not open credits.tbl!");
  language = rf_localization_get_language();
  if ( language )
  {
    if ( language == 1 )
    {
      rf_text_parser_find_before_stop_and_consume_required((char **)self, "#German", nullptr);
    }
    else if ( language == 2 )
    {
      rf_text_parser_find_before_stop_and_consume_required((char **)self, "#French", nullptr);
    }
  }
  else
  {
    rf_text_parser_find_before_stop_and_consume_required((char **)self, "#English", nullptr);
  }
  while ( rf_text_parser_read_cr_line_cstring_if_fits((int)self, &Destination, 256) && strcmp(&Destination, "#End") )
  {
    v2 = dword_663048;
    viewport_width = rf_renderer_get_viewport_width();
    v4 = rf_text_wrap_into_offset_length_arrays(
           (int *)Count,
           line_offsets,
           &Destination,
           viewport_width - 64,
           32,
           0,
           v2);
    if ( v4 )
      dword_6EFEB8 += v4 + &v10[strlen(&Destination)] - v10;
    else
      ++dword_6EFEB8;
    if ( dword_6EFEB8 > 5696 )
      break;
    if ( v4 )
    {
      for ( i = 0; i < v4; ++i )
      {
        strncat(MEMORY[0x6EFEC0], &v10[line_offsets[i] - 1], Count[i]);
        *(_WORD *)&MEMORY[0x6EFEC0][strlen(MEMORY[0x6EFEC0])] = 10;
      }
    }
    else
    {
      *(_WORD *)&MEMORY[0x6EFEC0][strlen(MEMORY[0x6EFEC0])] = 10;
    }
  }
  rf_memory_text_parser_close_buffer(self);
  v11 = -1;
  return rf_memory_text_parser_destroy_buffer_adapter(self);
}

