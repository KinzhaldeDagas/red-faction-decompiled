// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E03A0 rf_pixel_copy_run_advance_source_destination
// UNREALRED VERIFIED [texture-conversion-20261028]: Argumentspixelcount,destinationpointeraddress,sourcepointeraddress,bytesperpixel. memcpy(*dst,*src,count*bytes),advancesBOTHpointersbyproduct,returnssourcepointeraddress. No overlap,negativecount,productoverfloworbufferboundschecks; callerssupplyvalidsizes.
const void **__cdecl rf_pixel_copy_run_advance_source_destination(int a1, void **a2, const void **a3, int a4)
{
  memcpy(*a2, *a3, a4 * a1);
  *a2 = (char *)*a2 + a4 * a1;
  *a3 = (char *)*a3 + a4 * a1;
  return a3;
}

