// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FDC40 rf_jpeg_output_message_default
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jerror.c:output_message matched): Calls err.format_message+12(cinfo,localmessagebuffer),thenfprintf(stderr,"%s\n",buffer). Disassembly stagesbuffer andformat0x5FDC71/72 BEFORE CRT iobhelper0x60CDDE,adds0x40 toreturnedFILEbase forstderr,pushesstream andcallsfprintf0x5FDC80. Hex-Rays currentlymisassigns thetwo stagedarguments tohelperandshowsuninitializedv3;not actual uninitializedformat usage. No user-controlledformat substitutionherebeyondformatter;APIvoid.
int __cdecl rf_jpeg_output_message_default(int a1)
{
  FILE *v1; // eax
  char v3[204]; // [esp+0h] [ebp-D0h] BYREF

  (*(void (__cdecl **)(int, char *))(*(_DWORD *)a1 + 12))(a1, v3);
  v1 = (FILE *)crt_return_static_address_00664de0();
  return fprintf(v1 + 2, "%s\n", v3);
}

