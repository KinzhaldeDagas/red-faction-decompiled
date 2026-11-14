// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D460 rf_console_command_dump_registered_list
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No arguments; command callback. If execute flag1809818 nonzero,constructs local VFile and opens literal console_commands.txt with flags80000002/default limit9999999. Open failure destroys local and returns immediately. Writes each nonnull registered command as name or name - help using unbounded sprintf/copy into260B local and direct stdio line writer;closes/destroys file. If help flag1809814 nonzero prints help claiming filename console.txt,which differs from actual output path. Does not change registry; return not semantic status.
void rf_console_command_dump_registered_list()
{
  char v0; // [esp+7h] [ebp-23Dh]
  char *v1; // [esp+Ch] [ebp-238h]
  char *v2; // [esp+10h] [ebp-234h]
  int i; // [esp+14h] [ebp-230h]
  int self[70]; // [esp+18h] [ebp-22Ch] BYREF
  char Buffer[260]; // [esp+130h] [ebp-114h] BYREF
  int v6; // [esp+240h] [ebp-4h]

  if ( dword_1809818 )
  {
    rf_vfile_construct_unopened(self);
    v6 = 0;
    if ( rf_vfile_open_with_extension_cache_control_paths(self, "console_commands.txt", -2147483646, byte_98967F) )
    {
      v6 = -1;
      rf_vfile_destruct_close_if_open(self);
      return;
    }
    for ( i = 0; i < unk_180A480; ++i )
    {
      if ( dword_180A408[i] )
      {
        if ( *(_DWORD *)(dword_180A408[i] + 4) )
        {
          sprintf(Buffer, "%s - %s", *(const char **)dword_180A408[i], *(const char **)(dword_180A408[i] + 4));
        }
        else
        {
          v2 = *(char **)dword_180A408[i];
          v1 = Buffer;
          do
          {
            v0 = *v2;
            *v1++ = *v2++;
          }
          while ( v0 );
        }
        rf_vfile_write_line_stdio_direct(self, Buffer, -1);
      }
    }
    rf_vfile_close_stdio_or_vpp(self);
    v6 = -1;
    rf_vfile_destruct_close_if_open(self);
  }
  if ( dword_1809814 )
    rf_console_output_append_text_lines("Print out console commands to the text file console.txt", nullptr);
}

