// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED580 rf_acm_enumerate_ms_adpcm_driver_callback
// UNREALRED VERIFIED [wave-codec-20261028]: ACM enumeration callback. Queries920-byte ACMDRIVERDETAILSA; on failure replaces short/long names with global string0x664B0C. Queries metric0x65 into local but ignores value/result. Case-insensitive short name MS-ADPCM selects driver; if signed support flags>=0 stores driver ID at0x1F67108,otherwise null. Matching name always returnsFALSE0,stopping enumeration even if rejected by sign flag; other namesTRUE1. Does not open driver or validate details beyond name.
BOOL __stdcall rf_acm_enumerate_ms_adpcm_driver_callback(
        HACMDRIVERID hadid,
        DWORD_PTR dwInstance,
        signed int fdwSupport)
{
  struct tACMDRIVERDETAILSA padd; // [esp+4h] [ebp-3A8h] BYREF
  int pMetric; // [esp+3A8h] [ebp-4h] BYREF

  padd.cbStruct = 920;
  if ( acmDriverDetailsA(hadid, &padd, 0) )
  {
    lstrcpyA(padd.szShortName, asc_664B0C);
    lstrcpyA(padd.szLongName, asc_664B0C);
  }
  pMetric = -1;
  acmMetrics((HACMOBJ)hadid, 0x65u, &pMetric);
  if ( _stricmp("MS-ADPCM", padd.szShortName) )
    return 1;
  if ( fdwSupport >= 0 )
    *(_DWORD *)&byte_1F670FC[12] = hadid;
  else
    *(_DWORD *)&byte_1F670FC[12] = 0;
  return 0;
}

