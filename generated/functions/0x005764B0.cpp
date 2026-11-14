// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005764B0 rf_bitmap_get_resolved_upload_metadata
// UNREALRED VERIFIED [texture-upload-20261028]: Resolvesbitmap/frame0x574B80 into108-byterecord0x1897344. If recordDWORD+52nonzero,writes outputs unsigned16width+44,height+46,DWORD+48,andbyte+64(mipcountusedbyrenderer). IfDWORD+52zero,writesONLYwidth/height0,leavingthird/fourthoutputsunchanged. No failedresolver/indexguard. Returnincidentalrecordbase/outputpointer,notvalidatedstatus.
_DWORD *__cdecl rf_bitmap_get_resolved_upload_metadata(unsigned int a1, _DWORD *a2, _DWORD *a3, _DWORD *a4, _DWORD *a5)
{
  _DWORD *result; // eax
  int v6; // [esp+0h] [ebp-4h]

  v6 = rf_bitmap_resolve_current_frame_slot(a1);
  if ( *(_DWORD *)(dword_1897344 + 108 * v6 + 52) )
  {
    *a2 = *(unsigned __int16 *)(dword_1897344 + 108 * v6 + 44);
    *a3 = *(unsigned __int16 *)(dword_1897344 + 108 * v6 + 46);
    *a4 = *(_DWORD *)(dword_1897344 + 108 * v6 + 48);
    result = (_DWORD *)dword_1897344;
    *a5 = *(unsigned __int8 *)(dword_1897344 + 108 * v6 + 64);
  }
  else
  {
    *a3 = 0;
    *a2 = 0;
    return a3;
  }
  return result;
}

