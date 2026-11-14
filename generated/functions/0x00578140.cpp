// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578140 rf_bitmap_read_source_pcx_palette_or_fatal
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): cdecl(handle,paletteOutput). Resolves current record and calls PCX header reader5E6210 using record name and default context9999999;dimension/header outputs go to ignored locals,palette output forwarded from caller. On nonzero PCX error formats Couldnt open filename and invokes fatal bmpman.cpp2970;success returns0. Does not use cached auxiliary pointer,check record file type or guard resolver-1/generation. Palette NULL behavior inherited from header reader;source can be reopened through VFile.
int __cdecl rf_bitmap_read_source_pcx_palette_or_fatal(unsigned int handle, void *palette)
{
  int result; // eax
  char Buffer[260]; // [esp+0h] [ebp-118h] BYREF
  int v4; // [esp+108h] [ebp-10h]
  int v5; // [esp+10Ch] [ebp-Ch] BYREF
  int v6; // [esp+110h] [ebp-8h] BYREF
  int v7; // [esp+114h] [ebp-4h] BYREF

  v4 = rf_bitmap_resolve_current_frame_slot(handle);
  result = rf_pcx_read_header_dimensions_palette(
             (char *)(dword_1897344 + 108 * v4),
             &v7,
             &v6,
             &v5,
             palette,
             (int)byte_98967F);
  if ( result )
  {
    sprintf(Buffer, "Couldn't open %s.\n", (const char *)(dword_1897344 + 108 * v4));
    rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\bmpman\\bmpman.cpp", 2970, Buffer);
  }
  return result;
}

