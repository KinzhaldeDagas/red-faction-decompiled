// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B060 rf_text_write_wrapped_multiline_with_end_marker
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Cdecl input cstring and VFile pointer. Repeatedly emits source segments via direct stdio line writer5A0AB0. If remaining strlen<=70, writes entire remainder including embedded CR/LF. Otherwise searches backward at indices69..0 for CR or space; failing that searches forward from70 to end. A found separator is excluded from written segment and consumed; if no separator exists, writes whole long remainder. Only CR/space are wrap separators, not LF/tab, and no hard70-column bound. Each helper call adds LF; writer status is ignored and loop still advances. After source emits $end text plus LF then a blank LF; returns final helper EAX, not byte/line count. Empty source still emits marker and blank line.
void *__cdecl rf_text_write_wrapped_multiline_with_end_marker(const char *text, void *vfile)
{
  int v4; // [esp+10h] [ebp-8h]
  int i; // [esp+14h] [ebp-4h]

  while ( *text )
  {
    v4 = strlen(text);
    i = v4;
    if ( v4 > 70 )
    {
      i = 70;
      while ( i-- )
      {
        if ( text[i] == 13 || text[i] == 32 )
        {
          v4 = i++;
          break;
        }
      }
      if ( i < 0 )
      {
        for ( i = 70; i < v4; ++i )
        {
          if ( text[i] == 13 || text[i] == 32 )
          {
            v4 = i++;
            break;
          }
        }
      }
    }
    rf_vfile_write_line_stdio_direct(vfile, text, v4);
    text += i;
  }
  rf_vfile_write_line_stdio_direct(vfile, "$end text", -1);
  return (void *)rf_vfile_write_line_stdio_direct(vfile, nullptr, -1);
}

