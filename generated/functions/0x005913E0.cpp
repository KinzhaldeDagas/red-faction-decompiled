// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005913E0 rf_dsound_hresult_name_string
// UNREALRED VERIFIED [dsound-buffers-20261028]: Maps selected signed HRESULT values to static DSERR_* names,0 to DS_OK,other values unknown. Numeric-2147024809 and-2147221232 BOTH map to literal DSERR_NOAGGREGATION; preserves observed duplicate labeling rather than correcting it. Does not query system error text,allocate or log. Returned string is borrowed static storage.
const char *__cdecl rf_dsound_hresult_name_string(int a1)
{
  const char *result; // eax

  if ( a1 <= -2005401590 )
  {
    if ( a1 == -2005401590 )
      return "DSERR_ALLOCATED";
    if ( a1 <= -2147221232 )
    {
      if ( a1 != -2147221232 )
      {
        if ( a1 == -2147467263 )
          return "DSERR_UNSUPPORTED";
        if ( a1 == -2147467259 )
          return "DSERR_GENERIC";
        return "unknown";
      }
      return "DSERR_NOAGGREGATION";
    }
    if ( a1 == -2147024882 )
      return "DSERR_OUTOFMEMORY";
    if ( a1 == -2147024809 )
      return "DSERR_NOAGGREGATION";
    return "unknown";
  }
  if ( a1 > -2005401470 )
  {
    if ( a1 > -2005401430 )
    {
      if ( !a1 )
        return "DS_OK";
    }
    else
    {
      switch ( a1 )
      {
        case -2005401430:
          return "DSERR_UNINITIALIZED";
        case -2005401450:
          return "DSERR_BUFFERLOST";
        case -2005401440:
          return "DSERR_OTHERAPPHASPRIO";
      }
    }
    return "unknown";
  }
  if ( a1 == -2005401470 )
    return "DSERR_ALREADYINITIALIZED";
  switch ( a1 )
  {
    case -2005401570:
      result = "DSERR_CONTROLUNAVAIL";
      break;
    case -2005401550:
      result = "DSERR_INVALIDCALL";
      break;
    case -2005401530:
      result = "DSERR_PRIOLEVELNEEDED";
      break;
    case -2005401500:
      result = "DSERR_BADFORMAT";
      break;
    case -2005401480:
      result = "DSERR_NODRIVER";
      break;
    default:
      return "unknown";
  }
  return result;
}

