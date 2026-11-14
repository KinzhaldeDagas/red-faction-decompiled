// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00574990 rf_bitmap_format_bytes_per_pixel
// UNREALRED VERIFIED [texture-upload-20261028]: Internalformatcodes1/2->1byte,3/4/5/8->2,6->3,7->4; unknown->1. Purelookup,nohandlequery. Valuesareformatcodes,notbitmaphandles.
int __cdecl rf_bitmap_format_bytes_per_pixel(int a1)
{
  int result; // eax

  switch ( a1 )
  {
    case 1:
    case 2:
      result = 1;
      break;
    case 3:
    case 4:
    case 5:
      result = 2;
      break;
    case 6:
      result = 3;
      break;
    case 7:
      result = 4;
      break;
    case 8:
      result = 2;
      break;
    default:
      result = 1;
      break;
  }
  return result;
}

