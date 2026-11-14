// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578EA0 rf_memory_text_parser_open_file_to_owned_buffer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): ECX receiver plus(path,opaqueVFileContext,unusedInt),RET12;returns0 or negative VFile-open code. Constructs local VFile,unbounded-copies path to object+8 (can overwrite fields264/268 and beyond),sets local mode0 THEN1 and clears buffer0 WITHOUT closing any previous allocation. Hardcoded local1 makes mapped-cache lookup branch unreachable even when global189745C nonzero;third stack arg unused. Normal path opens VFile read mode1 with caller context;negative open result destroys local and returns,leaving prior cursor/fields stale and prior buffer pointer lost. Success stores file size DWORD268,allocates size+1 with malloc,immediately writes buffer[size]=NUL,reads exactly size bytes,closes VFile,then5791D0 sets
// cursor=buffer/field264=1. Ignores size/malloc/read-status/overflow checks;zero/partial reads not distinguished. Does not restrict source to loose files (VFile resolver still applies). Close579190 skips freeing any buffer when mapped-cache global nonzero,so forced owned path can leak under that condition. EAX0 does not verify complete read.
int __thiscall rf_memory_text_parser_open_file_to_owned_buffer(void *self, const char *path, void *context, int unused)
{
  char v5; // [esp+7h] [ebp-151h]
  char *v6; // [esp+Ch] [ebp-14Ch]
  const char *v7; // [esp+10h] [ebp-148h]
  int v9; // [esp+1Ch] [ebp-13Ch]
  int v10; // [esp+20h] [ebp-138h] BYREF
  int v11; // [esp+24h] [ebp-134h]
  char v12; // [esp+2Bh] [ebp-12Dh]
  int selfa[71]; // [esp+2Ch] [ebp-12Ch] BYREF
  int v14; // [esp+154h] [ebp-4h]

  rf_vfile_construct_unopened(selfa);
  v14 = 0;
  v7 = path;
  v6 = (char *)self + 8;
  do
  {
    v5 = *v7;
    *v6++ = *v7++;
  }
  while ( v5 );
  v12 = 1;
  *(_DWORD *)self = 0;
  if ( unk_189745C && !v12 )
  {
    if ( rf_vpackfile_find_member_size_and_byte_offset(&unk_1897460, (char *)self + 8, (_DWORD *)self + 67, &v10) )
      *(_DWORD *)self = v10 + unk_189745C;
  }
  if ( !*(_DWORD *)self )
  {
    v11 = rf_vfile_open_with_extension_cache_control_paths(selfa, (char *)path, 1, context);
    if ( v11 < 0 )
    {
      v9 = v11;
      v14 = -1;
      rf_vfile_destruct_close_if_open(selfa);
      return v9;
    }
    *((_DWORD *)self + 67) = rf_vfile_get_size((int)selfa, nullptr, (int)byte_98967F);
    *(_DWORD *)self = malloc(*((_DWORD *)self + 67) + 1);
    *(_BYTE *)(*(_DWORD *)self + *((_DWORD *)self + 67)) = 0;
    rf_vfile_read_buffered_bytes_versioned(selfa, *(char **)self, *((_DWORD *)self + 67), 0, 0);
    rf_vfile_close_stdio_or_vpp(selfa);
  }
  rf_memory_text_parser_reset_cursor_if_loaded(self);
  v14 = -1;
  rf_vfile_destruct_close_if_open(selfa);
  return 0;
}

