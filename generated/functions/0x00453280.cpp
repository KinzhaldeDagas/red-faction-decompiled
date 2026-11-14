// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00453280 rf_credits_event_exit_or_adjust_scroll
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl full32-bit event callback, no helpers; callback return is ignored by4477F0. If
// fade-inBYTE6EFEB1 ANYnonzero, return its ZERO-EXTENDED fullEAX value without reading event or changing state. Otherwise compute event-1 with32-bit wrap; unsigned>207 returns EAX0
// (retained zero from initial fade-in load). In-range1..208 uses PE-verified208-byte selector45331C and four jump pointers45330C. Events1 and57 store exitDWORD6F1504=1 then
// fade-outBYTE6EFEB0=1. Event200 stores scrollY6EFEB4=F32(oldY-frameFLOATseconds*DOUBLE40). Event208 storesY=F32(oldY+frameFLOATseconds*DOUBLE2*DOUBLE40), with no intermediate F32
// product store. Every other in-range event leaves globals unchanged. Native fullEAX for ALL in-range events is event-1, INCLUDING default cases; Hex-Rays apparent default return0 is
// false. No pause/deadline/mouse/scroll bound or extra argument read. Event processing and later parent baseline scroll remain separate native operations.
int __cdecl rf_credits_event_exit_or_adjust_scroll(int event)
{
  int result; // eax

  result = unk_6EFEB1;
  if ( !unk_6EFEB1 )
  {
    result = event - 1;
    switch ( event )
    {
      case 1:
      case 57:
        unk_6F1504 = 1;
        unk_6EFEB0 = 1;
        break;
      case 200:
        unk_6EFEB4 = unk_6EFEB4 - rf_frame_delta_seconds * 40.0;
        break;
      case 208:
        unk_6EFEB4 = rf_frame_delta_seconds * 2.0 * 40.0 + unk_6EFEB4;
        break;
      default:
        result = 0;
        break;
    }
  }
  return result;
}

