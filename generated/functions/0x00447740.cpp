// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00447740 rf_console_command_toggle_screenshot_format
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Only when console DWORD1809818!=0, reads screenshot-format BYTE6EDD40: EXACT1 becomes0 and formats literal 'JPG';
// every other value becomes1 and formats 'TGA'. Flag store precedes localization, sprintf and output. Both branches use localized format pointer88E230 (constant-zero branches make
// embedded English formats unreachable), unbounded sprintf into a60-byte buffer, then console text output with NULL color. No argument parsing or help gate; disabled invocation
// leaves format unchanged. Returns incidental EAX rather than a normalized state/status. Original PE bytes prove633E20 is the literal JPG NUL string despite the IDA off_ label.
int rf_console_command_toggle_screenshot_format()
{
  int result; // eax
  char Buffer[60]; // [esp+8h] [ebp-40h] BYREF

  if ( dword_1809818 )
  {
    if ( unk_6EDD40 == 1 )
    {
      unk_6EDD40 = 0;
      sprintf(Buffer, unk_88E230, &off_633E20);
    }
    else
    {
      unk_6EDD40 = 1;
      sprintf(Buffer, unk_88E230, "TGA");
    }
    return rf_console_output_append_text_lines(Buffer, nullptr);
  }
  return result;
}

