// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056DD50 rf_console_output_append_text_lines
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl(text,optionalRGBApointer). If initialized byte180A484==0,textNULL or strlen0 does nothing. Otherwise increments dirty counter180A494 ONCE per call,then splits at LF,excluding separator. Appends every segment including internal empty lines to ring180A5B0 indexed1809920,500 records stride261 =257 text bytes plus unaligned colorDWORD at+257 (180A6B1). Color from caller DWORD or default180A49C. Advances/wraps write index after each segment;trailing LF does not create extra final empty record. strncpy count is full segment length with NO257-byte bound,then explicit NUL,so long lines can overwrite color/neighbor records. No wrapping/format interpretation or logical line count maintained. EAX
// incidental,not a reliable length/status.
int __cdecl rf_console_output_append_text_lines(char *a1, int *a2)
{
  int result; // eax
  const char *v3; // [esp+Ch] [ebp-14h]
  char *v4; // [esp+10h] [ebp-10h]
  char *Source; // [esp+1Ch] [ebp-4h]

  result = unk_180A484;
  if ( unk_180A484 )
  {
    if ( a1 )
    {
      v3 = &a1[strlen(a1) + 1];
      result = v3 - (a1 + 1);
      if ( result >= 1 )
      {
        ++unk_180A494;
        Source = a1;
        do
        {
          v4 = strchr(Source, 10);
          if ( !v4 )
            v4 = (char *)(v3 - 1);
          strncpy(&unk_180A5B0[261 * dword_1809920], Source, v4 - Source);
          unk_180A5B0[261 * dword_1809920 + v4 - Source] = 0;
          if ( a2 )
            *(int *)((char *)unk_180A6B1 + 261 * dword_1809920) = *a2;
          else
            *(int *)((char *)unk_180A6B1 + 261 * dword_1809920) = unk_180A49C;
          if ( ++dword_1809920 >= 500 )
            dword_1809920 = 0;
          Source = v4 + 1;
          result = (int)(v4 + 1);
        }
        while ( v4 + 1 < v3 - 1 );
      }
    }
  }
  return result;
}

