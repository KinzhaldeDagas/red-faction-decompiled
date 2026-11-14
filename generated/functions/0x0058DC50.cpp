// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058DC50 rf_text_wrap_into_offset_length_arrays
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): Cdecl7 args lineLengths*,lineOffsets*,NUL text,maxPixelWidth,maxLines,ignoredWordMarker lowBYTE,fontID; caller pops28 bytes,returns emitted line count. Corrected first argument from integer to int*,second to signed int* for -1 sentinel. Skips initial spaces/tabs/LFs through helper predicate,then stores offsets[0]=-1 EVEN when maxLines<=0. Pending line skips leading space/tab only; first other byte becomes raw text offset and resets last-break index. Unskipped LF emits length=i-start,unconditionally stores offsets[++count]=-1,starts new line and clears measured-text buffer. Internal blank LF can emit empty lines; initial leading LFs are skipped. Requires offsets storage of at least
// maxLines+1 because sentinel write occurs immediately after each emitted line,BEFORE next iteration capacity check. Lengths need maxLines entries. No array/pointer/text validation. Non-LF ignored-word marker starts skip mode; marker and following bytes are excluded from measured text until first space/tab/LF. That terminating whitespace ONLY clears skip mode and is not otherwise processed,so LF terminating a skipped run does not emit a line. Raw output ranges still include ignored bytes. Normal bytes append to local512-byte buffer,then NUL; no buffer-capacity check(only511 appended bytes plus NUL fit). Measures after EACH appended byte using font helper(length-1,fontID); ignores measured height. Width>=maxPixelWidth triggers wrap,not just >. Last-break candidate is byte after hyphen or first whitespace in a whitespace run. If candidate exists,emit through candidate(excludes
// whitespace,includes hyphen),rewind input to candidate-1 for hyphen elsecandidate,then normal increment/pending-leading-skip resumes. With no candidate,emit up to BUT EXCLUDING current byte and decrement i so current byte is reprocessed on new line. A first glyph meeting/exceeding width can therefore emit empty lines without consuming input until maxLines reached. Whitespace-run flag is not reset at each line break. Final nonempty pending line emits length to end; no extra terminal sentinel after that final append. Recomputes strlen each loop iteration. No input mutation,Unicode tokenization,word-length limit or allocation.
int __cdecl rf_text_wrap_into_offset_length_arrays(
        int *line_lengths,
        int *line_offsets,
        const char *text,
        int max_pixel_width,
        int max_lines,
        char ignored_word_marker,
        int font_id)
{
  int v8; // [esp+10h] [ebp-22Ch]
  int v9; // [esp+14h] [ebp-228h]
  int v10; // [esp+18h] [ebp-224h]
  unsigned __int8 v11[512]; // [esp+1Ch] [ebp-220h] BYREF
  int v12; // [esp+220h] [ebp-1Ch] BYREF
  int v13; // [esp+224h] [ebp-18h] BYREF
  int i; // [esp+228h] [ebp-14h]
  int v15; // [esp+22Ch] [ebp-10h]
  int v16; // [esp+230h] [ebp-Ch]
  int v17; // [esp+234h] [ebp-8h]
  int v18; // [esp+238h] [ebp-4h]

  v9 = -1;
  v17 = 0;
  v18 = 0;
  memset(v11, 0, sizeof(v11));
  v15 = 0;
  v16 = 0;
  for ( i = 0; rf_text_byte_is_space_tab_lf(text[i]); ++i )
    ;
  v10 = 1;
  *line_offsets = -1;
  while ( i < (int)strlen(text) )
  {
    if ( v17 >= max_lines )
      return v17;
    if ( v10 )
    {
      line_offsets[v17] = -1;
      if ( rf_text_byte_is_space_or_tab(text[i]) )
        goto LABEL_5;
      line_offsets[v17] = i;
      v9 = -1;
      v10 = 0;
    }
    if ( v16 )
    {
      if ( rf_text_byte_is_space_tab_lf(text[i]) )
        v16 = 0;
    }
    else if ( text[i] == 10 )
    {
      line_lengths[v17] = i - line_offsets[v17];
      line_offsets[++v17] = -1;
      v10 = 1;
      memset(v11, 0, sizeof(v11));
      v15 = 0;
    }
    else if ( text[i] == ignored_word_marker )
    {
      v16 = 1;
    }
    else
    {
      if ( i > 0 && text[i - 1] == 45 )
        v9 = i;
      if ( rf_text_byte_is_space_or_tab(text[i]) )
      {
        if ( !v18 )
          v9 = i;
        v18 = 1;
      }
      else
      {
        v18 = 0;
      }
      v11[v15++] = text[i];
      v11[v15] = 0;
      rf_font_measure_text_extent(&v12, &v13, v11, -1, font_id);
      if ( v12 >= max_pixel_width )
      {
        if ( v9 < 0 )
        {
          v8 = i--;
        }
        else
        {
          v8 = v9;
          if ( v9 > 0 && text[v9 - 1] == 45 )
            i = v9 - 1;
          else
            i = v9;
        }
        line_lengths[v17] = v8 - line_offsets[v17];
        line_offsets[++v17] = -1;
        v10 = 1;
        memset(v11, 0, sizeof(v11));
        v15 = 0;
      }
    }
LABEL_5:
    ++i;
  }
  if ( line_offsets[v17] >= 0 )
  {
    line_lengths[v17] = i - line_offsets[v17];
    ++v17;
  }
  return v17;
}

