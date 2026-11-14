// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048D910 rf_banlist_load_text_file
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ban-list validation and wildcard matching, native text-reader capacity and list ownership, multiplayer process initialization and character-cache ABI): 
// Cdecl no arguments. Resets sentinel704C5C next/prev globals704C74/704C78 toself WITHOUT freeing previously linked nodes. Constructs local VFile,opens banlist.txt with mode1 and
// path context98967F. Nonzero open result treated as failure: destroys VFile and returns. Success loops until signed EOF helper true. Calls read_line_skip_crlf_run(destination
// local260,nominal capacity255,minVersion0); verified delegate IGNORES supplied length and stores unbounded line before returning length,so following filter is not buffer protection.
// Only signed returned length<=23 enters pattern validator48D6C0,then valid text appended through duplicate-suppressing48D4A0. Longer lines skipped after being consumed. No comment
// syntax/trimming/logging or all-row transaction here. Explicit close after loop,then destructor; unwind destroys VFile. No stable load-success/count return; normal EAX delegate
// artifact.
int __cdecl rf_banlist_load_text_file()
{
  int self[70]; // [esp+8h] [ebp-22Ch] BYREF
  char String1[260]; // [esp+120h] [ebp-114h] BYREF
  int v3; // [esp+230h] [ebp-4h]

  unk_704C74 = &unk_704C5C;
  unk_704C78 = &unk_704C5C;
  rf_vfile_construct_unopened(self);
  v3 = 0;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, "banlist.txt", 1, byte_98967F) )
  {
    v3 = -1;
    return rf_vfile_destruct_close_if_open(self);
  }
  else
  {
    while ( !rf_vfile_is_position_at_or_past_end_signed(self) )
    {
      if ( rf_binary_stream_read_line_skip_crlf_run(self, String1, 255, 0) <= 23 )
      {
        if ( rf_ban_pattern_text_is_valid(String1) )
          rf_banlist_append_unique_text(String1);
      }
    }
    rf_vfile_close_stdio_or_vpp(self);
    v3 = -1;
    return rf_vfile_destruct_close_if_open(self);
  }
}

