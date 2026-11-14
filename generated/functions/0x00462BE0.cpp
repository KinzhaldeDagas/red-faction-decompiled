// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462BE0 rf_browser_load_cache_and_favorites
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg. Open svrlist path6F51B8 rb;seek/ftell/rewind. Length not divisible by100 ->close,remove file,start discovery463050;missing file also starts discovery. Otherwise
// records=len/100;if signed capacity<records+512,release arrays,set capacity,allocate. Reused capacity does NOT independently clear liveCount. Read100 into stack/import until
// feof,liveCount>=fileRecords or capacity,or fread!=1;criterion is resulting liveCount,not records read. Then open favlist6F5090 rb:missing file preserves existing favoriteCount.
// Nonmultiple100 closes/removes without resetting it. Valid file resets favoriteCount0 and reads directly into favoriteArray up to fileRecords/512,imports each with favorite=1,and
// increments even if import rejected. No seek/ftell error,negative length,sorted-input,storageNULL or individual record validation. I/O results ignored except open/read;stored FILE*
// return is incidental mixed delegate residue.
FILE *rf_browser_load_cache_and_favorites()
{
  FILE *result; // eax
  int v1; // [esp+0h] [ebp-84h]
  _BYTE Buffer[108]; // [esp+4h] [ebp-80h] BYREF
  int v3; // [esp+74h] [ebp-10h]
  int v4; // [esp+78h] [ebp-Ch]
  FILE *Stream; // [esp+7Ch] [ebp-8h]
  size_t ElementSize; // [esp+80h] [ebp-4h]

  ElementSize = 100;
  Stream = fopen(unk_6F51B8, "rb");
  if ( Stream )
  {
    fseek(Stream, 0, 2);
    v3 = ftell(Stream);
    fseek(Stream, 0, 0);
    if ( v3 % (int)ElementSize )
    {
      fclose(Stream);
      remove(unk_6F51B8);
      rf_browser_start_discovery();
    }
    else
    {
      v4 = v3 / (int)ElementSize;
      if ( dword_6F5198 < v3 / (int)ElementSize + 512 )
      {
        rf_browser_release_record_and_index_arrays();
        dword_6F5198 = v4 + 512;
        rf_browser_allocate_record_and_index_arrays_once(v4 + 512);
      }
      while ( !feof(Stream)
           && unk_6F51A8 < v4
           && unk_6F51A8 < dword_6F5198
           && fread(Buffer, ElementSize, 1u, Stream) == 1 )
        rf_browser_import_cache100((int)Buffer, 0);
      fclose(Stream);
    }
  }
  else
  {
    rf_browser_start_discovery();
  }
  result = fopen(unk_6F5090, "rb");
  Stream = result;
  if ( result )
  {
    fseek(Stream, 0, 2);
    v1 = ftell(Stream);
    fseek(Stream, 0, 0);
    if ( v1 % (int)ElementSize )
    {
      fclose(Stream);
      return (FILE *)remove(unk_6F5090);
    }
    else
    {
      v4 = v1 / (int)ElementSize;
      for ( dword_6F52EC = 0;
            !feof(Stream)
         && dword_6F52EC < v4
         && dword_6F52EC < 512
         && fread((void *)(unk_6F52E8 + 100 * dword_6F52EC), ElementSize, 1u, Stream) == 1;
            ++dword_6F52EC )
      {
        rf_browser_import_cache100(unk_6F52E8 + 100 * dword_6F52EC, 1);
      }
      return (FILE *)fclose(Stream);
    }
  }
  return result;
}

