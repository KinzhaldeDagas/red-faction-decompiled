// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FDD10 rf_jpeg_format_message_default
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jerror.c:format_message matched): Args cinfo,destinationcharbuffer. Choosesbuilt-inmessage whenmsg_code20 within1..last116;otherwiseaddonifexistsandwithinfirst124..last128;missingentryfallsbackbuiltinindex0andstoresbadcodeinmsg_parm.i[0]24. ScansformatONLYuntilfirstpercent:ifnextchar s,passesmsg_parm.s(buffer+24) tosprintf;elsepasses8integerparams24..52. No snprintf/outputcapacity parameter;callerassumesJMSG_LENGTH_MAX. Does not emit/log/exit;incidental sprintfreturn.
int __cdecl rf_jpeg_format_message_default(int a1, char *Buffer)
{
  char v3; // [esp+3h] [ebp-15h]
  int v4; // [esp+4h] [ebp-14h]
  _DWORD *v5; // [esp+8h] [ebp-10h]
  int v6; // [esp+Ch] [ebp-Ch]
  char *v7; // [esp+10h] [ebp-8h]
  char *Format; // [esp+14h] [ebp-4h]

  v5 = *(_DWORD **)a1;
  v6 = *(_DWORD *)(*(_DWORD *)a1 + 20);
  Format = nullptr;
  if ( v6 <= 0 || v6 > v5[29] )
  {
    if ( v5[30] && v6 >= v5[31] && v6 <= v5[32] )
      Format = *(char **)(v5[30] + 4 * (v6 - v5[31]));
  }
  else
  {
    Format = *(char **)(v5[28] + 4 * v6);
  }
  if ( !Format )
  {
    v5[6] = v6;
    Format = *(char **)v5[28];
  }
  v4 = 0;
  v7 = Format;
  while ( 1 )
  {
    v3 = *v7++;
    if ( !v3 )
      break;
    if ( v3 == 37 )
    {
      if ( *v7 == 115 )
        v4 = 1;
      break;
    }
  }
  if ( v4 )
    return sprintf(Buffer, Format, v5 + 6);
  else
    return sprintf(Buffer, Format, v5[6], v5[7], v5[8], v5[9], v5[10], v5[11], v5[12], v5[13]);
}

