// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567020 rf_format_seconds_duration_h_m_ss
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): cdecl(signedSeconds,outBuffer), no capacity. Converts seconds to float,hours=trunc(value/3600). Positive hours subtract hours*3600 and format H:MM:SS;zero hours formats M:SS with no leading minute zero. Minutes/seconds from signed integer division/modulo60 of remaining float. Negative hours skip initial buffer write but enter append branch,so can append to incoming buffer without first initializing it; negative seconds get leading0 because seconds<10. Float conversion loses large-integer precision. Local12byte segment sprintf/copies,output strlen appends unbounded. Returns bytes of FINAL seconds substring INCLUDING its NUL,not total output length.
int __cdecl rf_format_seconds_duration_h_m_ss(int seconds, char *out)
{
  int result; // eax
  int v3; // [esp+78h] [ebp-20h]
  int v4; // [esp+7Ch] [ebp-1Ch]
  int v5; // [esp+80h] [ebp-18h]
  float v6; // [esp+84h] [ebp-14h]
  char v7[12]; // [esp+88h] [ebp-10h] BYREF

  v6 = (float)seconds;
  v3 = (int)(v6 / 3600.0);
  if ( v3 > 0 )
    v6 = v6 - (double)v3 * 3600.0;
  v4 = (int)v6 % 60;
  v5 = (int)v6 / 60;
  if ( v3 > 0 )
  {
    sprintf(out, "%d:", v3);
    if ( v5 < 10 )
    {
      strcpy(v7, "0");
      qmemcpy(&out[strlen(out)], v7, &v7[strlen(v7) + 1] - v7);
    }
  }
  if ( v3 )
  {
    sprintf(v7, "%d:", v5);
    qmemcpy(&out[strlen(out)], v7, &v7[strlen(v7) + 1] - v7);
  }
  else
  {
    sprintf(out, "%d:", v5);
  }
  if ( v4 < 10 )
  {
    strcpy(v7, "0");
    qmemcpy(&out[strlen(out)], v7, &v7[strlen(v7) + 1] - v7);
  }
  sprintf(v7, "%d", v4);
  result = &v7[strlen(v7) + 1] - v7;
  qmemcpy(&out[strlen(out)], v7, result);
  return result;
}

