// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058E7D0 rf_movie_cache_bink_format_once
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): No args: copies current D3D format1DAE900 to cache193BBAC,calls58E7F0 to set bitmap kind and capture screen resolution,stores returned Bink copy format193BBC4,sets initialized BYTE193BBD8=1,returns format. No own once-check: caller58E020 checks flag. No resource creation/free or automatic invalidation on later display-mode change.
int rf_movie_cache_bink_format_once()
{
  int result; // eax

  unk_193BBAC = unk_1DAE900;
  result = rf_movie_select_bink_copy_format();
  unk_193BBC4 = result;
  unk_193BBD8 = 1;
  return result;
}

