// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C3CB0 rf_d3d8_write_device_diagnostic_file
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): Builds loose-file path rfd3d.id and opens in text write mode, replacing prior contents. Writes adapter description/vendor/device/subsystem/revision, driver filename and four version words, optional driver path/stat modification time, selected texture/screen formats, and diagnostic option flags/scalars. Driver search uses SearchPathA and _stat64i32; failure emits a diagnostic line. Closes at end. Inferred FILE* return is not a live stream: success returns fclose EAX, open failure returns NULL. No fprintf error checks; only initialization caller found.
FILE *rf_d3d8_write_device_diagnostic_file()
{
  FILE *result; // eax
  struct _stat64i32 Stat; // [esp+28h] [ebp-240h] BYREF
  LPSTR FilePart; // [esp+5Ch] [ebp-20Ch] BYREF
  char FileName[256]; // [esp+60h] [ebp-208h] BYREF
  CHAR Buffer[256]; // [esp+160h] [ebp-108h] BYREF
  FILE *Stream; // [esp+264h] [ebp-4h]

  rf_vfile_build_loose_path(0, "rfd3d.id", FileName);
  result = fopen(FileName, "w");
  Stream = result;
  if ( result )
  {
    fprintf(Stream, "----------------------------\nD3D Device Information:\n\n");
    fprintf(Stream, "Device Description: %s\n", unk_1DAEB48);
    fprintf(Stream, "Vendor ID: %d\n", rf_d3d8_adapter_vendor_id);
    fprintf(Stream, "Device ID: %d\n", rf_d3d8_adapter_device_id);
    fprintf(Stream, "Subsystem ID: %d\n", unk_1DAED58);
    fprintf(Stream, "Revision: %d\n", unk_1DAED5C);
    fprintf(Stream, "\n----------------------------\nD3D Driver Information:\n\n");
    fprintf(Stream, "Driver filename: %s\n", MEMORY[0x1DAE948]);
    fprintf(Stream, "Product: 0x%x\n", unk_1DAED4E);
    fprintf(Stream, "Version: 0x%x\n", unk_1DAED4C);
    fprintf(Stream, "SubVersion: 0x%x\n", unk_1DAED4A);
    fprintf(Stream, "Build: 0x%x\n", unk_1DAED48);
    memset(&Stat, 0, sizeof(Stat));
    if ( !SearchPathA(nullptr, MEMORY[0x1DAE948], nullptr, 0x100u, Buffer, &FilePart) || _stat64i32(Buffer, &Stat) )
    {
      fprintf(Stream, "Unable to locate driver in path.\n");
    }
    else
    {
      fprintf(Stream, "Driver Location: %s\n", Buffer);
      fprintf(Stream, "Driver Date: 0x%x\n", LODWORD(Stat.st_mtime));
    }
    fprintf(Stream, "\n----------------------------\nRF D3D State Information:\n\n");
    fprintf(Stream, "AlphaTextureFormat: %d\n", unk_1DAED84);
    fprintf(Stream, "NonAlphaTextureFormat: %d\n", unk_1DAE900);
    fprintf(Stream, "ARGB1555TextureFormat: %d\n", unk_1DAE8F4);
    fprintf(Stream, "ScreenFormat: %d\n", unk_1DAE8F8);
    if ( byte_663F06 )
      fprintf(Stream, "D3Dsc: %s\n", "on");
    else
      fprintf(Stream, "D3Dsc: %s\n", (const char *)&off_646208);
    if ( unk_1DAEDA8 )
      fprintf(Stream, "D3Dbgb: %s\n", "on");
    else
      fprintf(Stream, "D3Dbgb: %s\n", (const char *)&off_64621C);
    if ( unk_1DAEDA9 )
      fprintf(Stream, "D3Dvm: %s\n", "on");
    else
      fprintf(Stream, "D3Dvm: %s\n", (const char *)&off_646230);
    if ( unk_1DAEDAB )
      fprintf(Stream, "D3Dv2m: %s\n", "on");
    else
      fprintf(Stream, "D3Dv2m: %s\n", (const char *)&off_646244);
    fprintf(Stream, "D3Dzm: %f\n", flt_6649F4);
    fprintf(Stream, "D3Drhw: %f\n", flt_6649F8);
    if ( unk_1DAEDEC )
      fprintf(Stream, "D3Dst: %s\n", "on");
    else
      fprintf(Stream, "D3Dst: %s\n", (const char *)&off_646270);
    if ( unk_1DAEDF0 )
      fprintf(Stream, "D3Dp2t: %s\n", "on");
    else
      fprintf(Stream, "D3Dp2t: %s\n", (const char *)&off_646284);
    if ( rf_d3d8_multitexture_available )
      fprintf(Stream, "D3Dmt: %s\n", "on");
    else
      fprintf(Stream, "D3Dmt: %s\n", (const char *)&off_646298);
    if ( unk_1DAEDF5 )
      fprintf(Stream, "D3Dm2x: %s\n", "on");
    else
      fprintf(Stream, "D3Dm2x: %s\n", (const char *)&off_6462AC);
    return (FILE *)fclose(Stream);
  }
  return result;
}

