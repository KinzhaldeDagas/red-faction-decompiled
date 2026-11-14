// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF3E0 rf_jpeg_jinit_marker_writer
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:jinit_marker_writer matched): Allocates32-byte image-pool1 markerobject,cinfo.marker344=it;callbacks0=fileheader5FF5B0,4=frameheader5FF7F0,8=scanheader5FFBF0,12=filetrailer600010,16=tablesonly600030,20=applicationmarkerheader5FF460,24=markerbyte5FF590;last_restart_interval28=0. No output/otherobjectinit;voidAPI. Callback600010 was falsely labeled __fputchar_3;it emitsJPEGEOI,not aCRTcharacter.
_DWORD *__cdecl rf_jpeg_jinit_marker_writer(int a1)
{
  _DWORD *result; // eax

  result = (_DWORD *)(**(int (__cdecl ***)(int, int, int))(a1 + 4))(a1, 1, 32);
  *(_DWORD *)(a1 + 344) = result;
  *result = rf_jpeg_marker_write_file_header;
  result[1] = rf_jpeg_marker_write_frame_header;
  result[2] = rf_jpeg_marker_write_scan_header;
  result[3] = rf_jpeg_marker_write_file_trailer;
  result[4] = rf_jpeg_marker_write_tables_only;
  result[5] = rf_jpeg_marker_write_marker_header;
  result[6] = rf_jpeg_marker_write_marker_byte;
  result[7] = 0;
  return result;
}

