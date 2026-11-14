// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600010 rf_jpeg_marker_write_file_trailer
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:write_file_trailer matched): Cdeclcinfo,simplyemit_marker(cinfo,217) ->JPEGEOI FF D9. Doesnotflushdestination,closeFILEorwritegenericcharacter. Prior__fputchar_3CRTFLIRTlabelandintCharacterprototypewerefalse;correctedvoidcinfoAPI. Callbackinstalledatmarker+12by5FF3E0.
void __cdecl rf_jpeg_marker_write_file_trailer(void *cinfo)
{
  rf_jpeg_marker_emit_marker(cinfo, 217);
}

