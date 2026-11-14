// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FD300 rf_jpeg_default_colorspace
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcparam.c:jpeg_default_colorspace matched): Maps inputcolor enum40:UNKNOWN0->UNKNOWN0,GRAYSCALE1->1,RGB2 orYCbCr3->YCbCr3,CMYK4->4,YCCK5->5;other inputerror9 BadInColorSpace. Delegates jpeg_set_colorspace0x5FD3C0,which validatesstate100 andpopulatescomponents. Thus RGB defaults subsampledYCbCr rather than RGBoutput;APIvoid.
int __cdecl rf_jpeg_default_colorspace(_DWORD *a1)
{
  int result; // eax

  switch ( a1[10] )
  {
    case 0:
      result = rf_jpeg_set_colorspace(a1, 0);
      break;
    case 1:
      result = rf_jpeg_set_colorspace(a1, 1);
      break;
    case 2:
    case 3:
      result = rf_jpeg_set_colorspace(a1, 3);
      break;
    case 4:
      result = rf_jpeg_set_colorspace(a1, 4);
      break;
    case 5:
      result = rf_jpeg_set_colorspace(a1, 5);
      break;
    default:
      *(_DWORD *)(*a1 + 20) = 9;
      result = (*(int (__cdecl **)(_DWORD *))*a1)(a1);
      break;
  }
  return result;
}

