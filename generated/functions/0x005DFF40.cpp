// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DFF40 rf_pixel_bytes_equal_do_while
// UNREALRED VERIFIED [image-headers-20261028]: Arguments two byte pointers,count. Compares byte pairs and returns0 on first mismatch,else1 after count bytes. Uses do/while, so count<=0 STILL compares one byte. No null/length checks; does not compare entire pixel stride unless supplied count equals stride.
int __cdecl rf_pixel_bytes_equal_do_while(char *a1, char *a2, int a3)
{
  int v3; // ecx
  int v4; // eax

  do
  {
    v3 = *a2;
    v4 = *a1;
    ++a2;
    ++a1;
    if ( v4 != v3 )
      return 0;
    --a3;
  }
  while ( a3 > 0 );
  return 1;
}

