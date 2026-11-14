// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005930A0 rf_vfile_open_with_extension_cache_control_paths
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall VFile, filename, mode, root/context value. Finds last-dot suffix anywhere in path. Unless context decimal9999999, tries resolver then opens immediately; this first successful resolution unbounded-copies suffix into global cache aNone_12 BEFORE open result known. Otherwise may retry cached root664788 if not-1, valid, suffix matches cache and cached root differs from88E3F4; successful resolution opens directly. Final fallback calls resolver with9999999, ignores its result, then opens; on open success0 updates cached root to receiver+0 and suffix. Crucially current resolver5929A0 NEVER READS its context argument, so these passed root ids do not force specific-root selection. Open result0
// success/negative error forwarded. No suffix-copy length bound or source NULL guard.
int __thiscall rf_vfile_open_with_extension_cache_control_paths(int *this, char *Str, int a3, char *a4)
{
  char v4; // al
  char v6; // al
  char *v7; // [esp+8h] [ebp-28h]
  const char *v8; // [esp+Ch] [ebp-24h]
  char *v9; // [esp+18h] [ebp-18h]
  const char *v10; // [esp+1Ch] [ebp-14h]
  const char *String1; // [esp+28h] [ebp-8h]
  int v13; // [esp+2Ch] [ebp-4h]

  String1 = rf_path_find_last_dot_or_empty_literal(Str);
  if ( a4 != byte_98967F && rf_vfile_resolve_open_source((int)this, Str, (int)a4) )
  {
    v10 = String1;
    v9 = aNone_12;
    do
    {
      v4 = *v10;
      *v9++ = *v10++;
    }
    while ( v4 );
    return rf_vfile_open_stdio_or_vpp((int)this, a3);
  }
  if ( dword_664788 != -1
    && rf_vfile_is_valid_search_root_id(dword_664788)
    && !_stricmp(String1, aNone_12)
    && dword_664788 != dword_88E3F4
    && rf_vfile_resolve_open_source((int)this, Str, dword_664788) )
  {
    return rf_vfile_open_stdio_or_vpp((int)this, a3);
  }
  rf_vfile_resolve_open_source((int)this, Str, (int)byte_98967F);
  v13 = rf_vfile_open_stdio_or_vpp((int)this, a3);
  if ( !v13 )
  {
    dword_664788 = *this;
    v8 = String1;
    v7 = aNone_12;
    do
    {
      v6 = *v8;
      *v7++ = *v8++;
    }
    while ( v6 );
  }
  return v13;
}

